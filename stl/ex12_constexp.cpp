#include <iostream>

constexpr int square(int x){return x * x;}

template<typename T>
auto process (T value){
    if constexpr (std::is_integral_v<T>){
        return value + 1;
    }
    else {
        return value + 0.5;
    }
}

using namespace std;
int main()
{
    constexpr int result = square(5);
    cout << result << endl;
    cout << process(10) << endl;
    cout << process(5.0) << endl;

    return 0;
}