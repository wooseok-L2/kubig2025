#include <iostream>
#include <utility>
#include <string>

using namespace std;

void process(string&& s){
    cout << "Rvalue : reference : " << s << endl;
}

void wrapper(string&& s){

    process(forward<string> (s));
}

int main() 
{
    wrapper(string("hello, world!!"));

    return 0;
}