//
// Created by Lucius Schoenbaum on 9/28/21.
//

/*
 * complex<T>
 * General Complex-Scalar type based on Scalar type T
 *
 * Morally, complex<T> inherits from T
 * for its real part,
 * but in practice, it is convenient
 * to have references x.re and x.im
 * come as a pair, without ceremony or fuss.
 *
 * Conventionally, refer to a complex type
 * as CT (cf. usci's Fourier)
 *
 */

#pragma once

#include <DGCALC.h>

#include <string>

template <typename T>
struct complex {
    template <typename PP, typename TT, size_t size, size_t cosize, size_t prosize>
    friend class Super;
public: // static fields:

    static constexpr size_t size = T::size;
    static constexpr size_t cosize = T::cosize;
    static constexpr size_t shortsize = T::shortsize;
    static constexpr size_t data_size = T::data_size;
    static constexpr size_t dimension = T::dimension;

public: // types:

    using Undertype = typename T::Undertype;

public: // fields:

    T re;
    T im;

public: // ctor:

    explicit complex(): re(T::zero()), im(T::zero()) {}

    // todo?
//    explicit complex(const string & str): re(T::zero()), im(T::zero()) {
//        // todo this won't quite work - you would have to implement a complex Parts.
//        Parts64B2 pt(str);
//        complex cpy(pt);
//        *this = cpy;
//    }

    explicit complex(T re, T im = T::zero()): re(re), im(im) {}

    explicit complex(Undertype re, Undertype im = 0): re(T(re)), im(T(im)) {}

public: // copy:

    complex(const complex & din) {
        this->re = din.re;
        this->im = din.im;
    }

    complex & operator=(const complex & rhs) {
        if (this == &rhs) return *this;
        this->re = rhs.re;
        this->im = rhs.im;
        return *this;
    }

public: // dtor:

    ~complex() = default;

public: // static methods:

    static complex dx() {
        return T::dx();
    }

    static complex tiny() {
        return T::tiny();
    }

    static complex pi() {
        return T::pi();
    }

public: // static methods:

    static complex zero() {
        return complex(T::zero());
    }

    static complex unit() {
        return complex(T::unit());
    }

    // complex<T>::sqrt(x)
    static complex sqrt(complex ain) {
        // I think this comparison is ok, correct me if I am wrong.
        if (ain.im == T::zero())
            return complex(T::sqrt(ain.re));
        complex norm = abs(ain);
        return complex(T::sqrt((norm.re + ain.re)/T(2)), T::sqrt((norm.re - ain.re)/T(2)));
    }

    // complex<T>::abs(x)
    // For consistency with other scalars, we continue to call this abs().
    // I believe it is commonly referred to as the modulus.
    // It is the little-l2 norm in the complex plane as a real 2D space.
    // We stay in the scalar type, so it returns a complex number.
    // This is necessary, if we wish to maintain
    // a consistent interface with each scalar type, including complex<T>.
    static complex abs(complex ain) {
        return complex(T::sqrt(ain.re*ain.re + ain.im*ain.im));
    }

    // complex<T>::abs2(x)
    // Exceptional method for complex<T>.
    // The square norm.
    static complex abs2(complex ain) {
        return complex(ain.re*ain.re + ain.im*ain.im);
    }

    // complex<T>::neg(x)
    static complex neg(complex ain) {
        return complex(T::neg(ain.re), T::neg(ain.im));
    }

    static complex inv(complex ain) {
        T abs2 = complex::abs2(ain);
        return complex(ain.re/abs2, T::neg(ain.im)/abs2);
    }

    // complex<T>::rem(x,y)
    // todo: perhaps revisit this?
    static complex rem(complex ain, complex bin) {
        return T::zero();
    }

    // complex<T>::mod(x,y)
    // mod in the sense of integer arithmetic,
    // not in the sense of complex arithmetic!
    // (This isn't our faults!)
    static complex mod(complex ain, complex bin) {
        return T::zero();
    }

    // complex<T>::sin(x)
    // Maybe it depends, but this does not arise often in practice.
    static complex sin(complex ain) {
        return complex(T::sin(ain.re)*T::cos(ain.im), T::neg(T::cos(ain.re)*T::sin(ain.im)));
    }

    // complex<T>::cos(x)
    // Maybe it depends, but this does not arise often in practice.
    static complex cos(complex ain) {
        return complex(T::cos(ain.re)*T::sin(ain.re), T::sin(ain.im)*T::cos(ain.im));
    }

    // complex<T>::exp(x)
    static complex exp(complex ain) {
        T tmp = T::exp(ain.re);
        return complex(tmp*T::sin(ain.re), tmp*T::cos(ain.im));
    }

    // complex<T>::log(x)
    static complex log(complex ain) {
        // todo I'm too tired to do this right now
        return T::log(ain.re);
    }

