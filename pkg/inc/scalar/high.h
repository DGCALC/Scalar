//
// Created by Lucius Schoenbaum on 9/28/21.
//

/*
 * high<T>
 * Higher-order Scalar type (dual number) based on Scalar type T
 *
 *
 *
 */

#pragma once

#include <DGCALC.h>

#include <string>

template <typename T, size_t d>
struct high {
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

    T data[d+1];

public: // ctor:

    explicit high() {
        for (auto i = 0; i <= d; ++i) {
            data[i] = T::zero();
        }
    }

    explicit high(T x) {
        data[0] = x;
        for (auto i = 1; i <= d; ++i) {
            data[i] = T::zero();
        }
    }

    explicit high(T x, T dx) {
        data[0] = x;
        data[1] = dx;
        if constexpr (d > 1)
            for (auto i = 2; i <= d; ++i) {
                data[i] = T::zero();
            }
    }

    explicit high(Undertype x, Undertype dx = 0) {
        data[0] = T(x);
        data[1] = T(dx);
        if constexpr (d > 1)
            for (auto i = 2; i <= d; ++i) {
                data[i] = T::zero();
            }
    }

    // todo initializer list ctor

public: // copy:

    high(const high & din) {
        for (int i = 0; i <= d; ++i) {
            this->data[i] = din.data[i];
        }
    }

    high & operator=(const high & rhs) {
        if (this == &rhs) return *this;
        for (int i = 0; i <= d; ++i) {
            this->data[i] = rhs.data[i];
        }
        return *this;
    }

public: // dtor:

    ~high() = default;

public: // static methods:

    static high dx() {
        return T::dx();
    }

    static high tiny() {
        return T::tiny();
    }

    static high pi() {
        return T::pi();
    }

public: // static methods:

    static high zero() {
        return high(T::zero());
    }

    static high unit() {
        return high(T::unit());
    }

    // high<T>::sqrt(x)
    /*
     * Let u = sqrt(x), x the independent variable.
     * For k >= 2, have that the kth dual number is
     * d^k u = -2 prod_{m=2}^{k-1} (2-4m) du^{2k-1}
     * where du is the 1st dual number.
     * This formula is easily obtained by rewriting
     * the more straightforward formula
     * d^k u = (-1)^{k+1} 1/2^k * prod_{m=1}^{k-2} (2m+1) * \left( \frac{1}{sqrt(x)}\right)^{2k-1}
     * It is rewritten as
     * -2 * du^{k} * prod_{m=1}^{k-2} du*(-4m-2)
     * for k >= 2, for a slightly more efficient procedure.
     *
     */
    static high sqrt(high ain) {
        high out;
        T tmp;
        out.data[0] = ain.data[0].sqrt();
        out.data[1] = T(0.5)/ain.data[0].sqrt();
        if constexpr (d >= 2) {
            for (auto di = 2; di <= d; ++di) {
                tmp = out.data[1];
                out.data[di] = T::unit();
                for (auto m = 0; m < di; ++m) {
                    out.data[di] *= tmp;
                }
                for (auto m = 1; m <= m - 2; ++m) {
                    out.data[di] *= tmp * T(-4 * m - 2);
                }
                out.data[di] *= T(-2);
            }
        }
        return out;
    }

    // high<T>::abs(x)
    static high abs(high ain) {
        high out = ain;
        if (ain.data[0] < 0)
            out = neg(ain);
        return out;
    }

    // high<T>::neg(x)
    static high neg(high ain) {
        high out;
        for (int i = 0; i <= d; ++i) {
            out.data[i] = ain.data[i].neg();
        }
        return out;
    }

