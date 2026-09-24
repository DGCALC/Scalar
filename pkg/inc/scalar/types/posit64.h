//
// Created by Lucius Schoenbaum on 9/28/21.
//

/*
 * posit
 * 
 * todo I think this is quite aged at this point. 11/29/22
 * 
 */

#pragma once

#include <string>
using std::string;
#include <cmath> // std::sqrt
#include <types/DGCALC.h>
#include <madtests/basis/bit.h>
#include <madtests/basis/parts64b2.h>

// todo verify that all Parts64B2 can handle posit, for all possible values of es.

// log2(64) - 3 = 3
// Recall es(N) = log2(N) - 3
// is the recommendation for size N.
template <int es = 3>
struct posit64 {
    template <typename PP, typename T, size_t M>
    friend class Super;
private: // fields:

    uint64_t data;

    static const constexpr int dimension = 1;

public: // ctor:

    explicit posit64(): data(0) {}

    explicit posit64(const string & str) {
        Parts64B2 pt(str);
        nonadj64 cpy(pt);
        *this = cpy;
    }

    explicit posit64(double dbl): uppr(0), lowr(0) {
        Parts64B2 pt(dbl);
        nonadj64 cpy(pt);
        *this = cpy;
    }

    explicit posit64(Parts64B2 parts): uppr(0), lowr(0) {
        // todo
    }

public: // copy:

    posit64(const posit64 & din) {
        this->data = din.data;
    }

    posit64 & operator=(const posit64 & rhs) {
        if (this == &rhs) return *this;
        this->data = rhs.data;
        return *this;
    }

public: // dtor:

    ~posit64() = default;

public: // static methods:

    static posit64 zero() {
        return posit64(0);
    }

    static posit64 unit() {
        return posit64(1);
    }

public: // API:

    Parts64B2 parts() const {
        Parts64B2 out;
        // todo
        return out;
    }

private: // Super-only:

    // used by Super for l2-norm
    friend posit64 operator^(const posit64 & ain, int pow) {
        return ain*ain;
    }
	
	[[nodiscard]] double754 ones() const {
		return unit();
	}

    // Bracket notation
    posit64 & operator[](size_t index) {
        return *this;
    }

    const posit64 & operator[](size_t index) const {
        return *this;
    }

    posit64 & operator[](IPoint index) {
        return *this;
    }

    const posit64 & operator[](IPoint index) const {
        return *this;
    }

public: // artifacts:

    bool operator==(const posit64 & rhs) const {
        if (this == &rhs) return true;
        return (data == rhs.data);
    };

    bool operator!=(const posit64 & rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const posit64 & rhs) const {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        return (a < b);
    }

    bool operator>(const posit64 & rhs) const {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        return (a > b);
    }

    bool operator<=(const posit64 & rhs) const {
        return !(*this > rhs);
    }

    bool operator>=(const posit64 & rhs) const {
        return !(*this < rhs);
    }

    // compound +
    posit64 & operator+=(const posit64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a+b);
        return *this;
    }
    // compound -
    posit64 & operator-=(const posit64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a-b);
        return *this;
    }
    // compound *
    posit64 & operator*=(const posit64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a*b);
        return *this;
    }
    // compound /
    posit64 & operator/=(const posit64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a/b);
        return *this;
    }
    /*
     * Reminder: when you get to the binary operators,
     * stop returning references.
     * Adding "friend" makes them ordinary functions,
     * which can nevertheless modify private members.
     */
    friend posit64 operator+(const posit64 & lhs, const posit64 & rhs) {
        posit64 out = lhs;
        out += rhs;
        return out;
    }
    friend posit64 operator-(const posit64 & lhs, const posit64 & rhs) {
        posit64 out = lhs;
        out -= rhs;
        return out;
    }
    friend posit64 operator*(const posit64 & lhs, const posit64 & rhs) {
        posit64 out = lhs;
        out *= rhs;
        return out;
    }
    friend posit64 operator/(const posit64 & lhs, const posit64 & rhs) {
        posit64 out = lhs;
        out /= rhs;
        return out;
    }

    posit64 sqrt() const {
        Parts64B2 a = parts();
        nonadj64 out = nonadj64(a.sqrt());
        return out;
    }

    posit64 abs() const {
        Parts64B2 a = parts();
        nonadj64 out = nonadj64(a.abs());
        return out;
    }

    static posit64 dx() {
        // todo: replace with actual smallest for posit64
        return posit64(1.0e-40);
    }

    static posit64 tiny() {
        return posit64(1.0e-40);
    }

public: // printing

    string str_parts(bool with_bin = true) const {
        // todo: this method
        // works like double754 str_parts(),
        // so it prints "everything"
        // and tries to dump all the information it can.
        string out;
        out += parts().str();
        if (with_bin) {
            out += "\n" + str_bin();
        }
    }

    string str_hex() const {
        string out;
        // todo
        return out;
    }

    string str_bin() const {
        string out;
        // todo
        return out;
    }

    double dbl() const {
        return parts().dbl();
    }

public: // viz:

    // vizualization method
    //) viz() methods are smoky (generate files).
    void viz() const {
        // todo?
    }

    // visualization intermediate representation
    //) Utility for higher viz() methods.
    // todo
    [[nodiscard]]
    DGCALC::viz_t viz_ir() const {
        return DGCALC::viz_t(0);
    }

};


#include <madtests/basis/bit_x.h>

