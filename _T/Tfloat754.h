//
// Created by Lucius Schoenbaum on 9/28/21.
//

#pragma once

#include <Tbasis.h>

#include <scalar/types/float754.h>



class Tfloat754 {



public: // API:

    static void Tdryrun() {
        float754 x = "1.234"_f754;
        cout << x << endl;
        cout << x.str_hex() << "\n";
        cout << x.str_bin() << "\n";
        cout << "str dat:" << x.str_dat() << endl;
        cout << "bye" << endl;
    }

    static void Tstr_methods() {
        float754 x = "1.234"_f754;
        cout << "standard:\n";
        cout << x << endl;
        cout << "digest:\n";
        cout << x.str_di() << endl;
        cout << "dat:\n";
        cout << x.dat() << endl;
        cout << "bye" << endl;
    }

    static void Toperations() {
        float754 a = "1.234"_f754;
        float754 b = "3.3"_f754;
        float754 a2 = "1.234"_f754;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "equality" << endl;
        cout << (a == b) << endl;
        cout << (a == a) << endl;
        cout << (a == a2) << endl;
        cout << "operator+" << endl;
        float754 c = a;
        c += b;
        cout << "a + b = " << c << endl;
        cout << "friend operator+" << endl;
        cout << (a + b) << endl;
        cout << "static method" << endl;
        cout << float754::sqrt(a) << endl;
        cout << a.sqrt() << endl;
        cout << "static field" << endl;
        cout << float754::size << endl;
        cout << float754::cosize << endl;
    }

};
