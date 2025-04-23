#include <iostream>
#include <memory>

using namespace std;

void useShared(shared_ptr<int> ptr)
{
    cout << "use count received ptr : " << ptr.use_count() << endl;
}

int main()
{
    auto a = make_shared<int>(100);
    auto b = a;  // 포인터에대한 참조 생김
    auto c = a;

    useShared(move(a));

    cout << "a use_count : " << a.use_count() << endl;
    cout << "b use_count : " << b.use_count() << endl;

    return 0;
}