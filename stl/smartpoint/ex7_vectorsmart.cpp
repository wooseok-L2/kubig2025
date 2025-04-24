#include <memory>
#include <vector>
#include <iostream>

using namespace std;

class Data
{
public:
    int value;
    Data(int v) : value(v) {}


};

int main()
{
    vector<shared_ptr<Data>> dataList;
    dataList.push_back(make_shared<Data>(1));
    dataList.push_back(make_shared<Data>(2));

    // shared_ptr<vector<Data>> dataList2;
    // dataList2->push_back(Data(10));
    // dataList2->push_back(Data(20));

    for (const auto &d : dataList)
        cout << d->value << endl;
    
    // for (const auto &d : *dataList2)
    //     cout << d->value << endl;
    

    return 0;
}