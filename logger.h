//
// Created by Luke Pebody on 26/03/2024.
//

#ifndef ADMISSABLE_SAT_LOGGER_H
#define ADMISSABLE_SAT_LOGGER_H

#include <iostream>
#include <sstream>

std::string get_time();

class logger
{
private:
    std::stringstream _strm;

public:
    logger()
    {
        _strm << get_time() << ": ";
    }

    ~logger()
    {
        std::cerr << _strm.str() << std::endl;
        std::cerr.flush();
    }

    template<typename T>
    logger& operator<<(T t)
    {
        _strm << t;
        return *this;
    }
};

#endif //ADMISSABLE_SAT_LOGGER_H
