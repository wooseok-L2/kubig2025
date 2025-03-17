#ifndef BOWLINGSQL_H
#define BOWLINGSQL_H

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
bool saveScore(MySQLConnection *mysql, const char *username, int score);

// 월별 통계 업데이트 함수
bool updateMonthlyStats(MySQLConnection *mysql);

// 사용자의 모든 게임 기록 출력 함수
void printUserHistory(MySQLConnection *mysql, const char *username);

// 최고 점수 플레이어 출력 함수
void printTopScores(MySQLConnection *mysql, int limit);

// 사용자 월별 통계 출력 함수 수정 - NULL 전달 시 전체 사용자 표시
void printMonthlyStats(MySQLConnection *mysql, const char *username);

// 사용자 입력 대기 함수 추가
void waitEnter(void);

#endif // BOWLINGSQL_H