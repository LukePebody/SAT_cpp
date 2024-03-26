//
// Created by Luke Pebody on 26/03/2024.
//

#ifndef ADMISSABLE_SAT_RECURSIVE_OPTIMISABLE_PROBLEM_H
#define ADMISSABLE_SAT_RECURSIVE_OPTIMISABLE_PROBLEM_H


#include "problem.h"
#include "kissat.h"

class recursive_optimisable_problem {
private:
    bool solvable();
    kissat _k;
    std::string _problem_type;

    [[nodiscard]] virtual int num_clauses() const = 0;
    virtual std::string clause_name(int i) = 0;

protected:
    int _m;
    problem _sat;
    std::set<int> _latest_model;

public:
    recursive_optimisable_problem(int m, const std::string& problem_type);
    void set_initial_marks(const std::vector<std::pair<int, bool>>& initial_marks);
    bool start();
    bool optimise();
    virtual void write_to(std::string filename) = 0;
    std::vector<std::pair<int, bool>> get_marks();
};


#endif //ADMISSABLE_SAT_RECURSIVE_OPTIMISABLE_PROBLEM_H
