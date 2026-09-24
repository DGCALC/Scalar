//
// Created by Lucius Schoenbaum on 5/24/21.
//

#pragma once

#include <iostream>
using namespace std;


class Tposit {



public: //

    static void Tgustafson_dotproduct_example() {
        float as[4];
        float bs[4];
        float outs;
        double ad[4];
        double bd[4];
        double outd, tmp;
        as[0] = 3.2e7;
        as[1] = 1.0;
        as[2] = -1.0;
        as[3] = 8.0e7;
        bs[0] = 4.0e7;
        bs[1] = 1.0;
        bs[2] = -1.0;
        bs[3] = -1.6e7;
        ad[0] = 3.2e7;
        ad[1] = 1.0;
        ad[2] = -1.0;
        ad[3] = 8.0e7;
        bd[0] = 4.0e7;
        bd[1] = 1.0;
        bd[2] = -1.0;
        bd[3] = -1.6e7;
        // https://www.youtube.com/watch?v=aP0Y1uAA-2Y#t=1m21s
        // cf. the pinned comment on the lecture video by the speaker, saying the exponents are "off by one".
        // cf. discussion - http://forums.parallax.com/discussion/166008/john-gustafson-presents-beyond-floating-point-next-generation-computer-arithmetic
        cout << "Gustafson's lecture: a•b = 0, a•b = 0, a•b = 1, a•b = 2" << endl;
        outs = 0.0;
        for (int i = 0; i < 4; ++i) {
            outs += as[i]*bs[i];
            cout << "outs = " << outs << endl;
        }
        cout << "(single) a • b = " << outs << endl;
        outd = 0.0;
        for (int i = 0; i < 4; ++i) {
            outd += ad[i]*bd[i];
            cout << "outd = " << outd << endl;
        }
        cout << "(double) a • b = " << outd << endl;
        outd = ad[0]*bd[0];
        outd += ad[1]*bd[1];
        cout << "outd = " << outd << endl;
        tmp = ad[2]*bd[2];
        tmp += ad[3]*bd[3];
        cout << "tmp = " << tmp << endl;
        outd = outd+tmp;
        cout << "(double, binary sum collapse) a • b = " << outd << endl;
        cout << "(correct) a • b = 2" << endl;
    }

};