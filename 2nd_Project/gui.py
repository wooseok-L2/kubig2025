import tkinter as tk
from tkinter import ttk
import sql


# Tkinter 창 생성
root = tk.Tk()
root.title("Parking System")
root.geometry("800x600")

# 메인 프레임 생성
main_frame = tk.Frame(root)
main_frame.pack(fill="both", expand=True)

### 주차칸 표시 (위쪽 영역) ###
canvas = tk.Canvas(main_frame, width=750, height=200, bg="white")
canvas.pack(side="top", pady=20)

# 주차 칸 그리기 (3개)
parking_slots = []
parking_texts = [] 
for i in range(3):
    x = 130 + (i * 200)  # 간격 조정
    slot = canvas.create_rectangle(x, 40, x + 100, 160, outline="black", width=3)
    parking_slots.append(slot)
    text = canvas.create_text(x + 50, 100, text="비어 있음", font=("Arial", 14, "bold"), fill="black")
    parking_texts.append(text)


def update_parking():
    try:
        conn = sql.sql_connect()
        cursor = conn.cursor()
        cursor.execute("SELECT slot_number, status FROM parking_slots")
        data = cursor.fetchall()
        #conn.close()

        # 슬롯 번호와 Tkinter 인덱스를 매핑
        slot_map = {f"A{i+1}": i for i in range(len(parking_slots))}

        # 상태 변경 (주차칸 색상 + 텍스트)
        for slot_number, status in data:
            if slot_number in slot_map:  
                slot_index = slot_map[slot_number]  
                if status == "사용 중":
                    canvas.itemconfig(parking_slots[slot_index], fill="red")  # 차량 감지 시 빨간색
                    canvas.itemconfig(parking_texts[slot_index], text="사용 중", fill="black")  # 텍스트도 빨간색으로 변경
                else:
                    canvas.itemconfig(parking_slots[slot_index], fill="white")  # 차량 없을 때 흰색
                    canvas.itemconfig(parking_texts[slot_index], text="비어 있음", fill="black")  # 텍스트를 검은색으로 변경
    
    except Exception as e:
        print(f"오류 발생: {e}")  # 오류 발생 시 출력
        
    finally:
        cursor.close()
        conn.close()

    root.after(1000, update_parking)

### SQL 데이터 표시 (아래쪽 영역) ###
tree = ttk.Treeview(main_frame, columns=("RFID_num", "entry_time", "exit_time", "total_usage_time", "current_status"), show="headings")

# 테이블 헤더 설정
tree.heading("RFID_num", text="RFID 번호")
tree.heading("entry_time", text="입차 시간")
tree.heading("exit_time", text="출차 시간")
tree.heading("total_usage_time", text="총 이용 시간")
tree.heading("current_status", text="현재 상태")

# 각 열의 너비 조정
tree.column("RFID_num", width=100)
tree.column("entry_time", width=200)
tree.column("exit_time", width=200)
tree.column("total_usage_time", width=100)
tree.column("current_status", width=100)

tree.pack(fill="both", expand=True, side="bottom")

### SQL 데이터 로드 함수 ###
def load_data():  
    try: 
        conn = sql.sql_connect()
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM parking_log")
        data = cursor.fetchall()
        conn.close()

        # 기존 데이터 삭제 후 새 데이터 삽입
        tree.delete(*tree.get_children())
        for row in data:
            tree.insert("", "end", values=row)
    
    except Exception as e:
        print(f"오류 발생: {e}")  # 오류 발생 시 출력
        
    finally:
        cursor.close()
        conn.close()

### 버튼 추가 (하단 영역) ###
button_frame = tk.Frame(root)
button_frame.pack(side="bottom", pady=10)

load_button = tk.Button(button_frame, text="데이터 새로고침", command=load_data)
load_button.pack(side="left", padx=10)

exit_button = tk.Button(button_frame, text="종료", command=root.quit)
exit_button.pack(side="right", padx=10)

### UI 업데이트 시작 ###        
update_parking()    
root.mainloop()