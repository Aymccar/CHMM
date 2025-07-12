#include "State.h"
#include <string>

State::State(const State& other)
    : _name(other._name),
      _emission(other._emission),
      _transition(other._transition)
{}

