//
// Created by Lucius Schoenbaum on 9/28/21.
//

#pragma once

#include <DGCALC.h>
#include <kyte/convert.h>
#include <types/machinetype.h>
#include <types/viz.h>

#include <cmath> // std::sqrt, std::abs, std::sin, std::cos, std::exp, std::log

struct float754: MachineType<float> {
    template <typename PP, typename T, size_t size, size_t cosize, size_t prosize>
    friend class Super;

    using T = float754;

public: // constants:

    // Note: due to hidden bit, the length of significand is precision minus one.
    static constexpr int precision = 24;

public: // ctor:

    explicit float754(): MachineType() {}

    explicit float754(float in): MachineType(in) {}

    // use MachineType's string ctor
    explicit float754(const std::string s): MachineType(s) {
    }

//    explicit float754(Parts64B2 parts): data(0) {
//        // todo
//    }

    //) This is possible but makes code a lot spookier.
    //explicit operator double() const {return data;}

public: // copy:

    // from MachineType

public: // dtor:

    ~float754() = default;

public: // static methods:

    static float754 dx() {
        // this is the smallest not counting denormals
        return float754(std::numeric_limits<float>::min());
    }

    static float754 tiny() {
        return float754(1.0e-40);
    }

    static float754 pi() {
        return float754(M_PI);
    }

public: // static methods:

    // Here and there, float754 can inherit from MachineType,
    // but overall it's a very annoying situation, that the inheritance
    // does so little to reduce this boilerplate code.

    static float754 zero() {
        return float754(0);
    }

    static float754 unit() {
        return float754(1);
    }

    // use these with T::sqrt(x) or float754::sqrt(x)
    static float754 sqrt(float754 ain) {
        return float754(std::sqrt(ain.data));
    }

    static float754 abs(float754 ain) {
        return float754(std::abs(ain.data));
    }

    // T::neg(x)
    static float754 neg(float754 ain) {
        return float754(-ain.data);
    }

    // T::inv(x)
    // This falls back on the somewhat crazy notation "1/x" for doubles.
    static float754 inv(float754 ain) {
        return float754(1/ain.data);
    }

    // T::rem(x, y)
    static float754 rem(float754 ain, float754 bin) {
        return float754(remainder(ain.data, bin.data));
    }

    // T::mod(x, y)
    static float754 mod(float754 ain, float754 bin) {
        return rem(ain, bin);
    }

    // T::sin(x)
    static float754 sin(float754 ain) {
        return float754(std::sin(ain.data));
    }

    // T::cos(x)
    static float754 cos(float754 ain) {
        return float754(std::cos(ain.data));
    }

    // T::exp(x)
    static float754 exp(float754 ain) {
        return float754(std::exp(ain.data));
    }

    // T::log(x)
    static float754 log(float754 ain) {
        return float754(std::log(ain.data));
    }

    // T::ln(x)
    static float754 ln(float754 ain) {
        return float754::log(ain);
    }

    static float754 floor(float754 ain) {
        return float754(std::floor(ain.data));
    }

    static float754 ceil(float754 ain) {
        return float754(std::ceil(ain.data));
    }

    template <typename itype>
    static float754 binom(itype n, itype k) {
        float754 out = unit();
        // because of the recursion,
        // we should be mindful to bound the input,
        // or else think very hard (and perhaps erroneously) about it.
        // These checks will go through the pipeline very fast.
        if (n < 0 || k < 0 || k > n)
            return zero();
        if (k == 0)
            return unit();
        if (k > n/2)
            return binom(n,n - k);
        for (int i = 0; i < k; ++i) {
            out *= float754(n - i)/float754(k - i);
        }
        return out;
    }

public: // API, mirroring static:

    // Here and there float754 can inherit from MachineType,
    // but overall it's a very annoying situation, that the inheritance
    // does so little to reduce this boilerplate code.

    [[nodiscard]] float754 sqrt() const {
        return float754::sqrt(*this);
    }

    [[nodiscard]] float754 abs() const {
        return float754::abs(*this);
    }

    [[nodiscard]] float754 neg() const {
        return float754::neg(*this);
    }

    [[nodiscard]] float754 inv() const {
        return float754::inv(*this);
    }

    [[nodiscard]] float754 rem(float754 bin) const {
        return float754::rem(*this, bin);
    }

    [[nodiscard]] float754 mod(float754 bin) const {
        return float754::mod(*this, bin);
    }

    [[nodiscard]] float754 sin() const {
        return float754::sin(*this);
    }

    [[nodiscard]] float754 cos() const {
        return float754::cos(*this);
    }

    [[nodiscard]] float754 exp() const {
        return float754::exp(*this);
    }

    [[nodiscard]] float754 log() const {
        return float754::log(*this);
    }

