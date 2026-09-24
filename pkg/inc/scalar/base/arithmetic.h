//
// Created by Lucius Schoenbaum on 10/27/21.
//

/*
 *
 * Arithmetic
 *
 * Static methods to perform computer arithmetic
 * on general width fields.
 *
 *
 */

#pragma once

#include <kyte/field.h>

template <DGCALC::logsize_t logsize>
struct Arithmetic {

    using field = Kyte::field<logsize>;
    using dfield = Kyte::field<logsize+1>;

    // shamt??? did I not write down what that was supposed to be? :P

    // iinverse: integer inverse 1/x.
    // Value is calculated to precision equal
    // to the implied precision of the input,
    // with round-to-nearest-even rounding policy
    // based on the supposition that ain continues as a string of zeros.
    // 0 is returned iff input is 0.
    static field iinverse(field ain, size_t shamt) {
        // Let a denote value ain.
        // handle case ain == 0: 0 is returned iff input is 0
        if (ain == 0) return 0;
        //\\ a != 0.
        // field to compute Remainder(1/x), with enough room to round
        dfield R(ain);
        // field to keep a, as dfield for now (could be more efficient)
        dfield D(ain);
        // field for a saved negative D
        dfield Dn = D.negate_bit();
        // the true width of a (min: 1, max: 64)
        // min achieved iff a is 1 (coming from Parts, this would be a
        // very low-precision situation, but still a case we must accomodate)
        size_t trueW = D.truewidth_bit();
        // fields for 1/x, stored as a negative field Qn and positive field Qp
        // Q will be Qp - Qn
        dfield Qp, Qn;
        // accumulator for shifts and running value of shift
        size_t S = 127, s;
        // final form
        uint64_t out;

        // iteration: shift and subtract until S is small enough
        // work until a's width is achieved, along with two more bits.
        // (If working with IEEE-754, this will always be the same.)
        while (127 - S < trueW + 2) {

        }
        s = R.FSLEFT();


        // finalize, round
        out = R.upper();
        // right shift it the appropriate amount todo
        // round todo

        return out;
    }

    // integer square root,
    // to highest possible precision
    // using the implied precision of the input
    static uint64_t sqrt(uint64_t ain) {
        field X(ain);
        return 1234;
    }

    // multiply by square root of 2,
    // preserving the implied precision
    // of the input
    static uint64_t mul_sqrt2(uint64_t ain) {
        static const constexpr uint64_t sqrt2 = 1414213562373095048; // 8 throws an annoying warning
        // todo
        return 1234;
    }

};

