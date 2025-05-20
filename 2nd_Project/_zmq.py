import zmq
import gui
import sys
import threading

# 프로그램 종료 함수
def exit_program():
    print("프로그램 종료 중...")
    socket.close()   # ZeroMQ 소켓 닫기
    context.term()   # ZeroMQ 컨텍스트 종료
    conn.close()     # 데이터베이스 연결 닫기
    gui.root.quit()  # Tkinter 창 닫기
    sys.exit()       # 전체 프로그램 종료  
    
# ZeroMQ 컨텍스트 생성
print("프로그램 시작...")

context = zmq.Context()
print("ZeroMQ 컨텍스트 생성 완료...")

socket = context.socket(zmq.REP)
print("ZeroMQ 소켓 생성 완료...")

socket.bind("tcp://*:5511")  
print("소켓 바인딩 완료...")

conn = gui.sql.sql_connect()
print("SQL연결 완료...")

def zmq_server():
    while True:
        message = socket.recv_string()  # 클라이언트로부터 메시지 수신
        print(f"받은 메시지: {message}")

        response = f"서버 응답: {message.upper()}"
        socket.send_string(response)  # 응답 전송
        
        # 데이터 삽입 후 commit() 실행
        try:
            cursor = conn.cursor()
            cursor.execute(message)
            conn.commit()  # 변경 사항 저장
            print("트랜잭션 정상 완료")
        except gui.sql.pymysql.MySQLError as e:
        # 오류 발생 시 롤백
            print(f"오류 발생: {e}")
            conn.rollback()
            print("트랜잭션 롤백 완료")
        finally:
            gui.update_parking()
        
        if not gui.root.winfo_exists():  # Tkinter 창이 닫히면 루프 종료
            exit_program()
            print("프로그램 정상 종료 실패")
            break


# ZeroMQ 서버를 스레드에서 실행
zmq_thread = threading.Thread(target=zmq_server, daemon=True)
zmq_thread.start()
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