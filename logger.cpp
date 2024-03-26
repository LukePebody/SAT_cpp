//
// Created by Luke Pebody on 26/03/2024.
//

#include <algorithm>
#include "logger.h"

std::string get_time()
{
    char s[1000];
    time_t t = time(NULL);
    struct tm *tmp = localtime(&t);
    strftime(s, sizeof(s), "%c", tmp);
    return s;
}