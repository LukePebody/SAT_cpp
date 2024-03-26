//
// Created by Luke Pebody on 25/03/2024.
//

#ifndef ADMISSABLE_SAT_INVERSE_FUNCTION_H
#define ADMISSABLE_SAT_INVERSE_FUNCTION_H

#include <set>
#include <iostream>
#include <map>
#include <algorithm>

class inverse_function
{
private:
    std::function<int(int)> _f;
    std::map<int, int> _m;

public:
    inverse_function(std::function<int(int)> f):
        _f (f),
        _m {{0, 0}}
    {
    }

    int lookup(int i)
    {
        auto mit = _m.upper_bound(i);
        if (mit != _m.end())
        {
            --mit;
            return mit->second;
        }
        --mit;
        int j = mit->second;
        while (true)
        {
            ++j;
            int v = _f(j);
            _m[v] = j;
            if (v > i)
                return j - 1;
        }
    }
};

#endif //ADMISSABLE_SAT_INVERSE_FUNCTION_H
