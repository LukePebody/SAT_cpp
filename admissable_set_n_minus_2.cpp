//
// Created by Luke Pebody on 26/03/2024.
//

#include <fstream>

#include "admissable_set_n_minus_2.h"

#include "combinations.h"
#include "logger.h"
#include "tuples.h"

const std::vector<std::vector<std::vector < int>>> pairings{
        {{0, 1}, {2, 3}, {4, 5}},
        {{0, 1}, {2, 4}, {3, 5}},
        {{0, 1}, {2, 5}, {3, 4}},
        {{0, 2}, {1, 3}, {4, 5}},
        {{0, 2}, {1, 4}, {3, 5}},
        {{0, 2}, {1, 5}, {3, 4}},
        {{0, 3}, {1, 2}, {4, 5}},
        {{0, 3}, {1, 4}, {2, 5}},
        {{0, 3}, {1, 5}, {2, 4}},
        {{0, 4}, {1, 2}, {3, 5}},
        {{0, 4}, {1, 3}, {2, 5}},
        {{0, 4}, {1, 5}, {2, 3}},
        {{0, 5}, {1, 2}, {3, 4}},
        {{0, 5}, {1, 3}, {2, 4}},
        {{0, 5}, {1, 4}, {2, 3}}
};

admissable_set_n_minus_2::admissable_set_n_minus_2(int m):
        recursive_optimisable_problem(m, "admissable set (n-2) problem") {
    logger() << "Part 1";
    for (auto c = combinations(m, 4); !(c.finished()); ++c)
        for (int p = 0; p < 4; ++p) {
            int i = c[p];
            std::vector<int> others;
            for (int q = 0; q < 4; ++q)
                if (p != q)
                    others.push_back(c[q]);

            for (int msk = 0; msk < 8; ++msk) {
                std::vector<std::pair<int, bool>> rule;
                for (int q = 0; q < 3; ++q)
                    for (int r = 0; r < 3; ++r)
                        if (q != r) {
                            int t = tuple_to_int(
                                    {{1 + std::min(i, others[q]), 1 + std::max(i, others[q])}, 1 + others[r]});
                            rule.emplace_back(t, ((msk >> r) & 1) == 1);
                        }
                _sat.add_rule(rule);
            }
        }

    logger() << "Part 2";
    for (auto& p: pairings)
        for (auto h = combinations(m, 6); !(h.finished()); ++h) {
            std::vector<std::pair<int, int>> pairs;
            for (auto pi: p)
                pairs.emplace_back(1 + h[pi[0]], 1 + h[pi[1]]);
            for (int msk = 0; msk < 64; ++msk) {
                std::vector<std::pair<int, bool>> rule;

                for (auto pair: pairs)
                    for (int i = 0; i < 6; ++i) {
                        int j = 1 + h[i];
                        if (j != pair.first && j != pair.second) {
                            int t = tuple_to_int({pair, j});
                            rule.emplace_back(t, ((msk >> i) & 1) == 1);
                        }
                    }
                _sat.add_rule(rule);
            }
        }
}

int admissable_set_n_minus_2::num_clauses() const
{
    return (_m * (_m - 1) * (_m - 2)) / 2;
}

std::string admissable_set_n_minus_2::clause_name(int i)
{
    auto tup = int_to_tuple(i);
    return "[" + std::to_string(tup.first.first) + ", " + std::to_string(tup.first.second) + "]:" + std::to_string(tup.second);
}


void admissable_set_n_minus_2::write_to(std::string filename)
{
    std::map<std::pair<int, int>, std::vector<int>> vectors;
    for (int i = 0; i < _m; ++i)
        for (int j = i + 1; j < _m; ++j)
        {
            std::vector<int> v;
            for (int k = 0; k < _m; ++k)
                v.push_back((k == i || k == j) ? 0 : 2);
            vectors[{i + 1, j + 1}] = v;
        }

    for (auto clause : _latest_model)
    {
        auto tup = int_to_tuple(clause);
        vectors[tup.first][tup.second - 1] = 1;
    }
    std::ofstream out(filename);
    for (auto& [pair, v]: vectors)
    {
        for (auto& i: v)
            out << i << " ";
        out << std::endl;
    }
    out.close();
}