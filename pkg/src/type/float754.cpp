//
// Created by Lucius Schoenbaum on 3/22/22.
//

#include <scalar/types/float754.h>

float754 operator""_f754(const char * lit, size_t n) {
    return float754(strtof(lit, nullptr));
}

float754 operator""_f754(long double ain) {
    return float754(static_cast<float>(ain));
}

std::ostream& operator<<(std::ostream & os, const float754 & obj) {
    os << obj.str();
    return os;
}