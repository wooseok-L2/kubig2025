#include "../include/board.h"
#include "../include/bowling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 운영체제 확인을 위한 매크로 추가
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// 보드 레이아웃 - board.c에서만 사용되므로 static으로 선언
static char board[7][50] = {
    "-------------------------------------------",
    "| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |",
    "-------------------------------------------",
    "| | | | | | | | | | | | | | | | | | | | | |",
    "-------------------------------------------",
    "|   |   |   |   |   |   |   |   |   |     |",
    "-------------------------------------------",
};

void printBoard(Score *player)
{
    // 화면 지우기 명령 활성화
    system(CLEAR_SCREEN);

    printf("\n\n\nPlayer name: %s\n", player->name);
    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", board[i]);
    }
}

void setScore(int frame, int bow, Score *player)
{
    for (int i = 1; i <= frame; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            board[3][1 + (i - 1) * 4 + (j - 1) * 2] = ' ';
        }
    }
    if (frame == 10 && bow == 1)
    {
        board[3][1 + (frame - 1) * 4] = ' ';
        board[3][1 + (frame - 1) * 4 + 2] = ' ';
        board[3][1 + (frame - 1) * 4 + 4] = ' ';
    }
    for (int i = 1; i <= frame; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            if (i == frame && bow == 1 && j == 2 && i <= 9)
                break;
            if (player->score[i][j] == 10 && j == 1)
            {
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = 'X';
            }
            else if (player->score[i][j] == 10 && i == 10 && j == 2)
            {
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = 'X';
            }
            else if (player->score[i][j] + player->score[i][j - 1] == 10 && j == 2 && player->score[i][j - 1] != 10)
            {
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = '/';
            }
            else if (player->score[i][j] + player->score[i][j - 1] < 10)
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = player->score[i][j] + '0';
        }
    }
    if (frame == 10 && bow == 3)
        if (player->score[10][3] == 10)
            board[3][1 + (10 - 1) * 4 + (3 - 1) * 2] = 'X';
        else
            board[3][1 + (10 - 1) * 4 + (3 - 1) * 2] = player->score[10][3] + '0';
}

void setFrameScore(int frame, Score *player)
{
    char buf[4];
    sprintf(buf, "%3d", player->frameScore[frame]);
    strncpy(board[5] + (frame - 1) * 4 + 1, buf, 3);
}