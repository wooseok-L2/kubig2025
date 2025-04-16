#include <iostream>
#include "complex.h"

int main()
{
    Complex c1;
    Complex c2 = 3.0;        //Complex c2(3.0)
    Complex c3(3.0, 4.0);
    Complex c4 = c3;         //Complex c4(c3)

    c1 = c3;
    
    c1 == c4;

    c1 != c3;

    c1 = c2 + c3;

    c1 = c2 - c3;

    c1 += c2 += c3;

    ++c1;
    c1++;
 
    std::cout << "c1 : " << c1 << std::endl;
    std::cout << "c2 : " << c2 << std::endl;
    std::cout << "c3 : " << c3 << std::endl;
    std::cout << "c4 : " << c4 << std::endl;

    return 0;
}