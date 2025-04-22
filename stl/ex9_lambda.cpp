#include <iostream>
#include <vector>
using namespace std;

class Adder
{
public:
    int offset;
    Adder(int o) : offset(o) {};
    int operator()(int x) const { return x + offset; }
};

int main()
{
    double pi = 3.1415926535;
    auto calc = [&pi](int r) -> double
    {
        pi = 30;
        return pi * r * r; };
    cout << "면적은 " << calc(3) << endl;
    cout << "Pi 의 값은 : " << pi << endl;

    int sum = 0;
    auto calc2 = [&sum](int x, int y)
    { sum = x + y; };
    calc2(2, 3);
    cout << "합은 : " << sum << endl;

    auto calc3 = [&](int x, int y)
    { sum = x + y + pi; };
    calc3(2, 3);
    cout << "합은 : " << sum << endl;

    // vector<int> test;
    // test();
    Adder addObject(4);
    cout << addObject(10) << endl;
    return 0;
}