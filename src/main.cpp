#include<vector>
#include<unordered_map>
#include<iostream>
#include<cmath>

#include<CHMM.h>
#include<probably.h>

using namespace std;

int main(int argc, char** argv){

    //HMM 1 (3 states)
    CHMM::State air("air", [](const vector<double>& O_t){ return abs(cos(O_t[0])*sin(O_t[0]));},   //The emission is |cos(t)*sin(t)|
                                                                                                {{"air", 0.80}, {"earth", 0.15}, {"see", 0.05}}); //From air to {air, earth, see}
                                                                                                                                                  
    CHMM::State earth("earth", [](const vector<double>& O_t){return probably::indicator_est(Eigen::Vector2d(O_t.data()), 15, 0, 500);}, //The emission is the uniform distribution on a 2d ball of radius 15 estimated with 500 gaussians and no noise
                                                                                                {{"air", 0.33}, {"earth", 0.33}, {"see", 0.33}}); //From earth to {air, earth, see} 
                                                                                                                                                  
    CHMM::State see("see", [](const vector<double>& O_t){return 0.01;},                          //The emission is 0.1
                                                                                                {{"air", 0.40}, {"earth", 0.20}, {"see", 0.40}}); //From see to {air, earth, see}

    CHMM::HMM HMM1 = {air, earth, see}; //HMM1 is composed of the 3 states

    //HMM 2 (copy of HMM1)
    vector<CHMM::State> HMM2 = CHMM::HMM(HMM1);

    //HMM 3 (only air and see)
    vector<CHMM::State> HMM3 = {air, see};

    //Compute all configuration E_HMM_1 X E_HMM_2
    vector<vector<CHMM::State>> states = CHMM::CHMM::compute_conf({HMM1, HMM2, HMM3});

    //Exclude some configuration
    vector<vector<CHMM::State>> S_E = {{air, air, air}};

    //Init 
    unordered_map<vector<CHMM::State>, double> E_0;
    vector<CHMM::State> init = {air, earth, air};
    for(size_t i = 0; i< states.size(); i++){
        E_0[states[i]] = 0;
        if (states[i] == init){
            E_0[states[i]] = 1;
        }
    }

    //CHMM from both sub-HMM
    CHMM::CHMM chmm(E_0, S_E);


    for(size_t i = 0; i < 100; i++){
        vector<vector<double>> O_t = {{(double)2*i}, //O^1_t
                                      {(double)i/10, (double)sqrt(i)}, //O^2_t (2d)
                                      {(double)100/(i+1)}}; //O^3_t
        chmm.update(O_t);
        chmm.print();
        cout << "-----------------" << endl;
    }
    cout << "Sum to check: " << chmm.sum() << " (Have to be 1)" << endl;
    cout << "-----------------" << endl;
    
    //Get i-th sub-HMM states probabilities
    unordered_map<CHMM::State, double> prob_0 = chmm.get_prob(0);
    unordered_map<CHMM::State, double> prob_1 = chmm.get_prob(1);
    unordered_map<CHMM::State, double> prob_2 = chmm.get_prob(2);

    cout << "HMM 1 : " << endl;
    for (auto& [conf, prob] : prob_0) {
        cout << conf.get_name() << " : " << prob << endl;
    }

    cout << "HMM 2 : " << endl;
    for (auto& [conf, prob] : prob_1) {
        cout << conf.get_name() << " : " << prob << endl;
    }

    cout << "HMM 3 : " << endl;
    for (auto& [conf, prob] : prob_2) {
        cout << conf.get_name() << " : " << prob << endl;
    }

    return 0;
}
