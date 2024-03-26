cmake_minimum_required(VERSION 3.24)
project(Admissable_SAT)

set(CMAKE_CXX_STANDARD 17)

add_executable(Admissable_SAT main.cpp problem.cpp admissable_set_n_minus_2.cpp logger.cpp kissat.cpp recursive_optimisable_problem.cpp recursive_optimisable_problem.h ramsey_number.cpp ramsey_number.h)
