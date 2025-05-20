import pymysql

def sql_connect():
    try:
        # (1) MYSQL 연결 
        conn = pymysql.connect(
            host='localhost',
            user='root',
            password='0000',
            database='parking_db',
            charset='utf8mb4'

        )

        # print('MariaDB 연결 성공')

    except pymysql.MySQLError as e:
        print('Database Error: ', e)

    # finally:
    #     # (5) 데이터베이스 커서와 커넥션을 모두 닫음 
    #     cursor.close()
    #     connection.close()
    #     print('MySQL Connection Close')
    
    return conn

# sql_connect()

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