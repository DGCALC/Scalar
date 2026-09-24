//
// Created by Lucius Schoenbaum on 9/28/21.
//


#pragma once

#include <Tbasis.h>

#include <scalar/high.h>
#include <scalar/types/double754.h>


class Thigh {

    using T = double754;
    using T1 = high<T, 1>;
    using T2 = high<T, 2>;

    template <typename highT>
    static void basictest(highT a, highT b) {
        cout << "a = " << a.str() << endl;
        cout << "b = " << b.str() << endl;
        cout << "addition and multiplication:\n";
        cout << "a + b = " << (a+b).str() << endl;
        cout << "a*b = " << (a*b).str() << endl;
        cout << "additive and multiplicative inverse:\n";
        cout << "-a = " << a.neg().str() << endl;
        cout << "1/a = " << a.inv().str() << endl;
        cout << "1/b = " << b.inv().str() << endl;
        cout << "division and square root:\n";
        cout << "√a = " << a.sqrt().str() << endl;
        cout << "√b = " << b.sqrt().str() << endl;
        cout << "a/b = " << (a/b).str() << endl;
        cout << "sine and cosine:\n";
        cout << "sin a = " << a.sin().str() << endl;
        cout << "cos a = " << a.cos().str() << endl;
        cout << "sin b = " << b.sin().str() << endl;
        cout << "cos b = " << b.cos().str() << endl;
        cout << "exponential:\n";
        cout << "exp a = " << a.exp().str() << endl;
        cout << "exp b = " << b.exp().str() << endl;
    }


public: // API:

    template <int d>
    static void Tdryrun() {
        using highT = high<T, d>;
        highT a{1, 2};
        highT b{3, 4};
        basictest(a, b);
        cout << "bye" << endl;
    }

};

