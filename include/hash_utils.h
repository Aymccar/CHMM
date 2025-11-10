#pragma once
#include <vector>
#include <string>
#include <functional>
#include "State.h"

namespace std {
    template <>
    struct hash<CHMM::State> {
        std::size_t operator()(const CHMM::State& s) const noexcept {
            return std::hash<std::string>()(s.get_name());
        }
    };

    template <>
    struct hash<std::vector<CHMM::State>> {
        std::size_t operator()(const std::vector<CHMM::State>& vec) const noexcept {
            std::size_t seed = 0;
            for (const auto& s : vec) {
                seed ^= std::hash<CHMM::State>()(s) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

