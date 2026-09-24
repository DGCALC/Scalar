//
// Created by Lucius Schoenbaum on 9/28/21.
//

/*
 * quaternion<T>
 * General Complex-Scalar type based on Scalar type T
 *
 * Morally, quaternion<T> inherits from T
 * for its real part,
 * but in practice, it is convenient
 * to have references x.re and x.im
 * come as a pair, without ceremony or fuss.
 *
 *
 */

#pragma once

#include <DGCALC.h>

#include <string>

template <typename T>
struct quaternion {
    template <typename PP, typename TT, size_t size, size_t cosize>
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

    explicit quaternion(): re(T::zero()), im(T::zero()) {}

    // todo?
//    explicit quaternion(const string & str): re(T::zero()), im(T::zero()) {
//        // todo this won't quite work - you would have to implement a quaternion Parts.
//        Parts64B2 pt(str);
//        quaternion cpy(pt);
//        *this = cpy;
//    }

    explicit quaternion(T re, T im = T::zero()): re(re), im(im) {}

    explicit quaternion(Undertype re, Undertype im = 0): re(T(re)), im(T(im)) {}

public: // copy:

    quaternion(const quaternion & din) {
        this->re = din.re;
        this->im = din.im;
    }

    quaternion & operator=(const quaternion & rhs) {
        if (this == &rhs) return *this;
        this->re = rhs.re;
        this->im = rhs.im;
        return *this;
    }

public: // dtor:

    ~quaternion() = default;

public: // static methods:

    static quaternion dx() {
        return T::dx();
    }

    static quaternion tiny() {
        return T::tiny();
    }

    static quaternion pi() {
        return T::pi();
    }

public: // static methods:

    static quaternion zero() {
        return quaternion(T::zero());
    }

    static quaternion unit() {
        return quaternion(T::unit());
    }

    // quaternion<T>::sqrt(x)
    static quaternion sqrt(quaternion ain) {
        // I think this comparison is ok, correct me if I am wrong.
        if (ain.im == T::zero())
            return quaternion(T::sqrt(ain.re));
        quaternion norm = abs(ain);
        return quaternion(T::sqrt((norm.re + ain.re)/T(2)), T::sqrt((norm.re - ain.re)/T(2)));
    }

    // quaternion<T>::abs(x)
    // For consistency with other scalars, we continue to call this abs().
    // I believe it is commonly referred to as the modulus.
    // It is the little-l2 norm in the quaternion plane as a real 2D space.
    // We stay in the scalar type, so it returns a quaternion number.
    // This is necessary, if we wish to maintain
    // a consistent interface with each scalar type, including quaternion<T>.
    static quaternion abs(quaternion ain) {
        return quaternion(T::sqrt(ain.re*ain.re + ain.im*ain.im));
    }

    // quaternion<T>::abs2(x)
    // Exceptional method for quaternion<T>.
    // The square norm.
    static quaternion abs2(quaternion ain) {
        return quaternion(ain.re*ain.re + ain.im*ain.im);
    }

    // quaternion<T>::neg(x)
    static quaternion neg(quaternion ain) {
        return quaternion(T::neg(ain.re), T::neg(ain.im));
    }

    static quaternion inv(quaternion ain) {
        T abs2 = quaternion::abs2(ain);
        return quaternion(ain.re/abs2, T::neg(ain.im)/abs2);
    }

    // quaternion<T>::rem(x,y)
    // todo: perhaps revisit this?
    static quaternion rem(quaternion ain, quaternion bin) {
        return T::zero();
    }

    // quaternion<T>::mod(x,y)
    // mod in the sense of integer arithmetic,
    // not in the sense of quaternion arithmetic!
    // (This isn't our faults!)
    static quaternion mod(quaternion ain, quaternion bin) {
        return T::zero();
    }

    // quaternion<T>::sin(x)
    // Maybe it depends, but this does not arise often in practice.
    static quaternion sin(quaternion ain) {
        return quaternion(T::sin(ain.re)*T::cos(ain.im), T::neg(T::cos(ain.re)*T::sin(ain.im)));
    }

    // quaternion<T>::cos(x)
    // Maybe it depends, but this does not arise often in practice.
    static quaternion cos(quaternion ain) {
        return quaternion(T::cos(ain.re)*T::sin(ain.re), T::sin(ain.im)*T::cos(ain.im));
    }

    // quaternion<T>::exp(x)
    static quaternion exp(quaternion ain) {
        T tmp = T::exp(ain.re);
        return quaternion(tmp*T::sin(ain.re), tmp*T::cos(ain.im));
    }

    // quaternion<T>::log(x)
    static quaternion log(quaternion ain) {
        // todo I'm too tired to do this right now
        return T::log(ain.re);
    }

