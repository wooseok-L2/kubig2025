#include <iostream>
#include "rational.h"

int main()
{
    Rational r1(3, 4);     // (3.0, 4.0i)
    Rational r2 = 3;          // (3.0, 0.0i)
    Rational r3;               // (0.0. 0.0i)

    // r3.setnumerator(r1.getnumerator());
    // r3.setdenominator(r1.getdenominator());
    r3 = r1;

    if (r1 == r3){      // operator == (r1, r3) or r1.operator == (r3)
        std::cout << "r1 and r3 are equal" << std::endl;
    }
    else {
        std::cout << "r1 and r3 are not equal" << std::endl;
    }


    std::cout << "r1 : ( " << r1.getnumerator() << " / " << r1.getdenominator() << " ) " << std::endl;
    std::cout << "r2 : ( " << r2.getnumerator() << " / " << r2.getdenominator() << " ) " << std::endl;
    std::cout << "r3 : ( " << r3.getnumerator() << " / " << r3.getdenominator() << " ) " << std::endl;

    return 0;
}