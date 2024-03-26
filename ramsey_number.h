//
// Created by Luke Pebody on 26/03/2024.
//

#ifndef ADMISSABLE_SAT_RAMSEY_NUMBER_H
#define ADMISSABLE_SAT_RAMSEY_NUMBER_H


#include "recursive_optimisable_problem.h"

class ramsey_number : public recursive_optimisable_problem
{
private:
    [[nodiscard]] int num_clauses() const override;
    std::string clause_name(int i) override;

public:
    ramsey_number(int m);
    void write_to(std::string filename) override;
};


#endif //ADMISSABLE_SAT_RAMSEY_NUMBER_H
