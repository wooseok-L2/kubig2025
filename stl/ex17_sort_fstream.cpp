#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Student
{
public: 
    string name;
    int sub1;
    int sub2;
    int sub3;
    int sub4;
    int sub5;   

    int totalscore() const { return sub1+sub2+sub3+sub4+sub5; }
    int avescore() const { return totalscore() / 5; }

    void print() const { 
        cout << name << endl; 
        cout << sub1 << " " << sub2 << " " << sub3 << " " << sub4 << " " << sub5 << endl; 
        cout << "total " << totalscore() << endl;
        cout << "average " << avescore() << endl;
        cout << "--------------------------------------" << endl;
    }
};

int main()
{
    ifstream file("/home/lws/kulws2025/kubig2025/stl/10.txt");
    vector<Student> students;

    string name;
    int s1, s2, s3, s4, s5;

    while (file >> name >> s1 >> s2 >> s3 >> s4 >> s5) {
        students.push_back({name, s1, s2, s3, s4, s5});
    }

    file.close();

    for (const auto& student : students){
        cout << student.name << " ";
    }
    cout << endl;

    sort(students.begin(), students.end(), [](const Student& a, const Student& b){return a.totalscore() < b.totalscore();});

    for (const auto& student : students){
        student.print();
    }

    return 0;
}
