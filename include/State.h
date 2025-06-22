#pragma once

class State {
public:
    State(){};
    State(std::string name, std::function<double(std::vector<double>)> emission, std::unordered_map<std::string, double> transition)
    :_name(name), _emission(emission), _transition(transition){};

    std::string get_name() const {return _name;};

    double emission(const std::vector<double>& o_t) const {return _emission(o_t);};
    double transition(const State& state) const {return _transition.find(state.get_name())->second;};

    bool operator==(const State& other) const {
        return _name == other._name;
    }

private:

    std::string _name;
    std::function<double(std::vector<double> o_t)> _emission;
    std::unordered_map<std::string, double> _transition; //State A store the map {A : P(A|A), B : P(B|A), ... } //TODO replace string with State but /!\ cause of recc decl
};

