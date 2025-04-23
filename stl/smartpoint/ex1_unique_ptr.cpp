#include <iostream>
#include <memory>

using namespace std;

class Myclass
{
public:
    int test_a;
    Myclass() 
    { 
        cout << "Myclass created" << endl;
        test_a = 100;
    }
    ~Myclass() { cout << "Myclass deleted" << endl; }
};


int main()
{
    // unique_ptr<Myclass> ptr = make_unique<Myclass>();
    auto ptr = make_unique<Myclass>();  // made in heap memory
    //ptr->test_a = 100;
    cout << ptr->test_a << endl;

    return 0;
}