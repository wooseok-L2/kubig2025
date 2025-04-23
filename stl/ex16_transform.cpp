#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    vector<int> evens;  //

    copy_if(nums.begin(), nums.end(), back_inserter(evens), [](int x){return x % 2 == 0;});

    vector<int> squares(evens.size());
    transform(evens.begin(), evens.end(), squares.begin(), [](int x){return x * x;});

    cout << "짝수의 제곱 : " ;
    for (const auto& v : squares)
        cout << v << " ";
    cout << endl;

    return 0;
}