    // quaternion<T>::ln(x)
    static quaternion ln(quaternion ain) {
        return log(ain);
    }

public: // API, mirroring static:

    [[nodiscard]] quaternion sqrt() const {
        return quaternion::sqrt(*this);
    }

    [[nodiscard]] quaternion abs() const {
        return quaternion::abs(*this);
    }

    // quaternion<T>::abs2(x)
    // Exceptional method for quaternion<T>.
    [[nodiscard]] quaternion abs2() const {
        return quaternion::abs2(*this);
    }

    [[nodiscard]] quaternion neg() const {
        return quaternion::neg(*this);
    }

    [[nodiscard]] quaternion inv() const {
        return quaternion::inv(*this);
    }

    [[nodiscard]] quaternion rem(quaternion bin) const {
        return quaternion::rem(*this, bin);
    }

    [[nodiscard]] quaternion mod(quaternion bin) const {
        return quaternion::rem(bin);
    }

    [[nodiscard]] quaternion sin() const {
        return quaternion::sin(*this);
    }

    [[nodiscard]] quaternion cos() const {
        return quaternion::cos(*this);
    }

    [[nodiscard]] quaternion exp() const {
        return quaternion::exp(*this);
    }

    [[nodiscard]] quaternion log() const {
        return quaternion::log(*this);
    }

    [[nodiscard]] quaternion ln() const {
        return log();
    }

private: // Super-only:

    // used by Super for l2-norm
    friend quaternion operator^(const quaternion & ain, int pow) {
        return ain*ain;
    }

public: // Super-related:

    // multiplication T x T --> T
    // trivial dot product.
    friend quaternion operator%(const quaternion & lhs, const quaternion & rhs) {
        return lhs*rhs;
    }

    // Bracket notation
    quaternion & operator[](size_t index) {
        return *this;
    }

    const quaternion & operator[](size_t index) const {
        return *this;
    }

    quaternion & operator[](DGCALC::IPoint<2> index) {
        return *this;
    }

    const quaternion & operator[](DGCALC::IPoint<2> index) const {
        return *this;
    }

public: // artifacts:

    bool operator==(const quaternion & rhs) const {
        if (this == &rhs) return true;
        return (re == rhs.re && im == rhs.im);
    };

    bool operator!=(const quaternion & rhs) const {
        return !(*this == rhs);
    }

    // Warning: dummy operation to fulfill Scalar API,
    // but may have some rare use cases.
    // todo finish by implementing <=> and > explicitly
    bool operator<(const quaternion & rhs) const {
        T norm2 = re*re+im*im;
        T norm2rhs = rhs.re*rhs.re+rhs.im*rhs.im;
        return (norm2 < norm2rhs);
    }

    bool operator>(const quaternion & rhs) const {
        return (rhs < *this);
    }

    bool operator<=(const quaternion & rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const quaternion & rhs) const {
        return !(*this < rhs);
    }

    // compound +
    quaternion & operator+=(const quaternion & rhs) {
        re += rhs.re;
        im += rhs.im;
        return *this;
    }
    // compound -
    quaternion & operator-=(const quaternion & rhs) {
        re -= rhs.re;
        im -= rhs.im;
        return *this;
    }
    // compound *
    quaternion & operator*=(const quaternion & rhs) {
        // Don't know if this is optimal.
        T tmp = re;
        re *= rhs.re;
        re -= im*rhs.im;
        im *= rhs.re;
        im += tmp*rhs.im;
        return *this;
    }
    // compound /
    quaternion & operator/=(const quaternion & rhs) {
        // Don't know if this is optimal.
        T tmp = abs2(rhs).re;
        *this *= quaternion(rhs.re/tmp, T::neg(rhs.im)/tmp);
        return *this;
    }
    /*
     * Reminder: when you get to the binary operators,
     * stop returning references.
     * Adding "friend" makes them ordinary functions,
     * which can nevertheless modify private members.
     */
    friend quaternion operator+(const quaternion & lhs, const quaternion & rhs) {
        quaternion out = lhs;
        out += rhs;
        return out;
    }
    friend quaternion operator-(const quaternion & lhs, const quaternion & rhs) {
        quaternion out = lhs;
        out -= rhs;
        return out;
    }
    friend quaternion operator*(const quaternion & lhs, const quaternion & rhs) {
        quaternion out = lhs;
        out *= rhs;
        return out;
    }
    friend quaternion operator/(const quaternion & lhs, const quaternion & rhs) {
        quaternion out = lhs;
        out /= rhs;
        return out;
    }

    // undertype - useful for interoperability of scalars,
    // meaningless for quaternion<T>.
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
std::ostream& operator<<(std::ostream & os, const quaternion<T> & obj) {
    os << obj.str();
    return os;
}
