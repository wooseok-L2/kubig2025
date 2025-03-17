#include "../include/bowling.h"
#include "../include/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 운영체제 확인을 위한 매크로 추가
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

static char board[7][50] = {
    "-------------------------------------------",
    "| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |",
    "-------------------------------------------",
    "| | | | | | | | | | | | | | | | | | | | | |",
    "-------------------------------------------",
    "|   |   |   |   |   |   |   |   |   |     |",
    "-------------------------------------------",
};

void initScore(Score *player, const char iname[])
{
    strcpy(player->name, iname);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            player->score[i][j] = 0;
        }
    }
}

void calScore(int *frameScore, const int (*score)[3])
{
    for (int i = 0; i < 11; ++i)
    {
        frameScore[i] = 0;
    }
    for (int i = 1; i < 11; ++i)
    {
        frameScore[i] += frameScore[i - 1] + score[i][1] + score[i][2];
        // 스트라이크 보너스
        if (score[i][1] == 10)
        {
            frameScore[i] += score[i + 1][1] + score[i + 1][2];
            if (score[i + 1][1] == 10)
                frameScore[i] += score[i + 2][1];
        }
        // 스페어 보너스
        else if (score[i][1] + score[i][2] == 10)
        {
            frameScore[i] += score[i + 1][1];
        }
    }
}

// 사용자 입력을 검증하는 함수 추가
int getValidScore(int frame, int bow, int prevScore)
{
    int maxScore = 10;
    int score;

    // 프레임의 두 번째 투구인 경우 최대값 조정
    if (bow == 2 && frame < 10)
    {
        maxScore = 10 - prevScore;
    }

    while (1)
    {
        scanf("%d%*c", &score);

        if (score >= 0 && score <= maxScore)
        {
            return score;
        }

        printf("유효한 점수를 입력하세요 (0-%d): ", maxScore);
    }
}

void playGame(Score *player, int i)
{
    // 화면 정리 후 첫 번째 투구 안내
    system(CLEAR_SCREEN);
    printBoard(player);
    printf("Player : %s\n", player->name);
    printf("%d frame 1 cast : ", i);
    player->score[i][1] = getValidScore(i, 1, 0);
    setScore(i, 1, player);
    // 점수 계산
    calScore(player->frameScore, player->score);

    // 화면 정리 후 업데이트된 보드 표시
    system(CLEAR_SCREEN);
    printBoard(player);

    // (i-1) frame spare? --> (i-1) frame score
    if (i > 1 && ((player->score[i - 1][1]) + (player->score[i - 1][2])) == 10 && ((player->score[i - 1][1] != 10)))
    {
        setFrameScore(i - 1, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // (i-2) frame strike && (i-1) frame strike --> (i-2) frame score
    if (i > 2 && (player->score[i - 2][1] == 10) && (player->score[i - 1][1] == 10))
    {
        setFrameScore(i - 2, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // 스트라이크일 경우 두 번째 투구 생략
    if (player->score[i][1] == 10)
        return;

    // 화면 정리 후 두 번째 투구 안내
    system(CLEAR_SCREEN);
    printBoard(player);
    printf("Player : %s\n", player->name);
    printf("%d frame 2 cast : ", i);
    player->score[i][2] = getValidScore(i, 2, player->score[i][1]);
    setScore(i, 2, player);
    // 점수 계산
    calScore(player->frameScore, player->score);

    // 화면 정리 후 업데이트된 보드 표시
    system(CLEAR_SCREEN);
    printBoard(player);

    // (i-1) frame strike --> (i-1) frame score
    if (i > 1 && player->score[i - 1][1] == 10)
    {
        setFrameScore(i - 1, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // i frame first + second < 10 --> i frame score
    if ((player->score[i][1] + player->score[i][2]) < 10)
    {
        setFrameScore(i, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }
}

void playGame10Frame(Score *player)
{
    // 화면 정리 후 첫 번째 투구 안내
    system(CLEAR_SCREEN);
    printBoard(player);
    printf("Player : %s\n", player->name);
    printf("10 frame 1 cast : ");
    player->score[10][1] = getValidScore(10, 1, 0);
    setScore(10, 1, player);
    // 점수 계산
    calScore(player->frameScore, player->score);

    // 화면 정리 후 업데이트된 보드 표시
    system(CLEAR_SCREEN);
    printBoard(player);

    // (i-2) frame strike && (i-1) frame strike --> (i-2) frame score
    if (player->score[8][1] == 10 && player->score[9][1] == 10)
    {
        setFrameScore(8, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // (i-1) frame spare? --> (i-1) frame score
    if ((player->score[9][1] + player->score[9][2] == 10) && (player->score[9][1] != 10))
    {
        setFrameScore(9, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // 화면 정리 후 두 번째 투구 안내
    system(CLEAR_SCREEN);
    printBoard(player);
    printf("Player : %s\n", player->name);
    printf("10 frame 2 cast : ");
    // 10프레임 특별 규칙: 첫 투구가 스트라이크면 두 번째 투구도 0-10점 가능
    int maxScore = (player->score[10][1] == 10) ? 10 : (10 - player->score[10][1]);
    player->score[10][2] = getValidScore(10, 2, player->score[10][1]);
    setScore(10, 2, player);
    // 점수 계산
    calScore(player->frameScore, player->score);

    // 화면 정리 후 업데이트된 보드 표시
    system(CLEAR_SCREEN);
    printBoard(player);

    // (i-1) frame strike --> (i-1) frame score
    if (player->score[9][1] == 10)
    {
        setFrameScore(9, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // i frame first + second < 10 --> i frame score
    if (player->score[10][1] + player->score[10][2] < 10)
    {
        setFrameScore(10, player);
        system(CLEAR_SCREEN);
        printBoard(player);
    }

    // third bowing
    if (player->score[10][1] == 10 || player->score[10][1] + player->score[10][2] == 10)
    {
        // 화면 정리 후 세 번째 투구 안내
        system(CLEAR_SCREEN);
        printBoard(player);
        printf("Player : %s\n", player->name);
        printf("10 frame 3 cast : ");
        player->score[10][3] = getValidScore(10, 3, 0); // 10프레임 3번째는 항상 0-10 가능
        setScore(10, 3, player);
        // 점수 계산
        player->frameScore[10] = player->frameScore[9] + player->score[10][1] + player->score[10][2] + player->score[10][3];
        setFrameScore(10, player);

        // 화면 정리 후 최종 보드 표시
        system(CLEAR_SCREEN);
        printBoard(player);
    }
}