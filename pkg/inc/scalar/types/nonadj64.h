//
// Created by Lucius Schoenbaum on 9/28/21, 3/22/22
//

/*
 * posit
 * 
 * todo I think this is quite aged at this point. 11/29/22
 * 
 */

/*
 * Notes 3/22/22:
 * Interesting. What is it that makes a parts into a nonadj64?
 * It's just the limits.
 * So it's all ---- all! ---- in the conversion from an
 * adequately wide Parts,
 * back to a nonadj64.
 *
 *
 */

#pragma once

#include <types/DGCALC.h>
#include <scalar/base/parts.h>


struct nonadj64 {
    template <typename PP, typename T, size_t M>
    friend class Super;
public: // static fields:

    // todo super interop
    static const constexpr int dimension = 1;

private: // fields:

    Parts<6> data;

public: // ctor:

    explicit nonadj64(double dbl = 0):
            data(Parts<6>(dbl))
    {}
    explicit nonadj64(const std::string & str):
        data(Parts<6>(str))
    {}

    explicit nonadj64(Parts<6> parts):
        data(parts)
    {}

public: // copy:

    nonadj64(const nonadj64 & din) {
        this->data = din.data;
    }

    nonadj64 & operator=(const nonadj64 & rhs) {
        if (this == &rhs) return *this;
        this->data = rhs.data;
        return *this;
    }

public: // dtor:

    ~nonadj64() = default;

public: // static methods:

    static nonadj64 zero() {
        return nonadj64(0);
    }

    static nonadj64 unit() {
        return nonadj64(1);
    }

public: // API:

    Parts<6> parts() const {
        return data;
    }

private: // Super-only:

    // used by Super for l2-norm
    friend nonadj64 operator^(const nonadj64 & ain, int pow) {
        return ain*ain;
    }
	
	[[nodiscard]] double754 ones() const {
		return unit();
	}

    // Bracket notation
    nonadj64 & operator[](size_t index) {
        return *this;
    }

    const nonadj64 & operator[](size_t index) const {
        return *this;
    }

    nonadj64 & operator[](IPoint index) {
        return *this;
    }

    const nonadj64 & operator[](IPoint index) const {
        return *this;
    }

public: // artifacts:

    // todo Careful, I'm not sure a = b <=> a.parts = b.parts.
    bool operator==(const nonadj64 & rhs) const {
        if (this == &rhs) return true;
        return (data == rhs.data);
    };

    bool operator!=(const nonadj64 & rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const nonadj64 & rhs) const {
        return (data < rhs.data);
    }

    // todo they all come from <
//    bool operator>(const nonadj64 & rhs) const {
//        return (data > rhs.data);
//    }

    bool operator<=(const nonadj64 & rhs) const {
        return !(*this > rhs);
    }

    bool operator>=(const nonadj64 & rhs) const {
        return !(*this < rhs);
    }

    // compound +
    nonadj64 & operator+=(const nonadj64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a+b);
        return *this;
    }
    // compound -
    nonadj64 & operator-=(const nonadj64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a-b);
        return *this;
    }
    // compound *
    nonadj64 & operator*=(const nonadj64 & rhs) {
        Parts64B2 a = parts();
        Parts64B2 b = rhs.parts();
        *this = nonadj64(a*b);
        return *this;
    }
    // compound /
    nonadj64 & operator/=(const nonadj64 & rhs) {
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
    friend nonadj64 operator+(const nonadj64 & lhs, const nonadj64 & rhs) {
        nonadj64 out = lhs;
        out += rhs;
        return out;
    }
    friend nonadj64 operator-(const nonadj64 & lhs, const nonadj64 & rhs) {
        nonadj64 out = lhs;
        out -= rhs;
        return out;
    }
    friend nonadj64 operator*(const nonadj64 & lhs, const nonadj64 & rhs) {
        nonadj64 out = lhs;
        out *= rhs;
        return out;
    }
    friend nonadj64 operator/(const nonadj64 & lhs, const nonadj64 & rhs) {
        nonadj64 out = lhs;
        out /= rhs;
        return out;
    }

    nonadj64 sqrt() const {
        Parts64B2 a = parts();
        nonadj64 out = nonadj64(a.sqrt());
        return out;
    }

    nonadj64 abs() const {
        Parts64B2 a = parts();
        nonadj64 out = nonadj64(a.abs());
        return out;
    }

    static nonadj64 dx() {
        // todo: replace with actual smallest for nonadj64
        return nonadj64(1.0e-40);
    }

    static nonadj64 tiny() {
        return nonadj64(1.0e-40);
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

