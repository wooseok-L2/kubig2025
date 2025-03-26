#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <libserialport.h>

// 데이터 송수신 및 DB 작업에 필요한 구조체 정의
typedef struct {
    struct sp_port *port;
    MYSQL *conn;
} ThreadData;

// 시리얼 데이터 송신 함수
void *send_serial_data(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    // 송신할 데이터 예시
    char message[] = "Hello from Server!";
    sp_blocking_write(data->port, message, sizeof(message), 1000);
    printf("Sent serial data: %s\n", message);

    return NULL;
}

// 시리얼 데이터 수신 함수
void *receive_serial_data(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    char buffer[256];
    sp_blocking_read(data->port, buffer, sizeof(buffer), 1000);
    printf("Received serial data: %s\n", buffer);

    // 수신 데이터를 MySQL DB에 삽입
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO serial_data (data) VALUES ('%s')", buffer);
    if (mysql_query(data->conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(data->conn));
    } else {
        printf("Data inserted into MySQL database.\n");
    }

    return NULL;
}

// MySQL 연결 설정 함수
MYSQL *setup_mysql_connection() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "password", "test_db", 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    printf("MySQL connected successfully.\n");
    return conn;
}

// 시리얼 포트 설정 함수
struct sp_port *setup_serial_port(const char *port_name) {
    struct sp_port *port;
    sp_get_port_by_name(port_name, &port);
    sp_open(port, SP_MODE_READ_WRITE);
    sp_set_baudrate(port, 9600);  // Baud rate 설정
    printf("Serial port %s opened successfully.\n", port_name);
    return port;
}

// 메인 함수
int main() {
    pthread_t send_thread, receive_thread;
    ThreadData data;

    // MySQL 연결 설정
    data.conn = setup_mysql_connection();

    // 시리얼 포트 설정
    data.port = setup_serial_port("COM1");

    // 스레드 생성
    pthread_create(&send_thread, NULL, send_serial_data, &data);
    pthread_create(&receive_thread, NULL, receive_serial_data, &data);

    // 스레드 종료 대기
    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    // 리소스 정리
    sp_close(data.port);
    mysql_close(data.conn);

    return 0;
}