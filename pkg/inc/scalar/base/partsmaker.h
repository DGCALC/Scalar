//
// Created by Lucius Schoenbaum on 10/28/21, 3/22/22
//

// Partsmaker
//
// This class hides the parsing string-input constructor from Parts,
// which uses subroutines that are not really relevant to that class.

// Construct Parts from string
// Format:
// <Num>[<Exponent>]
// <Exponent> = E<Num> | e<Num>
// For Num productions, supports:
// string in a binary form 0b... e.g. 0b1010
// string in a hex form 0x... e.g. 0b3f18c9
// string in a decimal form (no leading 0) e.g. 1234
// string in a signed radix 2 form 0b... e.g. 0b01u01u
// optional leading sign, + or -
// optional separators: , _ (comma or underscore)

#pragma once

#include <DGCALC.h>
#include <kyte/convert.h>

class Partsmaker {

public: // fields:

    int64_t n;
    uint64_t m;
    int64_t s;

public: // ctor:

    Partsmaker(std::string strin) {
        // Top level parsing
    }

private: // methods:

    uint64_t get_Num_uint(std::string strin) {
        uint64_t out;
        ;
        return out;
    }

    int64_t get_Num_int(std::string strin) {
        int64_t out;
        ;
        return out;
    }

};