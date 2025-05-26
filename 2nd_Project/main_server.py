# export DISPLAY=:0
import zmq
import gui
import sys
import threading

# 프로그램 종료 함수
def exit_program():
    print("프로그램 종료...")
    socket_in.close()
    socket_out.close()
    socket_RC.close()
    socket_stop.close()
    socket_parking.close()  # ZeroMQ 소켓 닫기
    context.term()   # ZeroMQ 컨텍스트 종료
    conn.close()     # 데이터베이스 연결 닫기
    gui.root.quit()  # Tkinter 창 닫기
    sys.exit()       # 전체 프로그램 종료  
    
# ZeroMQ 컨텍스트 생성
print("프로그램 시작...")

context = zmq.Context()
print("ZeroMQ 컨텍스트 생성 완료...")

# parking out 데이터 수신용 ZeroMQ 소켓
socket_in = context.socket(zmq.REP)
socket_in.bind("tcp://*:6512")
print("IN 소켓 바인딩 완료...")

# parking out 데이터 수신용 ZeroMQ 소켓
socket_out = context.socket(zmq.REP)
socket_out.bind("tcp://*:6513")
print("OUT 소켓 바인딩 완료...")

# RC car 데이터 수신용 ZeroMQ 소켓
socket_RC = context.socket(zmq.REP)
socket_RC.bind("tcp://*:6514")
print("RC car 소켓 바인딩 완료...")

# # RC car stop 수신용 ZeroMQ 소켓
socket_stop = context.socket(zmq.REP)
socket_stop.bind("tcp://*:6515")
print("stop 소켓 바인딩 완료...")

# 주차칸 상태 수신용 ZeroMQ 소켓
socket_parking = context.socket(zmq.REP)
socket_parking.bind("tcp://*:6511")
print("주차칸 소켓 바인딩 완료...")

conn = gui.sql.sql_connect()
print("SQL연결 완료...")

gui.update_parking()
gui.update_rc()

def send_initial_rfid_list_in():
    try:
        cursor = conn.cursor()
        query = "SELECT RFID_num FROM parking_log WHERE current_status = 'In';"
        cursor.execute(query)
        pre_id = [row[0] for row in cursor.fetchall()]  # 현재 입차 차량 RFID 리스트
        
        initial_data = ",".join(pre_id)
        
        # ZeroMQ 소켓에 대한 예외 처리 추가
        if socket_in and not socket_in.closed:
            try:
                socket_in.send_string(initial_data)
                print(f"초기 RFID 리스트 전송: {initial_data}")
            except zmq.ZMQError as e:
                print(f"ZMQ 오류 발생: {e}")
    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")
        
def send_initial_rfid_list_out():
    try:
        cursor = conn.cursor()
        query = "SELECT RFID_num FROM parking_log WHERE current_status = 'In';"
        cursor.execute(query)
        pre_id = [row[0] for row in cursor.fetchall()]  # 현재 입차 차량 RFID 리스트
        
        initial_data = ",".join(pre_id)
        
        # ZeroMQ 소켓에 대한 예외 처리 추가
        if socket_out and not socket_out.closed:
            try:
                socket_out.send_string(initial_data)
                print(f"초기 RFID 리스트 전송: {initial_data}")
            except zmq.ZMQError as e:
                print(f"ZMQ 오류 발생: {e}")
    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")
        
def parking_in():
    try:
        cursor = conn.cursor()
        query = "SELECT count(*) FROM parking_slots WHERE status = 'Empty';"
        cursor.execute(query)
        slots = cursor.fetchone()  

        # 리스트를 문자열로 변환하여 클라이언트에게 전송
        socket_in.send_string(str(slots[0]))  # 클라이언트로 데이터 전송
        print(f"주차칸 데이터 전송: {str(slots[0])}")

    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")  
        
def rc_stop():
    try:
        # 정지신호 전송
        try:
            cursor = conn.cursor()
            query = "INSERT INTO rc_stop (status, stop_time) VALUES ('stop', NOW());"
            cursor.execute(query) 
            conn.commit()  # 변경 사항 저장
            print("stop 트랜잭션 정상 완료")
        except gui.sql.pymysql.MySQLError as e:
            print(f"....오류 발생: {e}")
        finally:
            gui.update_parking()
        
    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")

def rc_move():
    try:
        # move신호 전송
        try:
            cursor = conn.cursor()
            query = "INSERT INTO rc_stop (status, move_time) VALUES ('moving', NOW());"
            cursor.execute(query) 
            conn.commit()  # 변경 사항 저장
            print("move 트랜잭션 정상 완료")
        except gui.sql.pymysql.MySQLError as e:
            print(f"....오류 발생: {e}")
        finally:
            gui.update_parking()
        
    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")
        
def parking_out(rfid_id):
    try:
        cursor = conn.cursor()
        query = f"SELECT total_usage_time FROM parking_log WHERE RFID_num = {rfid_id} ORDER BY exit_time DESC LIMIT 1;"
        cursor.execute(query)
        conn.commit()  # 변경 사항 저장
        usage_time = cursor.fetchone() # 현재 입차 차량 RFID 리스트
        if usage_time:  # 데이터가 존재하는 경우
            socket_out.send_string(str(usage_time[0]))  # 클라이언트로 데이터 전송
            print(f"usage_time 데이터 전송: {str(usage_time[0])}")
        else:
            response = "NOT_FOUND"  # 데이터가 없을 경우 예외 처리
            socket_out.send_string(response)  # ZeroMQ를 통해 데이터 전송
            print(f"전송된 데이터: {response}")
    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")      

