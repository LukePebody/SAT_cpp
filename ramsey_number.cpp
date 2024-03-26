//
// Created by Luke Pebody on 26/03/2024.
//

#include <fstream>
#include <string>

#include "ramsey_number.h"
#include "combinations.h"

int edge_to_int(std::pair<int, int> p)
{
    return (p.second * (p.second - 1) / 2) + p.first;
}

std::pair<int, int> int_to_edge(int k)
{
    int j = 1;
    while (j * (j + 1) <= 2 * k)
        ++j;
    return {k - (j - 1) * j / 2, j};
}

int ramsey_number::num_clauses() const
{
    return _m * (_m - 1) / 2;
}

ramsey_number::ramsey_number(int m):
        recursive_optimisable_problem(m, "Ramsey number problem")
{
    int a = 3;
    int b = 5;
    for (auto h = combinations(_m, a); !h.finished(); ++h)
    {
        std::vector<std::pair<int, bool>> rule;
        for (int i = 0; i < a; i++)
            for (int j = i + 1; j < a; j++)
                rule.emplace_back(edge_to_int({h[i], h[j]}), true);
        _sat.add_rule(rule);
    }
    for (auto h = combinations(_m, b); !h.finished(); ++h)
    {
        std::vector<std::pair<int, bool>> rule;
        for (int i = 0; i < b; i++)
            for (int j = i + 1; j < b; j++)
                rule.emplace_back(edge_to_int({h[i], h[j]}), false);
        _sat.add_rule(rule);
    }
}

std::string ramsey_number::clause_name(int i)
{
    auto p = int_to_edge(i);
    return "[" + std::to_string(p.first) + ", " + std::to_string(p.second) + "]";
}

void ramsey_number::write_to(std::string filename)
{
    std::map<int, std::set<int>> edges;
    for (auto clause: _latest_model)
    {
        auto p = int_to_edge(clause);
        edges[p.first].insert(p.second);
        edges[p.second].insert(p.first);
    }
    std::ofstream file(filename);
    for (int i = 0; i < _m; ++i)
    {
        file << i << ": ";
        for (int j : edges[i])
            file << j << " ";
        file << "\n";
    }
    file.close();
}