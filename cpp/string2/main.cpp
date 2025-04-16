#include <iostream>
#include "string.h"

int main()
{
    String s1;
    String s2 = "wonderful tonight";
    String s3 = s2;

    s1 = s2;
    s1 == s2;

    String s4 = "- eric claption";
    String s5 = s2 + s4;

    std::cout << "s1 : " << s1 << std::endl;
    std::cout << "s2 : " << s2 << std::endl;
    std::cout << "s3 : " << s3 << std::endl;
    std::cout << "s4 : " << s4 << std::endl;
    std::cout << "s5 : " << s5 << std::endl;

    return 0;
}