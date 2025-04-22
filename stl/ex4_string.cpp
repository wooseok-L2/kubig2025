#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cout << "enter sentence : " << endl;
    getline(cin, s, '\n');
    for (auto c : s) {
        string first = s.substr(0, 1);
        string sub = s.substr(1, s.size() - 1);
        s = sub + first;
        cout << s << endl;
    }

    return 0;
}