#include"CHMM.h"

#include <fstream>
#include <string>

using namespace std;


CHMM::CHMM(const unordered_map<vector<State>, double>& E_0, const vector<vector<State>>& S_E_):
    E_t(E_0), E_t_m_1(E_0), S_E(S_E_), header(false)
{
}

// Used for compute_conf
void cartesianProduct(
    const vector<vector<State>>& input,
    vector<State>& current,
    size_t depth,
    vector<vector<State>>& result
) {
    if (depth == input.size()) {
        result.push_back(current);  // current is already a vector<string>
        return;
    }

    for (const auto& state : input[depth]) {
        current[depth] = state; // Assign state name at current depth
        cartesianProduct(input, current, depth + 1, result);
    }
}

    
// Used by the user to easily get a vector of string with all the possible configuration of the CHMM. Usefull at least for the init
vector<vector<State>> CHMM::compute_conf(const vector<vector<State>>& HMMs) {
    vector<vector<State>> result;
    vector<State> current(HMMs.size());  // Flat vector of names
    cartesianProduct(HMMs, current, 0, result);
    return result;
}

void CHMM::update(const vector<vector<double>>& O_t){

    E_t_m_1 = unordered_map<vector<State>, double>(E_t); //Copy data at time t in t-1
    for (auto& [_, prob] : E_t){prob = 0;}; // emptying E_t
     
    for (auto& [conf_t, prob_t] : E_t) { //Calculation made for every configuration at the time t
        bool is_accessible = true;
        for (const auto& s_e : S_E){
            if (s_e == conf_t) {
                prob_t = 0;
                is_accessible = false;
            }
        } 
        if (is_accessible){
            for (const auto& [conf_t_m_1, prob_t_m_1] : E_t_m_1){ //Then for every previous configuration
               double prob_sub_transition = 1;
               for(size_t i = 0; i < conf_t_m_1.size(); i++){ // Transition for every sub-HMM
                   prob_sub_transition *= conf_t_m_1[i].transition(conf_t[i]); //Each transition are independent 
               }
               prob_sub_transition *= prob_t_m_1;
               prob_t += prob_sub_transition;
            }

            for (size_t i = 0; i < conf_t.size(); i++){ //Emission
                prob_t *= conf_t[i].emission(O_t[i]); //Each emission are independent
            }
        }
    }

    double sum_ = 0.0;
    for (const auto& [_, prob_t] : E_t){ //Computation of the normalization factor
        sum_ += prob_t;
    }

    for (auto& [_, prob_t] : E_t){
        prob_t /= sum_;
    }
}

unordered_map<State, double> CHMM::get_prob(int i) {
    unordered_map<State, double> ret;
    for (const auto& [conf, prob] : E_t){
        State state_i = conf[i];
        //ret.try_emplace(state_i, 0); Seems unnecessary
        ret[state_i] += prob;
    }

    return ret;
}

vector<unordered_map<State, double>> CHMM::get_prob() {
    vector<unordered_map<State, double>> ret;
    for (int i = 0; i < E_t.begin()->first.size(); i++){
        ret.push_back(get_prob(i));
    }
    return ret;
}

double CHMM::sum(){
    double sum = 0;
    for (auto [_, prob] : E_t) sum += prob;
    return sum;
}

void CHMM::write(std::ofstream& stream, double ts){
    if (!header) {
        stream << "ts" << "\t";
        for (const auto& [conf, _] : E_t){
            for (auto state_ptr = conf.begin(); state_ptr != conf.end(); state_ptr++){
                stream << state_ptr->get_name();
                if (state_ptr != conf.end() - 1) stream << " - ";
            }
            stream << "\t"; //std::tab
        }
        header = true;
        stream << std::endl;
    }
    
    stream << ts << "\t";
    for (const auto& [_, prob] : E_t){
        stream << prob << "\t";
    }
    stream << std::endl;
}


void CHMM::print(){
    for (const auto& [conf, prob] : E_t){
        cout << "Pr(";
        for (auto state_ptr = conf.begin(); state_ptr != conf.end(); state_ptr++){
            cout << state_ptr->get_name();
            if (state_ptr != conf.end()){cout<<" - ";}
        }
        cout <<")";
        cout <<" = " << prob << endl;
    }
}
