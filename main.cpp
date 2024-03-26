#include <iostream>

#include "admissable_set_n_minus_2.h"
#include "logger.h"
#include "kissat.h"
#include "ramsey_number.h"

int main() {
    std::vector<std::pair<int, bool>> prev_marks;
    for (int m = 3; m < 100000; ++m)
    {
        admissable_set_n_minus_2 prob(m);
        prob.set_initial_marks(prev_marks);
        bool solvable = prob.start();
        if (!solvable)
        {
            logger() << "The best you can do is " << m - 1;
            break;
        }
        std::stringstream strm;
        strm << "found_sets/admissable_set_" << m << "_" << (m - 2) << ".txt";
        prob.write_to(strm.str());
        solvable = prob.optimise();
        std::stringstream strm2;
        strm2 << "found_sets/optimal_admissable_set_" << m << "_" << (m - 2) << ".txt";
        prob.write_to(strm2.str());
        prev_marks = prob.get_marks();
    }
}
