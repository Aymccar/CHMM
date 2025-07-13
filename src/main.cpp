#include"CHMM.h"
#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

int main(int argc, char** argv){

    //HMM 1 (3 states)
    State air("air", [](vector<double> O_t){return 1;},     {{"air", 0.33}, {"earth", 0.33}, {"see", 0.33}});
    State earth("earth", [](vector<double> O_t){return 1;}, {{"air", 0.33}, {"earth", 0.33}, {"see", 0.33}});
    State see("see", [](vector<double> O_t){return 1;},     {{"air", 0.33}, {"earth", 0.33}, {"see", 0.33}});

    vector<State> HMM1 = {air, earth, see};
    vector<State> HMM2 = HMM_t(HMM1);

    vector<vector<State>> states = CHMM::compute_conf({HMM1, HMM2});
    unordered_map<vector<State>, double> E_0;

    vector<State> init = {air, air};
    vector<vector<State>> S_E = {{air, earth}, {see, earth}};


    for(size_t i = 0; i< states.size(); i++){
        E_0[states[i]] = 0;
        if (states[i] == init){
            E_0[states[i]] = 1;
        }
    }

    CHMM chmm(E_0, S_E);

    vector<vector<double>> O_t = {{0}};

    for(size_t i = 0; i < 100; i++){
        chmm.update(O_t);
        chmm.print();
        cout << "-----------------" << endl;
    }
    unordered_map<State, double> prob_0 = chmm.get_prob(0);
    unordered_map<State, double> prob_1 = chmm.get_prob(1);

    cout << "HMM 1 : " << endl;
    for (auto& [conf, prob] : prob_0) {
        cout << conf.get_name() << " : " << prob << endl;
    }
    cout << "HMM 2 : " << endl;
    for (auto& [conf, prob] : prob_1) {
        cout << conf.get_name() << " : " << prob << endl;
    }

    return 0;
}
