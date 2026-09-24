//
// Created by Lucius Schoenbaum on 9/28/21.
//

/*
 * Todo
 * - sin, cos, ...math
 * - move into source file
 *
 */

#pragma once

#include <DGCALC.h>
#include <kyte/convert.h>
#include <types/machinetype.h>
// todo this dependency should only be in the .cpp source!!!!!!!!!!!!!
#include <types/viz.h>
#include <cmath> // std::sqrt, std::abs, std::exp, std::log, std::sin, std::cos
#include <cstdio> // ????

struct double754: MachineType<double> {
    template <typename PP, typename T, size_t size, size_t cosize, size_t prosize>
    friend class Super;

    using T = double754;

public: // static fields:

    // Note: due to hidden bit, the length of significand is precision minus one.
    static constexpr int precision = 53;

public: // types:

    using Undertype = double;

public: // ctor:

    explicit double754(): MachineType() {}

    explicit double754(double in): MachineType(in) {}

    // use MachineType's string ctor
    explicit double754(std::string s): MachineType(s) {}

//    explicit double754(Parts64B2 parts): data(0) {
//        // todo
//    }

    //) This is possible but makes code a lot spookier.
    //explicit operator double() const {return data;}

public: // copy:

    // from MachineType

public: // dtor:

    ~double754() = default;

public: // static methods:

    static double754 dx() {
        // this is the smallest not counting denormals
        return double754(std::numeric_limits<double>::min());
    }

    static double754 tiny() {
        return double754(1.0e-40);
    }

    static double754 pi() {
        return double754(M_PI);
    }

public: // static methods:

    // Here and there, double754 can inherit from MachineType,
    // but overall it's a very annoying situation, that the inheritance
    // does so little to reduce this boilerplate code.

    static double754 zero() {
        return double754(0);
    }

    static double754 unit() {
        return double754(1);
    }

    // T::sqrt(x)
    static double754 sqrt(double754 ain) {
        return double754(std::sqrt(ain.data));
    }

    // T::abs(x)
    static double754 abs(double754 ain) {
        return double754(std::abs(ain.data));
    }

    // T::neg(x)
    static double754 neg(double754 ain) {
        return double754(-ain.data);
    }

    // T::inv(x)
    // This falls back on the somewhat crazy notation "1/x" for doubles.
    static double754 inv(double754 ain) {
        return double754(1/ain.data);
    }

    // T::rem(x, y)
    static double754 rem(double754 ain, double754 bin) {
        return double754(remainder(ain.data, bin.data));
    }

    // T::mod(x, y)
    static double754 mod(double754 ain, double754 bin) {
        return double754::rem(ain, bin);
    }

    // T::sin(x)
    static double754 sin(double754 ain) {
        return double754(std::sin(ain.data));
    }

    // T::cos(x)
    static double754 cos(double754 ain) {
        return double754(std::cos(ain.data));
    }

    // T::exp(x)
    static double754 exp(double754 ain) {
        return double754(std::exp(ain.data));
    }

    // T::log(x)
    static double754 log(double754 ain) {
        return double754(std::log(ain.data));
    }

    // T::ln(x)
    static double754 ln(double754 ain) {
        return double754::log(ain);
    }

    static double754 floor(double754 ain) {
        return double754(std::floor(ain.data));
    }

    static double754 ceil(double754 ain) {
        return double754(std::ceil(ain.data));
    }

    template <typename itype>
    static double754 binom(itype n, itype k) {
        double754 out = unit();
            // because of the recursion,
            // we should be mindful to bound the input,
            // or else think very hard (and perhaps erroneously) about it.
            // These checks should go through the pipeline very fast.
            if (n < 0 || k < 0 || k > n)
                return zero();
            if (k == 0)
                return unit();
            if (k > n/2)
                return binom(n,n - k);
            for (int i = 0; i < k; ++i) {
                out *= double754(n - i)/double754(k - i);
            }
            return out;
    }

public: // API, mirroring static:

    // Here and there, double754 can inherit from MachineType,
    // but overall it's a very annoying situation, that the inheritance
    // does so little to reduce this boilerplate code.

    [[nodiscard]] double754 sqrt() const {
        return double754::sqrt(*this);
    }

    [[nodiscard]] double754 abs() const {
        return double754::abs(*this);
    }

    [[nodiscard]] double754 neg() const {
        return double754::neg(*this);
    }

    [[nodiscard]] double754 inv() const {
        return double754::inv(*this);
    }

    [[nodiscard]] double754 rem(double754 bin) const {
        return double754::rem(*this, bin);
    }

    [[nodiscard]] double754 mod(double754 bin) const {
        return double754::mod(*this, bin);
    }

    [[nodiscard]] double754 sin() const {
        return double754::sin(*this);
    }

    [[nodiscard]] double754 cos() const {
        return double754::cos(*this);
    }

    [[nodiscard]] double754 exp() const {
        return double754::exp(*this);
    }

    [[nodiscard]] double754 log() const {
        return double754::log(*this);
    }

    [[nodiscard]] double754 ln() const {
        return double754::ln(*this);
    }

    [[nodiscard]] double754 floor() const {
        return double754::floor(*this);
    }

    [[nodiscard]] double754 ceil() const {
        return double754::ceil(*this);
    }

private: // Super-only:

