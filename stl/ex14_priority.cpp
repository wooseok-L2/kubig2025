#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Task
{
public:
    string name;
    int priority;

    // rhs(right hand side) lhs(left hand side) other
    bool operator<(const Task& rhs) const {
        return priority > rhs.priority;  // asc
    }
};


int main()
{   
    priority_queue<Task> scheduler;

    scheduler.push({"Write report", 2});
    scheduler.push({"Fix bug", 3});
    scheduler.push({"Email team", 1});

    cout << "working order : " << endl;
    while (!scheduler.empty()){
        Task t = scheduler.top();
        scheduler.pop();
        cout << t.name << "\t priority : " << t.priority << endl;
    }

    return 0;
}