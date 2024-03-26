//
// Created by Luke Pebody on 26/03/2024.
//

#include <fstream>
#include <iostream>

#include "kissat.h"
#include "logger.h"

std::optional<std::set<int>> kissat::solve(const problem& p)
{
    auto dimacs_and_variables = p.dimacs_and_variables();
    auto dimacs = dimacs_and_variables.first;
    auto variables = dimacs_and_variables.second;

    // create a file containing the clauses in dimacs format
    std::ofstream file;
    file.open("temp.cnf");
    file << "p cnf " << variables.size() << " " << dimacs.size() << std::endl;
    for (auto& clause: dimacs)
    {
        for (auto& literal: clause)
        {
            file << literal << " ";
        }
        file << "0" << std::endl;
    }
    file.close();

    // call kissat
    int z = system("kissat temp.cnf > temp.out 2> temp.err");

    if (z == 5120)
    {
        // not solvable
        return {};
    }

    if (z == 2560)
    {
        // solvable
        std::set<int> result;
        std::ifstream infile("temp.out");
        std::string line;
        while (std::getline(infile, line))
        {
            if (line[0] == 'v')
            {
                std::istringstream iss(line);
                std::string v;
                while (iss >> v)
                {
                    if (v == "v")
                        continue;
                    int i = std::stoi(v);
                    if (i > 0)
                        result.insert(variables[i - 1]);
                }
            }
        }
        return result;
    }

    logger() << "Kissat returned " << z;
    return {};
}