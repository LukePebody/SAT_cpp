//
// Created by Luke Pebody on 25/03/2024.
//

#ifndef ADMISSABLE_SAT_TUPLES_H
#define ADMISSABLE_SAT_TUPLES_H

#include "inverse_function.h"
#include <set>
#include <iostream>
#include <map>
#include <algorithm>

int func_1(int p)
{
    return (p - 1) * (p - 2) * (p - 3) / 2;
}

int func_2(int r)
{
    return 3 * (r - 1) * (r - 2) / 2;
}

inverse_function func_1_inverse(func_1);
inverse_function func_2_inverse(func_2);



int tuple_to_int(const std::pair<std::pair<int, int>, int>& tuple)
{
    int a = tuple.first.first;
    int b = tuple.first.second;
    int c = tuple.second;
    int largest = std::max(std::max(a, b), c);
    int smallest = std::min(std::min(a, b), c);
    int middle = a + b + c - largest - smallest;
    return func_1(largest) + func_2(middle) + 3 * (smallest - 1) + ((c == middle) ? 1 : (c == smallest) ? 2 : 0);
}

std::pair<std::pair<int, int>, int> int_to_tuple(int n)
{
    int largest = func_1_inverse.lookup(n);
    n -= func_1(largest);
    int middle = func_2_inverse.lookup(n);
    n -= func_2(middle);
    int smallest = 1 + (n / 3);
    n -= 3 * (smallest - 1);
    if (n == 0)
        return std::make_pair(std::make_pair(smallest, middle), largest);
    if (n == 1)
        return std::make_pair(std::make_pair(smallest, largest), middle);
    return std::make_pair(std::make_pair(middle, largest), smallest);
}

#endif //ADMISSABLE_SAT_TUPLES_H
