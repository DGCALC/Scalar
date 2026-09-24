//
// Created by Lucius Schoenbaum on 3/23/22.
//

/*
 * 754.h
 *
 * This header only provides double754 and float754. 
 * Other scalars (if needed) can be included explicitly. 
 *
 * It provides the shorthand F64 and F32,
 * which pair up with N64, N32, U64, U32, etc. from Typology.
 *
 * Integers, B-types (booleans and bitsets), and floats
 * for a standard 64-bit system can be accessed
 * with <scalar/types64.h>.
 *
 */

#pragma once

#include <scalar/types/double754.h>
#include <scalar/types/float754.h>

using F64 = double754;
using F32 = float754;

double754 operator""_F64(const char * lit, size_t);

double754 operator""_F64(unsigned long long int i);

double754 operator""_F64(long double);

float754 operator""_F32(const char * lit, size_t);

float754 operator""_F32(unsigned long long int i);

float754 operator""_F32(long double);
