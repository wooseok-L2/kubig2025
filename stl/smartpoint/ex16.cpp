// 목표 : STL 과 스마트 포인터를 사용해서 데이터베이스 엔진 만들기
// 스마트 포인터 활용 shared_ptr, unique_ptr
// thread 활용 : multithread, mutex, atomic -> 내부 동기화 위한 락 구조 설계 ( 락 함수 )
// 데이터 삽입 insert(key(int), value(string));
// 데이터 검색 find(key);
// 데이터 삭제 remove(key);
// class Database
// 저장용 컨테이너 : std::unordered_map
// 컬럼 추가(타입 정하기) - 시간 남으면


#include <iostream>
#include <unordered_map>
#include <string>
#include <mutex>
#include <memory>
#include <optional>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

class Database {
private:
    unordered_map<int, shared_ptr<string>> data_;
    mutable mutex mtx_;
    atomic<bool> running_{true};

public:
    void insert(int key, const string& value) {
        lock_guard<mutex> lock(mtx_);
        data_[key] = make_shared<string>(value);
        cout << "[Insert] " << key << " : " << value << endl;
    }

    optional<shared_ptr<string>> find(int key) {
        lock_guard<mutex> lock(mtx_);
        auto it = data_.find(key);
        if (it != data_.end())
            return it->second;
        return nullopt;
    }

    void remove(int key) {
        lock_guard<mutex> lock(mtx_);
        if (data_.erase(key))
            cout << "[Remove] " << key << " removed." << endl;
        else
            cout << "[Remove] " << key << " not found." << endl;
    }

    void showAll() const {
        lock_guard<mutex> lock(mtx_);
        if (data_.empty()) {
            cout << "[Show] 현재 데이터 없음." << endl;
            return;
        }
        cout << "[Show] 현재 저장된 데이터 목록:" << endl;
        for (const auto& [key, value] : data_) {
            cout << "  " << key << " : " << *value << endl;
        }
    }

    void stop() {
        running_ = false;
    }

    bool isRunning() const {
        return running_;
    }
};

void userInterface(Database& db) {
    string command;
    while (db.isRunning()) {
        cout << "\n명령 입력 (insert, find, remove, show, exit): ";
        cin >> command;

        if (command == "insert") {
            int key;
            string value;
            cout << "키 (int): ";
            cin >> key;
            cout << "값 (string): ";
            cin >> ws;
            getline(cin, value);
            db.insert(key, value);
        } else if (command == "find") {
            int key;
            cout << "찾을 키: ";
            cin >> key;
            auto result = db.find(key);
            if (result)
                cout << "[Find] " << key << " : " << *(*result) << endl;
            else
                cout << "[Find] " << key << " not found." << endl;
        } else if (command == "remove") {
            int key;
            cout << "삭제할 키: ";
            cin >> key;
            db.remove(key);
        } else if (command == "show") {
            db.showAll();
        } else if (command == "exit") {
            db.stop();
            cout << "프로그램 종료!" << endl;
        } else {
            cout << "알 수 없는 명령입니다." << endl;
        }
    }
}

int main() {
    Database db;
    userInterface(db);
    return 0;
}