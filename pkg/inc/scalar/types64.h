//
// Created by Lucius Schoenbaum on 3/28/22.
//

/*
 * A "complete" set of 64-bit types:
 *
 * B64, B32, B16, Bbyte, Bool
 * N64, N32, N16, Nbyte
 * U64, U32, U16, Ubyte
 * F64, F32
 *
 * For other types, see ()()() <----[wip: low-precision, arb-precision, arb-precision ints, ...]
 *
 * GOAL:
 * ..., B<n>, ..., B64, B32, B16, Bbyte, Bool
 * ..., N<n>, ..., N64, N32, N16, Nbyte
 * ..., U<n>, ..., U64, U32, U16, Ubyte
 * ..., F<n>, ..., F64, F32, F16, Fbyte
 *
 * At that point, I can consider it done, but it requires arb-arithmetic.
 *
 */

#pragma once

#include <types/B_logic.h>
#include <types/integers.h>
#include <scalar/754.h>
