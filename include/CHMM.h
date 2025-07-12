#pragma once
#include"hash_utils.h"
#include"State.h"

#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <functional>

using HMM_t = std::vector<State>;
using CHMMConf_t = std::vector<std::vector<State>>;

class CHMM {
public :
    CHMM(const std::unordered_map<std::vector<State>, double>& E_0, const std::vector<std::vector<State>>& S_E_);
    void update(const std::vector<std::vector<double>> O_t);
    static CHMMConf_t compute_conf(const std::vector<HMM_t>& state_set);

    void print();

private :
    std::unordered_map<std::vector<State>, double> E_t;
    std::unordered_map<std::vector<State>, double> E_t_m_1;
    std::vector<std::vector<State>> S_E; //Non accessible configuration S\E

};
