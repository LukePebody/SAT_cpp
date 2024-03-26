//
// Created by Luke Pebody on 25/03/2024.
//

#ifndef ADMISSABLE_SAT_PROBLEM_H
#define ADMISSABLE_SAT_PROBLEM_H

#include <map>
#include <set>
#include <vector>

class problem {
private:
    int _num_atoms = 0;
    std::vector<std::pair<std::vector<int>, std::vector<int>>> _atom_to_rules;
    std::vector<std::optional<bool>> _marks;
    std::set<int> _variables;
    std::vector<int> _satisfying_counts;
    std::set<int> _still_to_solve;
    std::vector<std::vector<std::pair<int, bool>>> _rules;

public:
    void add_rule(const std::vector<std::pair<int, bool>>& rule);
    void mark(int atom, bool set_true);
    void unmark(int atom);
    bool is_marked(int atom);
    bool marked_true(int atom);
    [[nodiscard]] std::pair<std::vector<std::vector<int>>,std::vector<int>> dimacs_and_variables() const;
    std::vector<std::pair<int, bool>> get_marks();
};




#endif //ADMISSABLE_SAT_PROBLEM_H
