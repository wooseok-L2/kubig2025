#include <iostream>
#include <array>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>
#include <string>

// fixed size array / slower than nomal array but fastest of STL

using namespace std;
int main()
{   
    array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (const auto& x : arr)
        cout << x << " ";
    cout << endl;

    // deque can insert/delete both sides and it is malloc size(flexiable)
    deque<int> dq = {1, 2, 3};
    dq.push_back(4);
    dq.push_front(0);
    dq.emplace_back(5);      // more stable than push
    dq.emplace_front(-1);
    dq.insert(dq.begin() + 3, 2.5);

    for (const auto &v : dq){
        cout << v <<  " ";
    }
    cout << endl;

    dq.pop_back();
    dq.pop_front();

    for (const auto &v : dq){
        cout << v <<  " ";
    }
    cout << endl;
    
    // list  / specialized for insert/delete
    list<int> lst = {1, 2, 3};
    auto it = lst.begin();
    it++;
    it++;
    it++;
    
    lst.insert(lst.begin(), 3);
    for (const auto &v : lst){
        cout << v << " ";
    }
    cout << endl;

    //set
    set<int> s = {3, 1, 2, 2, 1};
    for (const auto& v : s)
        cout << v << " ";
    cout << endl;
    cout << "size of s : " << s.size() << endl;

    // unordered_map
    // materials based on hash table -> very super fast access
    // sha256.. -> it means it would be hash table 
    unordered_map<std::string, int> um = {{"apple", 100}, {"banana", 150}, {"mango", 200}};
    
    // if you get all, map would be more fast. so just use map
    for (const auto& [key, val] : um){
        cout << key << " : " << val << endl;
    }

    // reference is fast
    cout << um["apple"] << endl;

    return 0;
}