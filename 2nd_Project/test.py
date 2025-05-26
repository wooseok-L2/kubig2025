from mfrc522 import SimpleMFRC522
from gpiozero import Servo
from time import sleep
import zmq
import spidev

# ZeroMQ 소켓 설정
context = zmq.Context()
print("ZeroMQ 컨텍스트 생성 완료...")
socket = context.socket(zmq.REQ)
try:
    socket.connect("tcp://192.168.0.54:6512")  # 서버 연결
    print("ZeroMQ 서버 연결 완료")
except zmq.ZMQError as e:
    print(f"서버 연결 실패: {e}")
    exit(1)

# 서보모터 설정
servo = Servo(26)  # GPIO 26 사용 (BCM 기준, Physical pin 37)

# RFID 리더기 초기화
reader = SimpleMFRC522()

print("RFID Sensor on. Tag RFID")
pre_id = None  # 이전 RFID 값을 저장할 변수

# 차량 입차 함수
def car_in(rfid_id):
    message = f"INSERT INTO parking_log (RFID_num, entry_time, current_status) VALUES ({rfid_id}, NOW(), 'In');"
    socket.send_string(message)  # 요청 전송
    response = socket.recv_string()  # 응답 수신
    print(f"Server Response: {response}")

# 차량 출차 함수
def car_out(rfid_id):
    message = f"UPDATE parking_log SET exit_time = NOW(), total_usage_time = SEC_TO_TIME(TIMESTAMPDIFF(SECOND, entry_time, NOW())), current_status = 'Out' WHERE RFID_num = {rfid_id} AND current_status = 'In';"
    socket.send_string(message)  # 요청 전송
    response = socket.recv_string()  # 응답 수신
    print(f"Server Response: {response}")

# RFID 태그 감지 루프
try:
    while True:
        rfid_id, _ = reader.read()
        print(f"Detected RFID: {rfid_id}")

        # 서보모터 90도 회전
        servo.max()
        sleep(1)

        # 일정 시간 대기 후 원위치 복귀
        sleep(5)
        servo.min()
        sleep(1)

        # RFID 태그 판별하여 입출차 처리
        if pre_id is None or pre_id != rfid_id:  # 새로운 태그일 경우 입차
            car_in(rfid_id)
            pre_id = rfid_id
        else:  # 동일 태그 연속 인식 시 출차 처리
            sleep(2)  # 짧은 대기 후 재확인
            new_rfid_id, _ = reader.read()
            if new_rfid_id == pre_id:  # 태그값이 동일하면 출차 처리
                car_out(rfid_id)
                pre_id = None  # 출차 후 ID 초기화

except KeyboardInterrupt:
    print("\nInterrupt End")
