#include "processor.hpp"
#include <iostream>
using namespace std;

constexpr int factorial(int n)
{
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main()
{
    // constexpre 테스트
    constexpr int fact = factorial(5); // 컴파일 타임 계산!
    cout << "Factorial(5)" << fact << endl;

    // 범위 기반 for 문
    vector<string> input = {"hello", "", "world"};
    Processor proc(input);

    auto transformed = proc.transform();
    cout << "transformed 데이타: " << endl;
    for (const auto &s : transformed)
        cout << s << endl;

    // if contexpr 테스트
    cout << "Compute tests: " << endl;
    cout << "Int 10 : " << proc.compute(10) << endl;
    cout << "Float 10.0 : " << proc.compute(10.0) << endl;
    cout << "String 'test' : " << proc.compute("test") << endl;

    // nullptr 테스트
    string *ptr = nullptr; // 초기화
    cout << "Pointer is : " << (ptr == nullptr ? "null" : "non-null") << endl;
    string a = "Non nullptr!!!";
    ptr = &a;
    cout << "Pointer is : " << (ptr == nullptr ? "null" : "non-null") << endl;
    return 0;
}