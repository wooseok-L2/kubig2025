#include <iostream>
#include "string.h"

int main()
{
    String s1 = "just the way you are";
    String s2 = s1;
    String s3;

    std::cout << "s1: " << s1.c_str() << ", " << s1.size() << std::endl;
    std::cout << "s2: " << s2.c_str() << ", " << s2.size() << std::endl;
    std::cout << "s3: " << s3.c_str() << ", " << s3.size() << std::endl;

    return 0;
}