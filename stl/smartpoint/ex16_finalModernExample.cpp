// 목표 : STL 과 스마트포인터를 사용해서 데이터베이스 엔진 만드세요.
// 스마트 포인터 활용 shared_ptr, unique_ptr
// 쓰레드 활용 multithread, mutex, atomic -> 내부 동기화 위한 락 구조 설계
// 데이터 삽입 insert(key(int), value(string));
// 데이터 검색 find(key);
// 데이터 삭제 remove(key);
// class DataBase
// 저장용 컨테이너 - unordered_map 참조에 특화된!!
// 컬럼 추가(타입 정하기) - .. 도전 하실분만!
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
using namespace std;

class DataBase
{
private:
    unordered_map<int, shared_ptr<string>> db;
    mutable shared_mutex mtx;

public:
    void insert(int key, const string &value)
    {
        unique_lock lock(mtx);
        db[key] = make_shared<string>(value);
    }
    shared_ptr<string> find(int key) const
    {
        shared_lock lock(mtx);
        auto it = db.find(key);
        return (it != db.end()) ? it->second : nullptr;
    }
    void remove(int key)
    {
        unique_lock lock(mtx);
        db.erase(key);
    }
    void printAll() const
    {
        shared_lock lock(mtx);
        for (const auto &[key, value] : db)
        {
            cout << key << " : " << *value << endl;
        }
    }
};

void threadTask(DataBase &db, int id)
{
    for (int i = 0; i < 5; ++i)
    {
        db.insert(id * 10 + i, "Data from main" + to_string(id));
        this_thread::sleep_for(50ms);
    }
}

int main()
{
    DataBase db;
    vector<thread> threads;
    for (int i = 0; i < 20; ++i)
        threads.emplace_back(threadTask, ref(db), i);
    // db.remove(4);
    // db.remove(8);
    cout << "find 3 : " << db.find(3) << endl;
    // cout << "find 4 : " << db.find(4) << endl;
    for (auto &t : threads)
        t.join();
    db.printAll();
    return 0;
}