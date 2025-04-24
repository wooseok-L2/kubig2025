#include <iostream>
#include <future>
#include <chrono>

using namespace std;

int slowAdd(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(2));

    return a + b;
}

int main()
{
    future<int> result = async(slowAdd, 2, 3);
    cout << "cal.... " << endl;
    cout << "result : " << result.get() << endl;

    return 0;
}