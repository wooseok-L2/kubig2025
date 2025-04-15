#include <iostream>
#include "complex.h"

int main()
{
    Complex c1;
    Complex c2 = 3.0;         // Complex c2(3.0);         
    Complex c3(3.0, 4.0);
    Complex c4 = c3;          // Complex c4(c3);

    c1 = c3;         
    c1 = c2 = c3;             // daisychain 

    if (c1 == c3){      // operator == (C1, c3) or c1.operator == (c3)
        std::cout << "c1 and c3 are equal" << std::endl;
    }
    else {
        std::cout << "c1 and c3 are not equal" << std::endl;
    }

    // std::cout << c1;    //std::cout.operator << c1 (x) or operator << (std::cout,c10) (o)
    // std::cout << std::endl;
    c4 = c2 + c3;     // c2.operator+(c3) or operator+(c2, c3)
    c4 = c2 - c3;

    std::cout << c1 << std::endl; 
    std::cout << c2 << std::endl; 
    std::cout << c3 << std::endl; 
    std::cout << c4 << std::endl; 


    return 0;
}