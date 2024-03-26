//
// Created by Luke Pebody on 26/03/2024.
//

#ifndef ADMISSABLE_SAT_ADMISSABLE_SET_N_MINUS_2_H
#define ADMISSABLE_SAT_ADMISSABLE_SET_N_MINUS_2_H

#include "recursive_optimisable_problem.h"

class admissable_set_n_minus_2 : public recursive_optimisable_problem
{
private:
    [[nodiscard]] int num_clauses() const override;
    virtual std::string clause_name(int i) override;

public:
    admissable_set_n_minus_2(int m);
    void write_to(std::string filename);
};

#endif //ADMISSABLE_SAT_ADMISSABLE_SET_N_MINUS_2_H
