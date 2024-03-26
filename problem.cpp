//
// Created by Luke Pebody on 25/03/2024.
//

#include "problem.h"

void problem::add_rule(const std::__1::vector<std::pair<int, bool>>& rule)
{
    int rule_number = _rules.size();
    _rules.emplace_back(rule);
    for (auto& atom : rule)
    {
        while (_num_atoms <= atom.first)
        {
            _marks.emplace_back();
            _atom_to_rules.emplace_back();
            _variables.insert(_num_atoms++);
        }
        if (atom.second)
            _atom_to_rules[atom.first].first.push_back(rule_number);
        else
            _atom_to_rules[atom.first].second.push_back(rule_number);
    }
    _still_to_solve.insert(rule_number);
    _satisfying_counts.push_back(0);
}

void problem::mark(int atom, bool set_true)
{
    while (atom >= _marks.size())
    {
        _marks.emplace_back();
        _atom_to_rules.emplace_back();
        _variables.insert(_num_atoms++);
    }
    auto& mit = _marks[atom];
    if (mit.has_value())
    {
        if (mit.value() == set_true)
            return;
        unmark(atom);
    }
    _marks[atom] = set_true;
    _variables.erase(atom);

    for (int rule: set_true ? _atom_to_rules[atom].first : _atom_to_rules[atom].second)
    {
        ++_satisfying_counts[rule];
        _still_to_solve.erase(rule);
    }
}

void problem::unmark(int atom)
{
    auto & mit = _marks[atom];
    if (!mit.has_value())
        return;

    for (int rule: mit.value() ? _atom_to_rules[atom].first : _atom_to_rules[atom].second )
    {
        --_satisfying_counts[rule];
        if (_satisfying_counts[rule] == 0)
            _still_to_solve.insert(rule);
    }
    _variables.insert(atom);
    _marks[atom] = {};
}

std::pair<std::vector<std::vector<int>>, std::vector<int>> problem::dimacs_and_variables() const {
    std::map<int, int> varlookup;
    int i = 1;
    for (auto& v: _variables)
        varlookup[v] = i++;

    std::vector<std::vector<int>> rules;
    for (auto& r: _still_to_solve)
    {
        std::vector<int> dimacs_rule;
        for (auto& element: _rules[r])
        {
            auto vit = varlookup.find(element.first);
            if (vit != varlookup.end())
                dimacs_rule.push_back((element.second ? 1 : -1) * vit->second);
        }
        rules.push_back(dimacs_rule);
    }
    return std::make_pair(rules, std::vector<int>(_variables.begin(), _variables.end()));
}

bool problem::is_marked(int atom)
{
    if (atom >= _marks.size())
        return false;
    return _marks[atom].has_value();
}

bool problem::marked_true(int atom)
{
    if (atom >= _marks.size())
        return false;
    return _marks[atom].has_value() && _marks[atom].value();
}

std::vector<std::pair<int, bool>> problem::get_marks() {
    std::vector<std::pair<int, bool>> result;
    for (int i = 0; i < _marks.size(); ++i)
    {
        if (_marks[i].has_value())
            result.emplace_back(i, _marks[i].value());
    }
    return result;
}
