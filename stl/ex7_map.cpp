#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<string, string> dic = {{"power", "힘"}, {"money", "돈"}};
    dic.insert(make_pair("love", "사랑"));
    dic["cherry"] = "체리";
    
    dic.erase("love");

    cout << "number of saved words : " << dic.size() << endl;

    string eng;

    while(true){
        cout << "word to find >> ";
        getline(cin, eng);
        if (eng == "exit") break;

        if (dic.find(eng) == dic.end()) 
            cout << "none" << endl;
        else 
            cout << dic[eng] << endl;
    }

    for (const auto& [eng, kor] : dic){
        std::cout << "eng : " << eng << "\t kor : " << kor << endl;
    }



    return 0;
}