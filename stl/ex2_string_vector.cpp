#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> sv;
    string name;
    cout << "Enter 5 names" << endl;

    for (int i = 0; i < 5; i++){
        cout << i + 1 << ">>";
        getline(cin, name);
        sv.push_back(name);
    }
    name = sv.at(0);
    for (int i = 0; i < sv.size(); i++){
        if(name < sv[i])
            name = sv[i];
    }
    cout << "name is :" << name << endl;

    return 0;
}