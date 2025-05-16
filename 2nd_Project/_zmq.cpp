#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ); // 요청-응답 패턴 사용
    socket.connect("tcp://localhost:5555"); // 서버 연결

    std::string message = "Hello from C++";
    zmq::message_t request(message.size());
    memcpy(request.data(), message.c_str(), message.size());

    socket.send(request); // 메시지 전송

    zmq::message_t reply;
    socket.recv(&reply); // 응답 수신
    std::cout << "서버 응답: " << std::string(static_cast<char*>(reply.data()), reply.size()) << std::endl;

    return 0;
}