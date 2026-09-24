//
// Created by Lucius Schoenbaum on 3/22/22.
//

#include <scalar/types/double754.h>

double754 operator""_d754(const char * lit, size_t n) {
    return double754(strtod(lit, nullptr));
}

double754 operator""_d754(long double ain) {
    return double754(static_cast<double>(ain));
}

std::ostream& operator<<(std::ostream & os, const double754 & obj) {
    os << obj.str();
    return os;
}

