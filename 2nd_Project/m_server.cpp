#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <zmq.hpp>
#include <iostream>

#define PORT 5511  // ESP8266과 연결할 포트
#define BUFFER_SIZE 1024  // 데이터 버퍼 크기

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // TCP 소켓 생성
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "소켓 생성 실패" << std::endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓 바인딩
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "소켓 바인딩 실패" << std::endl;
        return -1;
    }

    // 클라이언트 연결 대기
    if (listen(server_fd, 1) < 0) {
        std::cerr << "클라이언트 연결 대기 실패" << std::endl;
        return -1;
    }

    std::cout << "TCP 서버 실행 중... 포트: " << PORT << std::endl;

    // 클라이언트 연결 수락
    client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket < 0) {
        std::cerr << "클라이언트 연결 실패" << std::endl;
        return -1;
    }
    
    std::cout << "ESP8266 연결 성공!" << std::endl;

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ); // 요청-응답 패턴 사용
    socket.connect("tcp://localhost:6511"); // 서버 연결
    std::cout << "Main Server 연결 성공!" << std::endl;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);

        if (bytesReceived <= 0) {
            std::cerr << "클라이언트 연결 끊어짐." << std::endl;
            break;
        }
        else
        {
            std::cout << "수신된 메시지: " << buffer << std::endl;
            std::string response = "Data received!";

             // 문자열 변환 및 가공
            std::string receivedData(buffer);
            std::cout << "변환된 데이터: " << receivedData << std::endl;


            send(client_socket, response.c_str(), response.length(), 0);

            zmq::message_t request(receivedData.size());
            memcpy(request.data(), receivedData.c_str(), receivedData.size());

            socket.send(request, zmq::send_flags::none); // 메시지 전송

            zmq::message_t reply;
            zmq::recv_result_t result = socket.recv(reply, zmq::recv_flags::none);
            if (result.has_value()) {
                std::cout << "Received message size: " << result.value() << std::endl;
            } // 응답 수신
            std::cout << "서버 => " << std::string(static_cast<char*>(reply.data()), reply.size()) << std::endl <<std::flush;
        }
    }

    close(client_socket);
    close(server_fd);
    return 0;
}

