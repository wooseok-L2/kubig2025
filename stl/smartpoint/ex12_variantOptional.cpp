//  g++ -std=c++17 ex12_vriantOptional.cpp -o ex12_vriantOptional
#include <any>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
using namespace std;
int main()
{
    variant<int, string> data;
    // 데이터가 하나의 메모리에 저장될 때
    // 타입이 여러가지 일 경우
    data = 42;
    cout << get<int>(data) << endl;
    data = string("hello");
    cout << get<string>(data) << endl;

    optional<int> maybeInt; // 값이 있을 수도 있고 없을 수 있는 상황
    maybeInt = 10;
    if (maybeInt)
        cout << *maybeInt << endl;

    any anything = 123;
    cout << any_cast<int>(anything) << endl;
    anything = string("hi");
    cout << any_cast<string>(anything) << endl;
    anything = 1.1;
    cout << any_cast<double>(anything) << endl;
    return 0;
}