#include "../include/bowlingsql.h"
#include <time.h>

bool initMySQL(MySQLConnection *mysql)
{
    // 기본 연결 정보 설정
    mysql->host = "localhost";
    mysql->user = "myuser";
    mysql->pass = "0000";
    mysql->db = "bowling_db";
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

bool saveScore(MySQLConnection *mysql, const char *username, int score)
{
    char query[255];

    // 현재 날짜 가져오기
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", tm);

    // 쿼리 준비
    sprintf(query, "INSERT INTO score_records (username, play_date, score) VALUES ('%s', '%s', %d)",
            username, date, score);

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "점수 저장 실패: %s\n", mysql_error(mysql->conn));
        return false;
    }

    printf("점수가 성공적으로 저장되었습니다!\n");
    return true;
}

bool updateMonthlyStats(MySQLConnection *mysql)
{
    char query[512];

    // 월별 통계 업데이트 쿼리
    sprintf(query, "INSERT INTO user_monthly_stats (username, year, month, play_count) "
                   "SELECT username, YEAR(play_date), MONTH(play_date), COUNT(*) "
                   "FROM score_records "
                   "GROUP BY username, YEAR(play_date), MONTH(play_date) "
                   "ON DUPLICATE KEY UPDATE play_count = VALUES(play_count)");

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "월별 통계 업데이트 실패: %s\n", mysql_error(mysql->conn));
        return false;
    }

    printf("월별 통계가 업데이트되었습니다.\n");
    return true;
}

void printUserHistory(MySQLConnection *mysql, const char *username)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];

    // 사용자의 게임 기록 조회 쿼리
    sprintf(query, "SELECT play_date, score FROM score_records WHERE username = '%s' ORDER BY play_date DESC",
            username);

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
    printf("\n=== %s님의 게임 기록 ===\n", username);
    printf("날짜\t\t점수\n");
    printf("-------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("%s\t%s\n", row[0], row[1]);
    }

    mysql_free_result(res);
}

void printTopScores(MySQLConnection *mysql, int limit)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];

    // 최고 점수 조회 쿼리
    sprintf(query, "SELECT username, score, play_date FROM score_records ORDER BY score DESC LIMIT %d", limit);

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "최고 점수 조회 실패: %s\n", mysql_error(mysql->conn));
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
    printf("\n=== 최고 점수 TOP %d ===\n", limit);
    printf("순위\t사용자\t\t점수\t날짜\n");
    printf("----------------------------------\n");

    int rank = 1;
    while ((row = mysql_fetch_row(res)))
    {
        printf("%d\t%s\t\t%s\t%s\n", rank++, row[0], row[1], row[2]);
    }

    mysql_free_result(res);
}

// 사용자 월별 통계 출력 함수 구현
void printMonthlyStats(MySQLConnection *mysql, const char *username)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[512];

    // username이 NULL이면 모든 사용자에 대한 통계 조회
    if (username == NULL || username[0] == '\0')
    {
        // 모든 사용자의 월별 통계 조회
        sprintf(query, "SELECT username, year, month, play_count FROM user_monthly_stats "
                       "ORDER BY year DESC, month DESC, username");
    }
    else
    {
        // 특정 사용자의 월별 통계 조회
        sprintf(query, "SELECT year, month, play_count FROM user_monthly_stats "
                       "WHERE username = '%s' ORDER BY year DESC, month DESC",
                username);
    }

    // 쿼리 실행
    if (mysql_query(mysql->conn, query))
    {
        fprintf(stderr, "월별 통계 조회 실패: %s\n", mysql_error(mysql->conn));
        return;
    }

    // 결과 가져오기
    res = mysql_store_result(mysql->conn);
    if (res == NULL)
    {
        fprintf(stderr, "결과 가져오기 실패: %s\n", mysql_error(mysql->conn));
        return;
    }

    // 결과가 없는 경우
    if (mysql_num_rows(res) == 0)
    {
        if (username == NULL || username[0] == '\0')
            printf("\n=== 전체 사용자 월별 통계 ===\n");
        else
            printf("\n=== %s님의 월별 통계 ===\n", username);

        printf("기록이 없습니다.\n");
        mysql_free_result(res);
        return;
    }

    // 테이블 헤더 출력
    if (username == NULL || username[0] == '\0')
    {
        printf("\n=== 전체 사용자 월별 통계 ===\n");
        printf("사용자명\t년도\t월\t플레이 횟수\n");
        printf("-----------------------------------\n");

        // 결과 출력 - 모든 사용자
        while ((row = mysql_fetch_row(res)))
        {
            printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
        }
    }
    else
    {
        printf("\n=== %s님의 월별 통계 ===\n", username);
        printf("년도\t월\t플레이 횟수\n");
        printf("----------------------------\n");

        // 결과 출력 - 특정 사용자
        while ((row = mysql_fetch_row(res)))
        {
            printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
        }

        // 추가적인 통계 정보 출력 (총 플레이 횟수, 평균 등)
        mysql_free_result(res);

        // 총 플레이 횟수와 평균 점수 조회
        sprintf(query, "SELECT COUNT(*) as total_games, AVG(score) as avg_score "
                       "FROM score_records WHERE username = '%s'",
                username);

        if (mysql_query(mysql->conn, query))
        {
            fprintf(stderr, "통계 집계 조회 실패: %s\n", mysql_error(mysql->conn));
            return;
        }

        res = mysql_store_result(mysql->conn);
        if (res && (row = mysql_fetch_row(res)))
        {
            printf("\n총 게임 수: %s\n", row[0]);
            printf("평균 점수: %.2f\n", row[1] ? atof(row[1]) : 0);
        }
    }

    mysql_free_result(res);

    // 전체 통계 요약 (특정 사용자가 아닌 경우)
    if (username == NULL || username[0] == '\0')
    {
        // 전체 게임 수와 평균 점수 조회
        sprintf(query, "SELECT COUNT(*) as total_games, AVG(score) as avg_score, "
                       "COUNT(DISTINCT username) as total_users FROM score_records");

        if (mysql_query(mysql->conn, query))
        {
            fprintf(stderr, "통계 집계 조회 실패: %s\n", mysql_error(mysql->conn));
            return;
        }

        res = mysql_store_result(mysql->conn);
        if (res && (row = mysql_fetch_row(res)))
        {
            printf("\n총 사용자 수: %s\n", row[2]);
            printf("총 게임 수: %s\n", row[0]);
            printf("전체 평균 점수: %.2f\n", row[1] ? atof(row[1]) : 0);
        }

        mysql_free_result(res);
    }
}

void waitEnter(void)
{
    printf("엔터를 쳐 주세요....\n");
    while (getchar() != '\n')
        ;
}