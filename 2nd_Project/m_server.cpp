#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <zmq.hpp>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5511
#define BUFFER_SIZE 1024

std::vector<std::thread> clientThreads; // 클라이언트 스레드 목록

// 클라이언트 요청을 처리하는 함수
void handleClient(int client_socket, zmq::context_t& context) {
    zmq::socket_t socket_1(context, ZMQ_REQ);
    zmq::socket_t socket_2(context, ZMQ_REQ);
    zmq::socket_t socket_3(context, ZMQ_REQ);

    socket_1.connect("tcp://localhost:6511");
    socket_2.connect("tcp://localhost:6514");
    socket_3.connect("tcp://localhost:6515");
    char buffer[BUFFER_SIZE];

    while (true) {
        // 클라이언트 요청 처리
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);

        if (bytesReceived <= 0) {
            std::cerr << "클라이언트 연결 종료" << std::endl;
            close(client_socket);
            break;
        }

        std::string receivedData(buffer);
        // receivedData.erase(std::remove(receivedData.begin(), receivedData.end(), '\n'), receivedData.end());
        std::cout << "수신된 메시지: " << receivedData << std::endl;

        if (receivedData.empty()) {
            std::cerr << "받은 데이터가 빈 문자열임! 처리 건너뜀." << std::endl;
            continue;
        }

        std::string response = "Data received!\n";
        send(client_socket, response.c_str(), response.length(), 0);

        if (receivedData[0] == '2') {
            zmq::message_t request(receivedData.size());
            memcpy(request.data(), receivedData.c_str(), receivedData.size());
            socket_2.send(request, zmq::send_flags::none);

            zmq::message_t reply;
            zmq::recv_result_t result = socket_2.recv(reply, zmq::recv_flags::none);
            if (!result.has_value()) {
                std::cerr << "Receive failed" << std::endl;
            }
            std::string receivedMessage(static_cast<char*>(reply.data()), reply.size());
            std::cout << "[socket_2 응답] " << receivedMessage << std::endl;
            send(client_socket, receivedMessage.c_str(), receivedMessage.length(), 0);
        } 
        else if (receivedData[0] == 's' || receivedData[0] == 'm'){
            zmq::message_t request(receivedData.size());
            memcpy(request.data(), receivedData.c_str(), receivedData.size());
            socket_3.send(request, zmq::send_flags::none);

            zmq::message_t reply;
            zmq::recv_result_t result = socket_3.recv(reply, zmq::recv_flags::none);
            if (!result.has_value()) {
                std::cerr << "Receive failed" << std::endl;
            }
            std::string receivedMessage(static_cast<char*>(reply.data()), reply.size());
            std::cout << "[socket_3 응답] " << receivedMessage << std::endl;
            send(client_socket, receivedMessage.c_str(), receivedMessage.length(), 0);
        }
        else {
            zmq::message_t request(receivedData.size());
            memcpy(request.data(), receivedData.c_str(), receivedData.size());
            socket_1.send(request, zmq::send_flags::none);

            zmq::message_t reply;
            zmq::recv_result_t result = socket_1.recv(reply, zmq::recv_flags::none);
            if (!result.has_value()) {
                std::cerr << "Receive failed" << std::endl;
            }
            std::string receivedMessage(static_cast<char*>(reply.data()), reply.size());
            std::cout << "[socket_1 응답] " << receivedMessage << std::endl;
        }
    }
}

// 서버 실행 함수
int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "소켓 생성 실패" << std::endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "소켓 바인딩 실패" << std::endl;
        return -1;
    }

    if (listen(server_fd, 5) < 0) {
        std::cerr << "클라이언트 연결 대기 실패" << std::endl;
        return -1;
    }

    std::cout << "TCP 서버 실행 중... 포트: " << PORT << std::endl;

    zmq::context_t context(1);

    while (true) {
        std::cout << "클라이언트 연결 대기 중..." << std::endl;
        int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);

        if (client_socket < 0) {
            std::cerr << "클라이언트 연결 실패" << std::endl;
            continue;
        }

        std::cout << "클라이언트 연결됨!" << std::endl;

        // 새 클라이언트 처리 스레드 생성
        clientThreads.emplace_back(std::thread(handleClient, client_socket, std::ref(context)));
    }

    for (auto& thread : clientThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    close(server_fd);
    return 0;
}