    // used by Super for l2-norm
    friend double754 operator^(const double754 & ain, int pow) {
        // todo shouldn't this do something natural for values of pow?
        return ain*ain;
    }
	
	[[nodiscard]] double754 ones() const {
		return unit();
	}

    [[nodiscard]] double754 max() const {
        return *this;
    }

    [[nodiscard]] double754 min() const {
        return *this;
    }

public: // Super-related:

    // multiplication T x T --> T
    // trivial dot product.
    friend double754 operator%(const double754 & lhs, const double754 & rhs) {
        return lhs*rhs;
    }

    // Bracket notation
    double754 & operator[](size_t index) {
        return *this;
    }

    const double754 & operator[](size_t index) const {
        return *this;
    }

    double754 & operator[](DGCALC::IPoint<2> index) {
        return *this;
    }

    const double754 & operator[](DGCALC::IPoint<2> index) const {
        return *this;
    }

public: // artifacts:

    // typ. boolean-returning operators: inherited from MachineType

    // compound +
    double754 & operator+=(const double754 & rhs) {
        data += rhs.data;
        return *this;
    }
    // compound -
    double754 & operator-=(const double754 & rhs) {
        data -= rhs.data;
        return *this;
    }
    // compound *
    double754 & operator*=(const double754 & rhs) {
        data *= rhs.data;
        return *this;
    }
    // compound /
    double754 & operator/=(const double754 & rhs) {
        data /= rhs.data;
        return *this;
    }
    /*
     * Reminder: when you get to the binary operators,
     * stop returning references.
     * Adding "friend" makes them ordinary functions,
     * which can nevertheless modify private members.
     */
    friend double754 operator+(const double754 & lhs, const double754 & rhs) {
        double754 out = lhs;
        out += rhs;
        return out;
    }
    friend double754 operator-(const double754 & lhs, const double754 & rhs) {
        double754 out = lhs;
        out -= rhs;
        return out;
    }
    friend double754 operator*(const double754 & lhs, const double754 & rhs) {
        double754 out = lhs;
        out *= rhs;
        return out;
    }
    friend double754 operator/(const double754 & lhs, const double754 & rhs) {
        double754 out = lhs;
        out /= rhs;
        return out;
    }

    // todo
//    Parts parts() const {
//        return Parts(data);
//    }

public: // printing:

    // print in digest form: (whole part).xx (dec)
    // can be used for percentages: yy.xx
    std::string str_di() const {
        char buf[24];
        snprintf(buf, 24, "%.2f", data);
        return {buf};
    }

    // print 94% of full precision value
    // 95% of total precision of double type:
    // log10(2^52) = 53*log(2)/log(10) ≈ 15.95
    // 15.95*0.95 = 15.1 (decimal symbols, or decimal precision)
    // If we take 15 flat, and solve for the %age P, we find:
    // P = 15*log(10)/(53*log(2)) ===> P = 94.01%
    // using base 16 and 14 symbols (precision 13), as in default %a format
    // on my machine,
    // P = 13*log(16)/(53*log(2)) = 13*4 / 53 ===> P = 100% (exact).
    // So +.13a = %+a is the "most precise" format.
    // So we can do better if we use the %a format, but
    // - I have observed compatibility issues with this format,
    // and string pasta in this method would impact performance.
    // - The remaining 6% of precision (from 94%) is safe to discard,
    // due to accumulated round-off error.
    // In a (rare) situation where more than 15 decimal places of
    // precision is needed, it is suggested that it is probable that
    // using a wide precision scalar type, rather than double,
    // would give better results.
    // Based on the above, I define this method as follows,
    // as it must be defined for *all* scalars in Scalar:
    // - it provides at least 94% of total precision.
    // - it provides output in decimal scientific notation:
    // that is, as long as the value is not exceptional,
    // [+-]1.xxxx....xxxe[+-]xx...xx
    // where x are decimal char symbols.
    std::string str_94() const {
        char buf[24];
        snprintf(buf, 24, "%+.15e", data);
        return {buf};
    }

    std::string str_dat() const {
        return str_94();
    }

    std::string str() const {
        return str_std();
    }

public: // other printing methods:

    // print standard format (usu. ~10-13 dec digits)
    std::string str_std() const {
        return std::to_string(data);
    }

    // todo deprecated?
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
        // todo
//        out += parts().str();
        if (with_bin) {
            out += "\n" + str_bin();
        }
        return out;
    }

    // as data: hex
    std::string str_hex() const {
        return Kyte::Convert::tohex(data);
    }

    // as data: binary
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

public: // miscellaneous:

    // todo this doesn't belong here any more...remove to a DGCALC app.

    // The exact result is -0.8273960599...
    // Example due to Rump [cite] todo
    static double example_Rump_double() {
        double out;
        double a = 77617.0f;
        double b = 33096.0f;
        double b2, b4, b6, b8, a2, firstexpr;
        b2 = b*b;
        b4 = b2*b2;
        b6 = b4*b2;
        b8 = b4*b4;
        a2 = a*a;
        firstexpr = 11*a2*b2-b6-121*b4-2;
        out = 333.75*b6 + a2*firstexpr + 5.5*b8 + (a/(2.0*b));
        return out;
    }

};

double754 operator""_d754(const char * lit, size_t);

double754 operator""_d754(long double);

std::ostream& operator<<(std::ostream & os, const double754 & obj);

