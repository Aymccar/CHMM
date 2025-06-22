#include"CHMM.h"
#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

int main(int argc, char** argv){

    //HMM 1 (3 states)
    State air("air", [](vector<double> O_t){return 1;},     {{"air", 0.00}, {"earth", 0.50}, {"see", 0.50}});
    State earth("earth", [](vector<double> O_t){return 1;}, {{"air", 0.50}, {"earth", 0.50}, {"see", 0.00}});
    State see("see", [](vector<double> O_t){return 1;},     {{"air", 0.00}, {"earth", 0.00}, {"see", 1.00}});

    vector<State> HMM1 = {air, earth, see};

    vector<vector<State>> states = CHMM::compute_conf({HMM1});
    unordered_map<vector<State>, double> E_0;

    vector<State> init = {air};
    for(size_t i = 0; i< states.size(); i++){
        E_0[states[i]] = 0;
        if (states[i] == init){
            E_0[states[i]] = 1;
        }
    }

    CHMM chmm(E_0);

    vector<vector<double>> O_t = {{0}};

    for(size_t i = 0; i < 100; i++){
        chmm.update(O_t);
        chmm.print();
        cout << "-----------------" << endl;
    }

    return 0;
}
