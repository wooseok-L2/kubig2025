#include <iostream>
#include <future>
#include <chrono>
#include <vector>

using namespace std;

int slowAdd(int a, int b)
{
    for (int i = 0; i < 5; i++){
        cout << "slowadd working" << a << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    return a + b;
}

int main()
{
    vector<future<int>> result;
    for (int i = 0; i < 4; i++){
    
        result.push_back(async(slowAdd, i + 1, 3));
    }
    cout << "cal.... " << endl;
    for (int i = 0; i < 4; i++){

        cout << "result : " << result[i].get() << endl;
    }

    return 0;
}