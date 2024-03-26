//
// Created by Luke Pebody on 26/03/2024.
//

#ifndef ADMISSABLE_SAT_KISSAT_H
#define ADMISSABLE_SAT_KISSAT_H

#include <set>
#include <vector>
#include "problem.h"

class kissat {

public:
    std::optional<std::set<int>> solve(const problem& p);
};


#endif //ADMISSABLE_SAT_KISSAT_H