    // complex<T>::ln(x)
    static complex ln(complex ain) {
        return log(ain);
    }

public: // API, mirroring static:

    [[nodiscard]] complex sqrt() const {
        return complex::sqrt(*this);
    }

    [[nodiscard]] complex abs() const {
        return complex::abs(*this);
    }

    // complex<T>::abs2(x)
    // Exceptional method for complex<T>.
    [[nodiscard]] complex abs2() const {
        return complex::abs2(*this);
    }

    [[nodiscard]] complex neg() const {
        return complex::neg(*this);
    }

    [[nodiscard]] complex inv() const {
        return complex::inv(*this);
    }

    [[nodiscard]] complex rem(complex bin) const {
        return complex::rem(*this, bin);
    }

    [[nodiscard]] complex mod(complex bin) const {
        return complex::rem(bin);
    }

    [[nodiscard]] complex sin() const {
        return complex::sin(*this);
    }

    [[nodiscard]] complex cos() const {
        return complex::cos(*this);
    }

    [[nodiscard]] complex exp() const {
        return complex::exp(*this);
    }

    [[nodiscard]] complex log() const {
        return complex::log(*this);
    }

    [[nodiscard]] complex ln() const {
        return log();
    }

private: // Super-only:

    // used by Super for l2-norm
    friend complex operator^(const complex & ain, int pow) {
        return ain*ain;
    }

public: // Super-related:

    // multiplication T x T --> T
    // trivial dot product.
    friend complex operator%(const complex & lhs, const complex & rhs) {
        return lhs*rhs;
    }

    // Bracket notation
    complex & operator[](size_t index) {
        return *this;
    }

    const complex & operator[](size_t index) const {
        return *this;
    }

    complex & operator[](DGCALC::IPoint<2> index) {
        return *this;
    }

    const complex & operator[](DGCALC::IPoint<2> index) const {
        return *this;
    }

public: // artifacts:

    bool operator==(const complex & rhs) const {
        if (this == &rhs) return true;
        return (re == rhs.re && im == rhs.im);
    };

    bool operator!=(const complex & rhs) const {
        return !(*this == rhs);
    }

    // Warning: dummy operation to fulfill Scalar API,
    // but may have some rare use cases.
    // todo finish by implementing <=> and > explicitly
    bool operator<(const complex & rhs) const {
        T norm2 = re*re+im*im;
        T norm2rhs = rhs.re*rhs.re+rhs.im*rhs.im;
        return (norm2 < norm2rhs);
    }

    bool operator>(const complex & rhs) const {
        return (rhs < *this);
    }

    bool operator<=(const complex & rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const complex & rhs) const {
        return !(*this < rhs);
    }

    // compound +
    complex & operator+=(const complex & rhs) {
        re += rhs.re;
        im += rhs.im;
        return *this;
    }
    // compound -
    complex & operator-=(const complex & rhs) {
        re -= rhs.re;
        im -= rhs.im;
        return *this;
    }
    // compound *
    complex & operator*=(const complex & rhs) {
        // Don't know if this is optimal.
        T tmp = re;
        re *= rhs.re;
        re -= im*rhs.im;
        im *= rhs.re;
        im += tmp*rhs.im;
        return *this;
    }
    // compound /
    complex & operator/=(const complex & rhs) {
        // Don't know if this is optimal.
        T tmp = abs2(rhs).re;
        *this *= complex(rhs.re/tmp, T::neg(rhs.im)/tmp);
        return *this;
    }
    /*
     * Reminder: when you get to the binary operators,
     * stop returning references.
     * Adding "friend" makes them ordinary functions,
     * which can nevertheless modify private members.
     */
    friend complex operator+(const complex & lhs, const complex & rhs) {
        complex out = lhs;
        out += rhs;
        return out;
    }
    friend complex operator-(const complex & lhs, const complex & rhs) {
        complex out = lhs;
        out -= rhs;
        return out;
    }
    friend complex operator*(const complex & lhs, const complex & rhs) {
        complex out = lhs;
        out *= rhs;
        return out;
    }
    friend complex operator/(const complex & lhs, const complex & rhs) {
        complex out = lhs;
        out /= rhs;
        return out;
    }

    // undertype - useful for interoperability of scalars,
    // meaningless for complex<T>.
    [[nodiscard]] Undertype under() const {
        return re.under();
    }

public: // printing

    std::string str_di() const {
        return re.str_di() + " + i" + im.str_di();
    }

    // I'm not sure if this is what you would want here, but we'll see (?)
    std::string str_dat() const {
        return re.str_dat() + ", " + im.str_dat();
    }

     std::string str() const {
        return str_di();
    }

};

template <typename T>
std::ostream& operator<<(std::ostream & os, const complex<T> & obj) {
    os << obj.str();
    return os;
}
