#include <iostream>
#include "rational.h"

int main()
{
    Rational r1(3, 4);     // (3.0, 4.0i)
    Rational r2(3);          // (3.0, 0.0i)
    Rational r3;               // (0.0. 0.0i)

    r3.numerator(3);
    r3.denominator(4);

    std::cout << "r1 : ( " << r1.numerator() << " / " << r1.denominator() << " ) " << std::endl;
    std::cout << "r2 : ( " << r2.numerator() << " / " << r2.denominator() << " ) " << std::endl;
    std::cout << "r3 : ( " << r3.numerator() << " / " << r3.denominator() << " ) " << std::endl;

    return 0;
}