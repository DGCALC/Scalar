//
// Created by Lucius Schoenbaum on 9/28/21.
//

#pragma once

#include <Tbasis.h>

#include <scalar/types/double754.h>



class Tdouble754 {



public: // API:

    static void Tdryrun() {
        double754 x = "1.234"_d754;
        cout << x << endl;
        cout << x.str_hex() << "\n";
        cout << x.str_bin() << "\n";
        cout << "bye" << endl;
    }

    static void Tstr_methods() {
        double754 x = "1.234"_d754;
        cout << "standard:\n";
        cout << x << endl;
        cout << "digest:\n";
        cout << x.str_di() << endl;
        cout << "dat:\n";
        cout << x.dat() << endl;
        cout << "bye" << endl;
    }

    static void Toperations() {
        double754 a = "1.234"_d754;
        double754 b = "3.3"_d754;
        double754 a2 = "1.234"_d754;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "equality" << endl;
        cout << (a == b) << endl;
        cout << (a == a) << endl;
        cout << (a == a2) << endl;
        cout << "operator+" << endl;
        double754 c = a;
        c += b;
        cout << "a + b = " << c << endl;
        cout << "friend operator+" << endl;
        cout << (a + b) << endl;
        cout << "static method" << endl;
        cout << double754::sqrt(a) << endl;
        cout << a.sqrt() << endl;
        cout << "static field" << endl;
        cout << double754::size << endl;
        cout << double754::cosize << endl;
    }

    static void Tdouble_mod() {
        double x = 12.34;
        double y = 3.45;
        cout << x << endl;
        cout << y << endl;
//        cout << (x % y) << endl; // error
    }

    static void Tbinom() {
        const int stop = 7;
        for (int n = -1; n < stop; ++n) {
            for (int k = -1; k <= stop; ++k) {
                cout << double754::binom(n,k) << "\t\t";
            }
            cout << endl;
        }
    }

};
