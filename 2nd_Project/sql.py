import mysql.connector

def sql_connect():
    try:
        # (1) MYSQL 연결 
        conn = mysql.connector.connect(
            host = 'localhost',
            database = 'parking_db',  
            user = 'myuser',
            password = '0000'   
        )

        if conn.is_connected():
            db_info = conn.get_server_info()


    except ImportError as e:
        print('Database Error: ',e) 

    # finally:
    #     # (5) 데이터베이스 커서와 커넥션을 모두 닫음 
    #     cursor.close()
    #     connection.close()
    #     print('MySQL Connection Close')
    
    return conn

# # 테이블 생성
# cursor.execute("""
# CREATE TABLE IF NOT EXISTS users (
#     id INT AUTO_INCREMENT PRIMARY KEY,
#     name VARCHAR(50),
#     age INT
# )
# """)

# # 데이터 삽입 후 commit() 실행
# cursor.execute("INSERT INTO users (name, age) VALUES (%s, %s)", ("Bob", 30))
# conn.commit()  # 변경 사항 저장

# # 데이터 조회
# cursor.execute("SELECT * FROM users")
# rows = cursor.fetchall()
# for row in rows:
#     print(row)

# # 연결 종료
# cursor.close()
# conn.close()