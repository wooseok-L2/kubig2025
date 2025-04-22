#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;

    v.push_back(1);
    v.push_back(11);
    v.push_back(111);
    v.push_back(1111);
    v.push_back(11111);
    v.push_back(111111);

    // cout << "1st element of v : " << v[0] << endl;
    // cout << "2nd element of v : " << v[1] << endl;
    // cout << "3rd element of v : " << v[2] << endl;

    //vector<int>::iterator it;     //use auto
    auto it = v.begin() + 2;
    v.erase(it);
    v.at(0) = 2;
    // for
    for (int i = 0; i < v.size(); i++){
        cout << "v " << i + 1 << " elements :" << v.at(i) << endl; 
    }


    return 0;
}