//
// Created by Luke Pebody on 26/03/2024.
//

#ifndef ADMISSABLE_SAT_COMBINATIONS_H
#define ADMISSABLE_SAT_COMBINATIONS_H

#include <vector>

class combinations
{
private:
    std::vector<int> _v;
    int _n;
    int _k;
public:
    combinations(int n, int k):
        _n(n), _k(k)
    {
        _v.reserve(k);
        for (int i = 0; i < k; ++i)
            _v.push_back(i);
    }

    bool finished()
    {
        return _v[_k - 1] >= _n;
    }

    void operator++()
    {
        int i = _k - 1;
        while ((i >= 0) && (_v[i] == _n - _k + i))
            --i;
        if (i < 0)
            i = 0;
        ++_v[i];
        for (int j = i + 1; j < _k; ++j)
            _v[j] = _v[j - 1] + 1;
    }

    int operator[](int i)
    {
        return _v[i];
    }
};

#endif //ADMISSABLE_SAT_COMBINATIONS_H
