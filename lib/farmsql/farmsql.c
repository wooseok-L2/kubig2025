#include "farmsql.h"
#include "serial.h"
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

bool saveData(MySQLConnection *mysql, SensorData *rx)
{
    char query[512];

    // 현재 날짜 가져오기
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time[30];
    strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", tm);

    // 쿼리 준비
    snprintf(query, sizeof(query), "INSERT INTO data_records (Time, Temperature, Humidity, Sunshine) VALUES ('%s', %d, %d, %d)",
             time, rx->temperature, rx->humidity, rx->sun);

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

    // 통계 업데이트 쿼리
    sprintf(query, "INSERT INTO hour_stats (Month, Day, Hour, Temperature, Humidity, SoilMoisture, Sunshine) "
                   "SELECT MONTH(Time), DAY(Time), HOUR(Time), AVG(Temp), AVG(Humi), AVG(SoilMoisture), AVG(Sunshine) "
                   "FROM data_records "
                   "GROUP BY MONTH(Time), DAY(Time), HOUR(Time) "
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

    // 기록 조회 쿼리
    sprintf(query, "SELECT Day, Hour, Temperature, Humidity, SoilMoisture, Sunshine FROM data_records WHERE day = '%s' ORDER BY m_date DESC",
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
    printf("Day\t\tHour\t\tTemp\t\tHumi\t\tSoil\t\tSun\n");
    printf("------------------------------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    }

    mysql_free_result(res);
}

void waitEnter(void)
{
    printf("엔터를 쳐 주세요....\n");
    while (getchar() != '\n')
        ;
}