    /*
     * Let u = 1/x, for independent variable x.
     * From the formula
     * u^{(d)} = (-1)^d d! x^{-d-1}
     * it is immediate that
     * u^{(d)} = -d * u * u^{(d-1)}
     *
     */
    // high<T>::inv(x)
    static high inv(high ain) {
        // I'm not sure what this thing should do when ain "is" zero.
        // I'm not sure what that even means yet, for a higher-order dual number.
        // No matter how you define it, something breaks near the singularity.
        high out;
        out.data[0] = ain.data[0].inv();
        out.data[1] = out.data[0];
        out.data[1] = out.data[1].neg();
        if constexpr (d >= 2) {
            for (auto di = 2; di <= d; ++di) {
                out.data[di] = T(-di)*out.data[0]*out.data[di-1];
            }
        }
        return out;
    }

    // high<T>::rem(x,y)
    // todo: perhaps revisit this?
    static high rem(high ain, high bin) {
        return T::zero();
    }

    // high<T>::mod(x,y)
    // mod in the sense of integer arithmetic,
    // not in the sense of complex arithmetic!
    // (This isn't our faults!)
    static high mod(high ain, high bin) {
        // todo ???
        return T::zero();
    }

    // high<T>::sin(x)
    static high sin(high ain) {
        high out;
        out.data[0] = ain.data[0].sin();
        out.data[1] = ain.data[0].cos();
        if constexpr (d >= 2) {
            for (auto di = 2; di <= d; di += 4) {
                out.data[di] = ain.data[di].sin().neg();
            }
            for (auto di = 3; di <= d; di += 4) {
                out.data[di] = ain.data[di].cos().neg();
            }
            for (auto di = 4; di <= d; di += 4) {
                out.data[di] = ain.data[di].sin();
            }
            for (auto di = 5; di <= d; di += 4) {
                out.data[di] = ain.data[di].cos();
            }
        }
        return out;
    }

    // high<T>::cos(x)
    static high cos(high ain) {
        high out;
        out.data[0] = ain.data[0].cos();
        out.data[1] = ain.data[0].sin().neg();
        if constexpr (d >= 2) {
            for (auto di = 2; di <= d; di += 4) {
                out.data[di] = ain.data[di].cos().neg();
            }
            for (auto di = 3; di <= d; di += 4) {
                out.data[di] = ain.data[di].sin();
            }
            for (auto di = 4; di <= d; di += 4) {
                out.data[di] = ain.data[di].cos();
            }
            for (auto di = 5; di <= d; di += 4) {
                out.data[di] = ain.data[di].sin().neg();
            }
        }
        return out;
    }

    /*
     * I have some confusion about initialization:
     * should higher orders be initialized to zero,
     * if there is no reason to set them to anything in particular?
     * ...if so, this operation turns these zeros to ones.
     * Is this right? Would it be more correct to have
     * things be set to, say, "no value" until some operation
     * forces them to populate (such as sqrt or product).
     * ...Maybe I'm missing something obvious here.
     * I've been coding a lot so I'm a little math-numb at the moment.
     *
     */
    // high<T>::exp(x)
    static high exp(high ain) {
        high out;
        out.data[0] = ain.data[0].exp();
        out.data[1] = ain.data[1].exp();
        if constexpr (d >= 2) {
            for (auto di = 2; di <= d; di += 1) {
                out.data[di] = ain.data[di].exp();
            }
        }
        return out;
    }

    // high<T>::log(x)
    static high log(high ain) {
        // todo SYMBOLIC CALCULUS!
        return T(0);
    }

    // high<T>::ln(x)
    // alternative notation for log
    static high ln(high ain) {
        return log(ain);
    }

public: // API, mirroring static:

    [[nodiscard]] high sqrt() const {
        return high::sqrt(*this);
    }

    [[nodiscard]] high abs() const {
        return high::abs(*this);
    }

    [[nodiscard]] high neg() const {
        return high::neg(*this);
    }

    [[nodiscard]] high inv() const {
        return high::inv(*this);
    }

    [[nodiscard]] high rem(high bin) const {
        return high::rem(*this, bin);
    }

    [[nodiscard]] high mod(high bin) const {
        return high::rem(bin);
    }

    [[nodiscard]] high sin() const {
        return high::sin(*this);
    }

    [[nodiscard]] high cos() const {
        return high::cos(*this);
    }

