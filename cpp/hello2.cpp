#include <iostream>
#include <cstring>

int main()
{
    std::string s1;
    std::string s2 = "hello, ";

    s1 = s2;
    s1 = s1 + "world";

    std::cout << s1 << std::endl;
    std::cout << s1.size() << std::endl;

    return 0;
}