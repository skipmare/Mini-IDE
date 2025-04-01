//
// Created by ADMIN on 30/04/2024.
//
#include <algorithm>
#include <vector>
#include <map>
#include "set"
#include "queue"
using namespace std;
#include "iostream"


#ifndef TA_ENFA_CPP
#define TA_ENFA_CPP

class ENFA_state {
    std::multimap<std::string, ENFA_state *> transitions;
    std::string name;
    bool is_final;
    bool is_start;

    std::vector<ENFA_state *> e_closure;
public:
    ENFA_state() {};
    ENFA_state(std::string name, bool is_final, bool is_start) {
        this->name = name;
        this->is_final = is_final;
        this->is_start = is_start;
    }

    bool is_final_state() {
        return is_final;
    }

    bool is_start_state() {
        return is_start;
    }

    std::string get_name() {
        return name;
    }
    void set_start(bool is_start) {
        this->is_start = is_start;
    }
    void set_final(bool is_final) {
        this->is_final = is_final;
    }

    void add_transition(std::string input, ENFA_state *state) {
        transitions.insert(std::make_pair(input, state));
    }


    std::multimap<std::string, ENFA_state *> get_alltransitions() {
        if (this == nullptr) {
            throw std::runtime_error("Attempted to call get_alltransitions on a null ENFA_state pointer");
        }
        return transitions;
    }

    std::vector<ENFA_state *> get_e_closure() {
        return e_closure;
    }

    void set_e_closure(std::vector<ENFA_state *> e_closure) {
        this->e_closure = e_closure;
    }

};

class ENFA {
    std::vector<ENFA_state *> states;
    std::vector<string> alphabet;
    ENFA_state *start_state;
    std::vector<ENFA_state *> final_states;
    std::string type = "ENFA";
    std::string eps;
public:
    ENFA(){};

    void add_state(ENFA_state *state) {
        states.push_back(state);
    }
    void set_alphabet(std::vector<std::string> alphabet) {
        this->alphabet = alphabet;
    }
    std::string get_eps() {
        return eps;
    }
    void set_start(ENFA_state *state) {
        start_state = state;
    }
    void add_final_state(ENFA_state *state) {
        final_states.push_back(state);
    }
    ENFA_state *get_start_state() {
        return start_state;
    }
    std::vector<ENFA_state *> get_final_states() {
        return final_states;
    }
    std::vector<ENFA_state *> get_states() {
        return states;
    }

    void set_eps(std::string eps) {
        this->eps = eps;
    }


    void printStats(){
        std::cout<<"no_of_states="<<this->states.size()<<std::endl;
        int eps_counter = 0;

        for(ENFA_state* state: states) {
            for(auto transition: state->get_alltransitions()) {
                if(transition.first == eps) {
                    eps_counter++;
                }
            }
        }

        std::cout<<"no_of_transitions["<<eps<<"]"<<"="<<eps_counter<<std::endl;
        // Sort the alphabet vector in ascending order
        std::sort(this->alphabet.begin(), this->alphabet.end());

// Now iterate over the sorted alphabet vector
        for(string alpha : this->alphabet){
            int counter = 0;
            for(ENFA_state* state: states){
                for(auto transition: state->get_alltransitions()){
                    if(transition.first == alpha){
                        counter++;
                    }
                }
            }
            std::cout<<"no_of_transitions["<<alpha<<"]"<<"="<<counter<<std::endl;
        }

        std::map<int, int> degree_map;

        for (ENFA_state* state: states) {
            int degree = state->get_alltransitions().size();
            degree_map[degree]++;
        }
        for(auto degree: degree_map){
            std::cout<<"degree["<<degree.first<<"]"<<"="<<degree.second<<std::endl;
        }
    }

    bool accepts(const std::string& input) {
        // Use a queue for BFS traversal
        std::queue<std::pair<ENFA_state*, std::string>> queue;

        // To prevent revisiting the same state with the same remaining input
        std::set<std::pair<std::string, std::string>> visited;

        // Start with the initial state
        queue.push({start_state, input});

        while (!queue.empty()) {
            auto [current_state, remaining_input] = queue.front();
            queue.pop();

            // Create a unique identifier for this state and input combination
            std::string state_id = current_state->get_name();
            std::pair<std::string, std::string> state_input_pair = {state_id, remaining_input};

            // Skip if we've already processed this state with this remaining input
            if (visited.find(state_input_pair) != visited.end()) {
                continue;
            }

            // Mark as visited
            visited.insert(state_input_pair);

            // Check if we've reached an accepting state with no input left
            if (remaining_input.empty() && current_state->is_final_state()) {
                return true;
            }

            // Process all transitions from the current state
            for (auto transition : current_state->get_alltransitions()) {
                // For epsilon transitions, don't consume any input
                if (transition.first == eps) {
                    queue.push({transition.second, remaining_input});
                }
                    // For character transitions, check if we can consume the next character
                else if (!remaining_input.empty() && transition.first == std::string(1, remaining_input[0])) {
                    queue.push({transition.second, remaining_input.substr(1)});
                }
            }
        }

        // If we've exhausted all possibilities without accepting, reject
        return false;
    }


};


#endif //TA_ENFA_CPP
