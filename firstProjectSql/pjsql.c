#include "pjsql.h"
#include <time.h>


bool initMySQL(MySQLConnection *mysql)
{
    // 기본 연결 정보 설정
    mysql->host = "localhost";
    mysql->user = "myuser";
    mysql->pass = "0000";
    mysql->db = "smartfarm_db";
    mysql->port = 3306;

    // MySQL 초기화
    mysql->conn = mysql_init(NULL);
    if (mysql->conn == NULL)
    {
        fprintf(stderr, "MySQL 초기화 실패\n");
        return false;
    }

    // MySQL 서버 연결
    if (!mysql_real_connect(mysql->conn, mysql->host, mysql->user, mysql->pass,
                            mysql->db, mysql->port, NULL, 0))
    {
        fprintf(stderr, "MySQL 연결 실패: %s\n", mysql_error(mysql->conn));
        return false;
    }

    printf("MySQL 데이터베이스에 연결되었습니다.\n");
    return true;
}

void closeMySQL(MySQLConnection *mysql)
{
    if (mysql->conn != NULL)
    {
        mysql_close(mysql->conn);
        mysql->conn = NULL;
        printf("MySQL 연결이 종료되었습니다.\n");
    }
}

bool saveData(MySQLConnection *mysql, int temp, int humi, int sun)
{
    char query[255];

    // 현재 날짜 가져오기
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", tm);

    // 쿼리 준비
    sprintf(query, "INSERT INTO data_records (m_date, temp, humi, sun) VALUES ('%s', %d, %d, %d)",
             date, temp, humi, sun);

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "Data 저장 실패: %s\n", mysql_error(mysql->conn));
        return false;
    }

    printf("Data가 성공적으로 저장되었습니다!\n");
    return true;
}

bool updateHourStats(MySQLConnection *mysql)
{
    char query[512];

    // 월별 통계 업데이트 쿼리
    sprintf(query, "INSERT INTO data_hour_stats (year, month, day, hour, temp, humi, sun) "
                   "SELECT YEAR(m_date), MONTH(m_date), DAY(m_date), HOUR(m_date), AVG(temp), AVG(humi), AVG(sun) "
                   "FROM data_records "
                   "GROUP BY YEAR(m_date), MONTH(m_date), HOUR(m_date), DAY(m_date) "
                   );

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "시간별 통계 업데이트 실패: %s\n", mysql_error(mysql->conn));
        return false;
    }

    printf("시간별 통계가 업데이트되었습니다.\n");
    return true;
}

void printDayStatsHistory(MySQLConnection *mysql, const char *day)  // 인수 무엇으로?
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];

    // 사용자의 게임 기록 조회 쿼리
    sprintf(query, "SELECT day, hour, temp, humi, sun FROM data_records WHERE day = '%s' ORDER BY m_date DESC",
            day);

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "기록 조회 실패: %s\n", mysql_error(mysql->conn));
        return;
    }

    // 결과 가져오기
    res = mysql_store_result(mysql->conn);
    if (res == NULL)
    {
        fprintf(stderr, "결과 가져오기 실패: %s\n", mysql_error(mysql->conn));
        return;
    }

    // 결과 출력
    printf("\n\t=== %s Data ===\n", day);
    printf("Day\t\tHour\t\ttemp\t\thumi\t\tsun\n");
    printf("----------------------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
    }

    mysql_free_result(res);
}

void waitEnter(void)
{
    printf("엔터를 쳐 주세요....\n");
    while (getchar() != '\n')
        ;
}