    [[nodiscard]] float754 ln() const {
        return float754::ln(*this);
    }

    [[nodiscard]] float754 floor() const {
        return float754::floor(*this);
    }

    [[nodiscard]] float754 ceil() const {
        return float754::ceil(*this);
    }

public: // API:

//    Parts64B2 parts() const {
//        return Parts64B2(data);
//    }

private: // Super-only:

    // used by Super for l2-norm
    friend float754 operator^(const float754 & ain, int pow) {
        return ain*ain;
    }
	
	[[nodiscard]] float754 ones() const {
		return unit();
	}

    [[nodiscard]] float754 max() const {
        return *this;
    }

    [[nodiscard]] float754 min() const {
        return *this;
    }

public: // Super-related:

    // multiplication T x T --> T
    // trivial dot product.
    friend float754 operator%(const float754 & lhs, const float754 & rhs) {
        return lhs*rhs;
    }

    // Bracket notation
    float754 & operator[](size_t index) {
        return *this;
    }

    const float754 & operator[](size_t index) const {
        return *this;
    }

    float754 & operator[](DGCALC::IPoint<2> index) {
        return *this;
    }

    const float754 & operator[](DGCALC::IPoint<2> index) const {
        return *this;
    }


public: // artifacts:

    // typ. boolean-returning operators: inherited from MachineType

    // compound +
    float754 & operator+=(const float754 & rhs) {
        data += rhs.data;
        return *this;
    }
    // compound -
    float754 & operator-=(const float754 & rhs) {
        data -= rhs.data;
        return *this;
    }
    // compound *
    float754 & operator*=(const float754 & rhs) {
        data *= rhs.data;
        return *this;
    }
    // compound /
    float754 & operator/=(const float754 & rhs) {
        data /= rhs.data;
        return *this;
    }
    /*
     * Reminder: when you get to the binary operators,
     * stop returning references.
     * Adding "friend" makes them ordinary functions,
     * which can nevertheless modify private members.
     */
    friend float754 operator+(const float754 & lhs, const float754 & rhs) {
        float754 out = lhs;
        out += rhs;
        return out;
    }
    friend float754 operator-(const float754 & lhs, const float754 & rhs) {
        float754 out = lhs;
        out -= rhs;
        return out;
    }
    friend float754 operator*(const float754 & lhs, const float754 & rhs) {
        float754 out = lhs;
        out *= rhs;
        return out;
    }
    friend float754 operator/(const float754 & lhs, const float754 & rhs) {
        float754 out = lhs;
        out /= rhs;
        return out;
    }

    // todo
//    Parts parts() const {
//        return Parts(data);
//    }

public: // printing

    // print in digest form: (whole part).xx (dec)
    // can be used for percentages: yy.xx
    std::string str_di() const {
        char buf[24];
        snprintf(buf, 24, "%.2f", data);
        return {buf};
    }

    // print 94% of full precision value
    // 100% of total precision of float type:
    // log10(2^24) = 24*log(2)/log(10) ≈ 7.22
    // If we take 7 flat, and solve for the %age P, we find:
    // P = 7*log(10)/(24*log(2)) ===> P > 96.8%
    // So 7 is satisfactory.
    // see notes in double754.h
    std::string str_94() const {
        char buf[24];
        snprintf(buf, 24, "%+.7e", data);
        return {buf};
    }

    std::string str_dat() const {
        return str_94();
    }

    std::string str() const {
        return str_std();
    }

public: // other printing methods:

    std::string str_std() const {
        return std::to_string(data);
    }

    std::string dat() const {
        return str_94();
    }

    std::string str_parts(bool with_bin = true) const {
        std::string out;
        int fpc = fpclassify(data);
        switch (fpc) {
            case (FP_INFINITE):
                out += "infinite:";
                break;
            case (FP_NAN):
                out += "nan:";
                break;
            case (FP_NORMAL):
                out += "normal:";
                break;
            case (FP_SUBNORMAL):
                out += "subnormal:";
                break;
            case (FP_ZERO):
                out += "zero:";
                break;
            default:
                out += "classify:OTHER?:";
        }
//        out += parts().str();
        if (with_bin) {
            out += "\n" + str_bin();
        }
        return out;
    }

    std::string str_hex() const {
        return Kyte::Convert::tohex(data);
    }

    std::string str_bin() const {
        return Kyte::Convert::tobin(data);
    }

public: // viz:

    // vizualization method
    //) viz() methods are smoky (generate files).
    void viz() const {
        // todo?
    }

    // visualization intermediate representation
    //) Utility for higher viz() methods.
    [[nodiscard]]
    viz_t viz_ir() const {
        return viz_t(data);
    }

};

float754 operator""_f754(const char * lit, size_t);

float754 operator""_f754(long double);

std::ostream& operator<<(std::ostream & os, const float754 & obj);
