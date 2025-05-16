import zmq

# ZeroMQ 컨텍스트 생성
context = zmq.Context()
socket = context.socket(zmq.REP)  # 요청-응답 패턴 사용
socket.bind("tcp://*:5555")  # 포트 5555에서 대기

print("서버 시작...")

while True:
    message = socket.recv_string()  # 클라이언트로부터 메시지 수신
    print(f"받은 메시지: {message}")

    response = f"서버 응답: {message.upper()}"
    socket.send_string(response)  # 응답 전송