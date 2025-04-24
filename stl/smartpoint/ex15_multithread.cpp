#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono_literals; // 시간 코드 넣을 때

class TaskQueue
{
private:
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    vector<thread> workers;
    atomic<bool> stop{false};

public:
    TaskQueue(size_t thread_count)
    {
        for (size_t i = 0; i < thread_count; ++i)
        {
            workers.emplace_back([this](){
                while(true){
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(mtx);
                        cv.wait(lock, [this]()
                                { return stop || !tasks.empty(); });
                        if (stop &&tasks.empty())
                            return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task(); // task 실행
                } });
        }
    }
    
    void enqueue(function<void()> task)
    {
        {
            lock_guard<mutex> lock(mtx);
            tasks.push(move(task));
        }
        cv.notify_one();
    }

    ~TaskQueue()
    {
        stop = true;
        cv.notify_all();
        for (auto &t : workers)
            t.join();
    }
};

int main()
{
    TaskQueue queue(4);
    for (int i = 0; i < 10; ++i)
    {
        queue.enqueue([i]()
                      { cout << "작업 " << i << " 시작!!!" << endl; });
    }
    this_thread::sleep_for(1s);
    return 0;
}