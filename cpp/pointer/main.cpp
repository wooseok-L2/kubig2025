#include <iostream>

int main()
{
    int a = 0x12345678;

    //char *p = static_cast<char *p>(&a);
    char *p = reinterpret_cast<char *>(&a);


    printf("0x%x \n", *p);

    return 0;
}