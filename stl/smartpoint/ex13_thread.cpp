#include <iostream>
#include <mutex> // mutually exclusive
#include <thread>
using namespace std;

int counter = 0;
mutex mtx;

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        lock_guard<mutex> lock(mtx);
        ++counter;
    }
}

int main()
{
    thread t1(increment);
    thread t2(increment);
    // execution.
    // ...
    t1.join(); // t1 에서 실행되는 상황이 끝나면 대기하라!
    // ... main. 끝. t1 끝난상황..
    t2.join(); // t2 에서 실행 되는 사황이 끝나면 대기하라!
    // execution - main thread. t1 thread. t2 thread. 끝난다음
    cout << "최종 카운터 값: " << counter << endl;
}