    [[nodiscard]] high exp() const {
        return high::exp(*this);
    }

    [[nodiscard]] high log() const {
        return high::log(*this);
    }

    [[nodiscard]] high ln() const {
        return log();
    }

private: // Super-only:

    // used by Super for l2-norm
    friend high operator^(const high & ain, int pow) {
        return ain*ain;
    }

public: // Super-related:

    // multiplication T x T --> T
    // trivial dot product.
    friend high operator%(const high & lhs, const high & rhs) {
        return lhs*rhs;
    }

    // Bracket notation
    high & operator[](size_t index) {
        return *this;
    }

    const high & operator[](size_t index) const {
        return *this;
    }

    high & operator[](DGCALC::IPoint<2> index) {
        return *this;
    }

    const high & operator[](DGCALC::IPoint<2> index) const {
        return *this;
    }

public: // artifacts:

    bool operator==(const high & rhs) const {
        if (this == &rhs) return true;
        bool out = true;
        for (auto i = 0; i <= d; ++i) {
            if (data[i] != rhs.data[i]) {out = false; break;}
        }
        return out;
    };

    bool operator!=(const high & rhs) const {
        return !(*this == rhs);
    }

    // todo finish by implementing <=> and > explicitly
    bool operator<(const high & rhs) const {
        return data[0] < rhs.data[0];
    }

    bool operator>(const high & rhs) const {
        return (rhs < *this);
    }

    bool operator<=(const high & rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const high & rhs) const {
        return !(*this < rhs);
    }

    // compound +
    high & operator+=(const high & rhs) {
        for (int i = 0; i <= d; ++i) {
            data[i] += rhs.data[i];
        }
        return *this;
    }
    // compound -
    high & operator-=(const high & rhs) {
        for (int i = 0; i <= d; ++i) {
            data[i] -= rhs.data[i];
        }
        return *this;
    }
    // compound *
    high & operator*=(const high & rhs) {
        data[0] *= rhs.data[0];
        data[1] = data[1]*rhs.data[0] + data[0]*rhs.data[1];
        // todo wrap in if constexpr
        for (int i = 2; i <= d; ++i) {
            // sum of terms
            for (int j = 0; j < i; ++j) {
                data[i] += T::binom(i,j)*data[j]*rhs.data[i-j];
            }
        }
        return *this;
    }
    // compound /
    high & operator/=(const high & rhs) {
        high tmp = rhs.inv();
        *this *= tmp;
        return *this;
    }
    /*
     * Reminder: when you get to the binary operators,
     * stop returning references.
     * Adding "friend" makes them ordinary functions,
     * which can nevertheless modify private members.
     */
    friend high operator+(const high & lhs, const high & rhs) {
        high out = lhs;
        out += rhs;
        return out;
    }
    friend high operator-(const high & lhs, const high & rhs) {
        high out = lhs;
        out -= rhs;
        return out;
    }
    friend high operator*(const high & lhs, const high & rhs) {
        high out = lhs;
        out *= rhs;
        return out;
    }
    friend high operator/(const high & lhs, const high & rhs) {
        high out = lhs;
        out /= rhs;
        return out;
    }

    // undertype - useful for interoperability of scalars,
    // meaningless for high<T>.
    [[nodiscard]] Undertype under() const {
        return data[0].under();
    }

public: // printing

    std::string str_di() const {
        string out = data[0].str_di() + " + d(";
        out += data[1].str_di() + ")";
        for (int i = 2; i <= d; ++i) {
            out += " + d" + std::to_string(i) + "(" + data[i].str_di() + ")";
        }
        return out;
    }

    std::string str_dat() const {
        string out;
        for (int i = 0; i <= d; ++i) {
            out += data[i].str_dat() + " ";
        }
        return out;
    }

     std::string str() const {
        return str_di();
    }

};

template <typename T, size_t d>
std::ostream& operator<<(std::ostream & os, const high<T, d> & obj) {
    os << obj.str();
    return os;
}