def parking_in_listen(): 
    while True:
        message = socket_in.recv_string()  # 클라이언트로부터 메시지 수신
        print(f"받은 메시지: {message}")
        # 클라이언트가 초기 RFID 리스트 요청 시 처리
        if message == "INIT_REQUEST":
            send_initial_rfid_list_in()
            continue  # 이후 로직을 실행하지 않고 다음 요청을 기다림
        elif message == "REQUEST_SLOTS":
            parking_in()
            continue   
        response = f"response: {message.upper()}"
        socket_in.send_string(response)  # 응답 전송          
        try:
            cursor = conn.cursor()
            cursor.execute(message)  # SQL 인젝션 위험 (보완 필요)
            conn.commit()  # 변경 사항 저장
            print("RFID 트랜잭션 정상 완료")
        except gui.sql.pymysql.MySQLError as e:
            print(f"!!!오류 발생: {e}")
            conn.rollback()
        finally:
            gui.update_parking()
            
        if not gui.root.winfo_exists():
            exit_program()
            break
        
def parking_out_listen():
    while True:
        message = socket_out.recv_string()  # 클라이언트로부터 메시지 수신
        print(f"받은 메시지: {message}")
        # 클라이언트가 초기 RFID 리스트 요청 시 처리
        if message == "INIT_REQUEST":
            send_initial_rfid_list_out()
            continue  # 이후 로직을 실행하지 않고 다음 요청을 기다림
        elif message.startswith("REQUEST_USAGE_TIME,"):
            rfid_id = message.split(",", 1)[1]  # 쉼표 기준으로 분리하여 RFID 값 가져오기
            parking_out(str(rfid_id))
            continue
        response = f"response: {message.upper()}"
        socket_out.send_string(response)  # 응답 전송
        try:
            cursor = conn.cursor()
            cursor.execute(message)  # SQL 인젝션 위험 (보완 필요)
            conn.commit()  # 변경 사항 저장
            print("RFID 트랜잭션 정상 완료")
        except gui.sql.pymysql.MySQLError as e:
            print(f"....오류 발생: {e}")
            conn.rollback()
        finally:
            gui.update_parking()
            
        if not gui.root.winfo_exists():
            exit_program()
            break

def status_rc_listen():
    while True:
        message = socket_stop.recv_string()  # 클라이언트로부터 메시지 수신
        print(f"받은 메시지: {message}")
        
        response = f"response: {message.upper()}"
        socket_stop.send_string(response)  # 응답 전송
        
        if message == 'stop':
            rc_stop()
        elif message == "moving":
            rc_move()
            
        gui.update_rc()

        if not gui.root.winfo_exists():
            exit_program()
            break

def parking_rc():
    try:
        cursor = conn.cursor()
        query = "SELECT count(*) FROM parking_slots WHERE status = 'Empty';"
        cursor.execute(query)
        slots = cursor.fetchone()  

        # 리스트를 문자열로 변환하여 클라이언트에게 전송
        if slots[0] == 0:
            response = 'full'
            socket_RC.send_string(response)  # 클라이언트로 데이터 전송
            print(f"rc 데이터 전송: {response}")
        else:
            response = 'empty'
            socket_RC.send_string(response)  # 클라이언트로 데이터 전송
            print(f"rc 데이터 전송: {response}")

    except gui.sql.pymysql.MySQLError as e:
        print(f"초기 데이터 조회 오류: {e}")  

def parking_RC_listen():
    while True:
        message = socket_RC.recv_string()  # 클라이언트로부터 메시지 수신
        print(f"받은 메시지: {message}")
        
        parking_rc()

        if not gui.root.winfo_exists():
            exit_program()
            break

# 주차칸 상태 데이터 처리 함수
def parking_status_listen():
    while True:
        message = socket_parking.recv_string()
        print(f"주차칸 데이터 수신: {message}")
        
        response = f"주차칸 response: {message.upper()}"
        socket_parking.send_string(response)

        # 주차칸 데이터 저장
        try:
            cursor = conn.cursor()
            cursor.execute(message)
            conn.commit()
            print("주차칸 트랜잭션 정상 완료")
        except gui.sql.pymysql.MySQLError as e:
            print(f"주차칸 오류 발생: {e}")
            conn.rollback()
        finally:
            gui.update_parking()

        if not gui.root.winfo_exists():
            exit_program()
            break

# ZeroMQ 서버를 스레드에서 실행
threading.Thread(target=parking_in_listen, daemon=True).start()
threading.Thread(target=parking_out_listen, daemon=True).start()
threading.Thread(target=status_rc_listen, daemon=True).start()
threading.Thread(target=parking_RC_listen, daemon=True).start()
threading.Thread(target=parking_status_listen, daemon=True).start()
print("ZMQ 스레딩 시작")

# Tkinter 메인 루프 실행
gui.root.mainloop()

    
# # 가상환경 생성
# python3 -m venv server_envs

# # 가상환경 활성화
# source server_env/bin/activate  # (Windows에서는 server_env\Scripts\activate)

# # 필요한 패키지 설치 (예: Flask)
# pip install flask

# # 서버 실행
# python app.py

# wget https://dev.mysql.com/get/mysql-apt-config_0.8.15-1_all.deb
# sudo dpkg -i mysql-apt-config_0.8.15-1_all.deb
# sudo apt-get update
# sudo apt-get install mysql-server