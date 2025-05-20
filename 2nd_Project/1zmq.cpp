#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ); // 요청-응답 패턴 사용
    socket.connect("tcp://192.168.0.54:5511"); // 서버 연결

    // 조건문으로 RFID 넘버가 존재하면 쿼리문에 RFID 넘버만 변수로 받아서 넣으면 될 것 같음
    // RFID를 미리 sql에 등록 후 UPDATE 문으로 해당 RFID 넘버의 데이터를 수정하는 형태로 가야할 듯..?
    // std::string message = "INSERT INTO parking_log (RFID_num, entry_time, current_status) VALUES ('3456789012', NOW(), 'In');";
    std::string message = "UPDATE parking_log SET exit_time = NOW(), total_usage_time = SEC_TO_TIME(TIMESTAMPDIFF(SECOND, entry_time, NOW())), current_status = 'Out' WHERE RFID_num = '3456789012' AND current_status = 'In';";
    // std::string message = "INSERT INTO parking_slots (slot_number, status) VALUES ('A2', 'Empty'), ('A3', 'Empty');";
    // std::string message = "UPDATE parking_slots SET status = 'Occupied', entry_time = NOW(), exit_time = NULL WHERE slot_number = 'A2';";
    // std::string message = "UPDATE parking_slots SET status = 'Empty', exit_time = NOW() WHERE slot_number = 'A1';";
    zmq::message_t request(message.size());
    memcpy(request.data(), message.c_str(), message.size());

    socket.send(request, zmq::send_flags::none); // 메시지 전송

    zmq::message_t reply;
    zmq::recv_result_t result = socket.recv(reply, zmq::recv_flags::none);
    if (result.has_value()) {
        std::cout << "Received message size: " << result.value() << std::endl;
    } // 응답 수신
    std::cout << "서버 => " << std::string(static_cast<char*>(reply.data()), reply.size()) << std::endl <<std::flush;

    return 0;
}