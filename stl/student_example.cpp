// 학생들의 이름과 점수를 저장한 클래스로 벡터를 이용해서 정렬하는 프로그램.
// 정렬 기준은 내림차순(높은 점수가 앞에) 점수가 같으면 이름 오름차순
// algorithm 에서는 stable_sort 변경!
// 데이터는 1000.txt 테스트.
// 참고 - sort_fstream2.cpp
// 학점 grade private -> A(<=100), B(<90), C(<80), D(<70), F(<60)
// -> print() 에 표현 될 수 있게 변경.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Student
{
private:
    string name_;
    vector<int> scores_;
    char grade_;
    string a = "FFFFFFDCBAA";

public:
    Student(const string &name, const vector<int> scores) : name_(name), scores_(scores)
    {
        int avg = averageScore();
        grade_ = a[avg / 10];
    }

    int totalScore() const
    {
        return accumulate(scores_.begin(), scores_.end(), 0);
    }
    int averageScore() const
    {
        return totalScore() / scores_.size();
    }
    const string &name() const
    {
        return name_;
    }
    void print() const
    {
        cout << "이름 : " << name_ << endl;
        cout << "점수 : ";
        for (const auto &v : scores_)
            cout << v << " ";
        cout << endl;
        cout << "총점 : " << totalScore() << endl;
        cout << "평균 : " << averageScore() << " ( " << grade_ << " ) " << endl;
        cout << "-----------------------------------------" << endl;
    }
    bool operator<(const Student &other) const
    {
        return totalScore() < other.totalScore(); // 총점이 낮은 학생이 "더 작다"
    }
};

int main()
{
    ifstream file("/home/lws/kulws2025/kubig2025/stl/1000.txt");
    vector<Student> students;

    string line, name;
    vector<int> scores;
    int score;

    while (getline(file, line))
    {
        istringstream iss(line);
        iss >> name;
        while (iss >> score)
            scores.push_back(score);
        students.emplace_back(name, scores);
        scores.clear();
    }
    file.close();

    stable_sort(students.begin(),
                students.end(),
                [](const Student &a, const Student &b)
                {
            if(a.averageScore() != b.averageScore())
                return a.averageScore() < b.averageScore();
            return a.name() < b.name(); });

    // partition
    auto fail_bound = partition(students.begin(), students.end(), [](const Student &st)
                                { return st.averageScore() < 60; });
    cout << (*fail_bound).averageScore() << endl;
    vector<Student> fail_students(students.begin(), fail_bound);
    vector<Student> success_students(fail_bound, students.end());

    for (const auto &student : fail_students)
        student.print();

    cout << "합격 : " << endl;

    for (const auto &student : success_students)
        student.print();
    // merge !!
    vector<Student> merge_students;
    merge(fail_students.begin(), fail_students.end(), success_students.begin(), success_students.end(), back_inserter(merge_students));

    cout << "합친 vector : " << endl;

    for (const auto &student : merge_students)
        student.print();

    return 0;
}