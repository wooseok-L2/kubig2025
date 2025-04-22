#include <cctype>
#include <ctime>
#include <iostream>
#include <list>

using namespace std;

void test_function(list<int> &students);

int main()
{
    list<int> students;
    string student;
    char temp;
    int grade;
    FILE *fp = fopen("/home/lws/kulws2025/kubig2025/stl/student.txt", "r");
    // ifstream fin("/home/aa/kuBig2025/stl/studnet.txt");

    while (fread(&temp, sizeof(char), 1, fp))
    {

        if (isdigit(temp))
            student.push_back(temp);
        else if (!student.empty())
        {
            grade = stoi(student);
            students.push_back(grade);
            student.clear();
        }
    }

    if (!student.empty())
    {
        grade = stoi(student);
        students.push_back(grade);
    }

    for (auto v : students)
        cout << v << endl;

    fclose(fp);

    auto count = students.size();

    // vector 의 연산 시간!!
    double begin = clock();
    test_function(students);
    double end = clock();

    cout << "벡터를 연산하는 시간은 " << count << " 데이터 사이즈" << endl;
    cout << "지워진 데이터의 숫자는 " << count - students.size() << endl;
    cout << (end - begin) / CLOCKS_PER_SEC << "초" << endl;
}

void test_function(list<int> &students)
{
    list<int>::iterator it = students.begin();
    while (it != students.end())
    {
        if (*it < 60)
        {
            it = students.erase(it);
        }
        else
        {
            ++it;
        }
    }
}