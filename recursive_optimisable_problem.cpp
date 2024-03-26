//
// Created by Luke Pebody on 26/03/2024.
//

#include <fstream>

#include "recursive_optimisable_problem.h"

#include "logger.h"

recursive_optimisable_problem::recursive_optimisable_problem(int m,
                                                             const std::string& problem_type):
        _m(m), _k(), _sat(), _problem_type(problem_type) {
    logger() << "Creating " << _problem_type << " for m = " << m << "...";
}

void recursive_optimisable_problem::set_initial_marks(const std::vector<std::pair<int, bool>> &initial_marks)
{
    logger() << "Marking " << initial_marks.size() << " marks";
    for (auto mk: initial_marks)
        _sat.mark(mk.first, mk.second);
}

bool recursive_optimisable_problem::start()
{
    bool initially_solvable = solvable();
    std::string maybe_not = initially_solvable ? "" : "not ";
    logger() << "" << _problem_type << " for m = " << _m << " was " << maybe_not << "solvable initially";
    if (!initially_solvable) {
        bool fixed = false;
        for (int i = num_clauses() - 1; i >= 0; --i) {
            if (!_sat.is_marked(i))
                continue;
            bool p = _sat.marked_true(i);
            std::string maybe_text = p ? " - was true, so trying false" : " - was false, so moving on.";
            logger() << "Unmarking " << clause_name(i) << maybe_text;
            _sat.unmark(i);
            if (p) {
                _sat.mark(i, false);
                if (solvable()) {
                    fixed = true;
                    break;
                }
                else
                    _sat.unmark(i);
            }

        }
        if (!fixed)
        {
            logger() << "" << _problem_type << " for m = " << _m << " is not solvable.";
            return false;
        }
        logger() << "" << _problem_type << " for m = " << _m << " is solvable.";
    }
    return true;
}

bool recursive_optimisable_problem::optimise()
{
    for (int i = 0; i < num_clauses(); ++i)
    {
        if (_sat.is_marked(i))
            continue;
        if (_latest_model.find(i) != _latest_model.end())
        {
            _sat.mark(i, true);
        }
        else
        {
            _sat.mark(i, true);
            if (!solvable())
            {
                _sat.mark(i, false);
            }
        }
    }
    logger() << "" << _problem_type << " for m = " << _m << " is now optimal";
    return true;
}

bool recursive_optimisable_problem::solvable()
{
    auto response = _k.solve(_sat);
    if (response.has_value())
    {
        _latest_model = {response.value()};
        for (auto mk : _sat.get_marks())
            if (mk.second)
                _latest_model.insert(mk.first);
    }
    return response.has_value();
}

std::vector<std::pair<int, bool>> recursive_optimisable_problem::get_marks()
{
    std::vector<std::pair<int, bool>> result;
    int nc = num_clauses();
    for (int i = 0; i < nc; ++i)
        result.emplace_back(i, _latest_model.find(i) != _latest_model.end());
    return result;
}

