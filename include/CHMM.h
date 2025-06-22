#pragma once
#include"hash_utils.h"
#include"State.h"

#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <functional>


class CHMM {
public :
    CHMM(const std::unordered_map<std::vector<State>, double>& E_0);
    void update(const std::vector<std::vector<double>> O_t);
    static std::vector<std::vector<State>> compute_conf(const std::vector<std::vector<State>>& state_set);

    void print();

private :
    std::unordered_map<std::vector<State>, double> E_t;
    std::unordered_map<std::vector<State>, double> E_t_m_1;

};
