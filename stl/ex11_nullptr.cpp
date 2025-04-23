#include <iostream>
void func(int) { std::cout << "int\n"; }
void func(int *) { std::cout << "pointer\n"; }
void func(long) { std::cout << "long\n"; }

int main()
{
    int *ptr = nullptr; // 초기화
    int *fp;
    if (ptr == nullptr)
    {
        std::cout << "Null pointer" << std::endl;
    }
    func(0L);
    func(1);
    func(NULL); // nullpointer 안가짐....
    func(nullptr);
    func(ptr);
    func(fp);

    //return 0;
}