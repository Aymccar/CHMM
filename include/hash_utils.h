#pragma once

#include <vector>
#include <string>
#include <functional>
#include "State.h"  // assuming State is defined in State.h

namespace std {
    template <>
    struct hash<State> {
        std::size_t operator()(const State& s) const noexcept {
            return std::hash<std::string>()(s.get_name());
        }
    };

    template <>
    struct hash<std::vector<State>> {
        std::size_t operator()(const std::vector<State>& vec) const noexcept {
            std::size_t seed = 0;
            for (const auto& s : vec) {
                seed ^= std::hash<State>()(s) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

