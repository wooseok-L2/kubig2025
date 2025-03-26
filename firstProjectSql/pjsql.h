#ifndef PJSQL_H
#define PJSQL_H

#include <mysql/mysql.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// MySQL 연결 정보
typedef struct
{
    MYSQL *conn;
    char *host;
    char *user;
    char *pass;
    char *db;
    int port;
} MySQLConnection;


// MySQL 연결 초기화 및 연결 함수
bool initMySQL(MySQLConnection *mysql);

// MySQL 연결 종료 함수
void closeMySQL(MySQLConnection *mysql);

// 점수 저장 함수
bool saveData(MySQLConnection *mysql, (char *)buffer);

// 시간별 통계 업데이트 함수
bool updateHourStats(MySQLConnection *mysql);

// 날짜별 기록 출력 함수
void printDayStatsHistory(MySQLConnection *mysql, const char *day);

// 사용자 입력 대기 함수 추가
void waitEnter(void);

#endif // BOWLINGSQL_H