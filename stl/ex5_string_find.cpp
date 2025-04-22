#include <iostream>
#include <string>

using namespace std;

int main()
{
    string sentence;
    cout << "enter sentence : " << endl;
    getline(cin, sentence, '\n');

    string find_character, replace_character;

    cout << endl << "find : ";
    getline(cin, find_character, '\n');
    cout << "replace : ";
    getline(cin, replace_character, '\n');

    int index = 0;

    while(true){
        int index = sentence.find(find_character, index);
        if (index == -1) break;
        sentence.replace(index, find_character.length(), replace_character);
    }

    cout << sentence << endl;

    return 0;
}