//
// Created by Lucius Schoenbaum on 9/28/21.
//


#pragma once

#include <Tbasis.h>

#include <scalar/complex.h>
#include <scalar/types/double754.h>


class Tcomplex {

    using T = double754;
    using CT = complex<T>;

public: // API:


    static void Tdryrun() {
        CT z1(1.234, 3.456);
        CT z2(0, 1);

        cout << "dat:\n";
        cout << z1.str_dat() << "\n";
        cout << z2.str_dat() << "\n";
        cout << "string:\n";
        cout << z1.str() << "\n";
        cout << z2.str() << "\n";
        cout << (z1*z2).str() << "\n";
        cout << "divide:\n";
        cout << (CT::unit()/z1).str() << "\n";
        cout << (z1/z2).str() << "\n";
        cout << "some methods:\n";
        cout << CT::sin(z2).str() << "\n";
        cout << CT::cos(z2).str() << "\n";
        cout << "operator << \n";
        cout << z1 << endl;
        cout << z2 << endl;
        cout << "bye" << endl;
    }

};

