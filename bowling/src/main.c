#include "../include/board.h"
#include "../include/bowling.h"
#include "../include/bowlingsql.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // string.h 추가

// 운영체제 확인을 위한 매크로 추가
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// 메뉴 상수 정의를 enum으로 변경
typedef enum
{
    PLAY_GAME = 1,
    VIEW_HISTORY,
    TOP_SCORES,
    MONTHLY_STATS, // 새 메뉴 옵션 추가
    EXIT = 0
} MenuOption;

// 메뉴 출력 함수
void printMenu()
{
    system(CLEAR_SCREEN);
    printf("=== 볼링 게임 시스템 ===\n");
    printf("1. 게임 플레이\n");
    printf("2. 내 기록 보기\n");
    printf("3. 최고 점수 보기\n");
    printf("4. 월별 통계 보기\n"); // 새 메뉴 옵션 추가
    printf("0. 종료\n");
    printf("선택: ");
}

// 게임 실행 함수
void runGame(MySQLConnection *mysql)
{
    Score player;
    char name[10];

    // 시작 시 화면 지우기
    system(CLEAR_SCREEN);

    printf("볼링 게임을 시작합니다!\n");
    printf("플레이어 이름을 입력하세요 (최대 9글자): ");
    scanf("%9s%*c", name);

    // 점수 초기화
    initScore(&player, name);

    // 보드 출력
    printBoard(&player);

    // 1-9 프레임 진행
    for (int i = 1; i <= 9; i++)
    {
        playGame(&player, i);
    }

    // 10 프레임 진행 (특별 규칙 적용)
    playGame10Frame(&player);

    // 종료 시 화면 지우고 최종 결과 표시
    system(CLEAR_SCREEN);
    printBoard(&player);
    printf("\n게임이 종료되었습니다!\n");
    printf("최종 점수: %d\n", player.frameScore[10]);

    // MySQL에 점수 저장
    if (mysql->conn != NULL)
    {
        saveScore(mysql, player.name, player.frameScore[10]);
        updateMonthlyStats(mysql);
    }
    waitEnter();
}

int main()
{
    int choice;
    char username[50];
    MySQLConnection mysql = {0};
    bool dbConnected = false;

    // MySQL 연결 시도
    dbConnected = initMySQL(&mysql);
    if (!dbConnected)
    {
        printf("경고: 데이터베이스 연결 실패. 점수가 저장되지 않습니다.\n");
        waitEnter();
    }

    while (true)
    {
        printMenu();
        scanf("%d%*c", &choice);

        switch (choice)
        {
        case PLAY_GAME:
            runGame(&mysql);
            break;

        case VIEW_HISTORY:
            system(CLEAR_SCREEN);
            if (!dbConnected)
            {
                printf("데이터베이스 연결이 필요합니다.\n");
            }
            else
            {
                printf("사용자 이름을 입력하세요: ");
                scanf("%49s%*c", username);
                printUserHistory(&mysql, username);
            }
            waitEnter();
            break;

        case TOP_SCORES:
            system(CLEAR_SCREEN);
            if (!dbConnected)
            {
                printf("데이터베이스 연결이 필요합니다.\n");
            }
            else
            {
                printTopScores(&mysql, 10); // 상위 10개 점수 표시
            }
            waitEnter();
            break;

        case MONTHLY_STATS: // 새 메뉴 옵션 처리 수정
            system(CLEAR_SCREEN);
            if (!dbConnected)
            {
                printf("데이터베이스 연결이 필요합니다.\n");
            }
            else
            {
                printf("사용자 이름을 입력하세요 (모든 사용자 통계를 보려면 그냥 Enter): ");
                // 사용자 입력 받기
                if (fgets(username, sizeof(username), stdin))
                {
                    // 개행 문자 제거
                    username[strcspn(username, "\n")] = 0;

                    // 월별 통계 업데이트 및 출력
                    updateMonthlyStats(&mysql);

                    // 빈 문자열이면 NULL 전달
                    if (username[0] == '\0')
                        printMonthlyStats(&mysql, NULL);
                    else
                        printMonthlyStats(&mysql, username);
                }
            }
            waitEnter();
            break;

        case EXIT:
            if (dbConnected)
            {
                closeMySQL(&mysql);
            }
            printf("프로그램을 종료합니다. 감사합니다!\n");
            return 0;

        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }

    return 0;
}