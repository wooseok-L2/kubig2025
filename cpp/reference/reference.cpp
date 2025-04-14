#include <iostream>

int main()
{
    int a;
    a = 100;
    int &r = a;
    
    r = 200;
    std::cout << a << std::endl;

    return 0;
}