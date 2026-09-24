//
// Created by Lucius Schoenbaum on 3/29/22.
//

#include <scalar/754.h>

double754 operator""_F64(const char * lit, size_t n) {
    return double754(strtod(lit, nullptr));
}

double754 operator""_F64(unsigned long long int i) {
    return double754(i);
}

double754 operator""_F64(long double ain) {
    return double754(static_cast<double>(ain));
}

float754 operator""_F32(const char * lit, size_t n) {
    return float754(strtof(lit, nullptr));
}

float754 operator""_F32(unsigned long long int i) {
    return float754(i);
}

float754 operator""_F32(long double ain) {
    return float754(static_cast<float>(ain));
}
