#include <iostream>
#include <vector>
using namespace std;

// class A :
// public :
//     class B :

int main()
{
    vector<int> test_vector = {1, 2, 3, 4, 5, 6};

    for (vector<int>::iterator it = test_vector.begin(); it != test_vector.end(); ++it) // for 문 두번째 방식
    {
        cout << *it << endl;
    }

    // iterator 가 정의 - begin(), end()
    // *it 역참조가 가능해야 한다.
    for (auto v : test_vector) // 메모리 복사 o, 값 변경 x
    {
        cout << v << endl;
    }

    for (auto &v : test_vector) // 메모리 복사 x, 값 변경 o -> 벡터 컨테이너 값 변경
    {
        cout << v << endl;
    }

    for (const auto &v : test_vector) // 메모리 복사 x, 값 변경 x  => 효율적으로 값 잠고
    {
        cout << v << endl;
    }

    return 0;
}