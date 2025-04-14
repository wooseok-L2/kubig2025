#include <iostream>
#include "complex.h"

int main()
{
    Complex c1;
    // Complex c2(3.0);         
    Complex c2 = 3.0;
    Complex c3(3.0, 4.0);    

    // c1.setreal(c3.getreal());
    // c1.setimag(c3.getimag());
    c1 = c3;      // operator = (c1, c3) or c1.operator = c3;
    // c1 = &c3;     //c1.operator = (&c3);


    // if (c1.getreal() == c3.getreal() && c1.getimag() == c3.getimag()){
    if (c1 == c3){      // operator == (C1, c3) or c1.operator == (c3)
        std::cout << "c1 and c3 are equal" << std::endl;
    }
    else {
        std::cout << "c1 and c3 are not equal" << std::endl;
    }

    std::cout << "c1 : (" << c1.getreal() << ", " << c1.getimag() << "i)" << std::endl;
    std::cout << "c2 : (" << c2.getreal() << ", " << c2.getimag() << "i)" << std::endl;
    std::cout << "c3 : (" << c3.getreal() << ", " << c3.getimag() << "i)" << std::endl;

    return 0;
}