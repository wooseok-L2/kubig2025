#ifndef BOWLING_H
#define BOWLING_H

// 점수 정보 구조체
typedef struct
{
    int score[12][3];
    int frameScore[11];
    char name[10];
} Score;

// 게임 로직 및 점수 계산 관련 함수
void initScore(Score *player, const char iname[]);
void calScore(int *frameScore, const int (*score)[3]);
int getValidScore(int frame, int bow, int prevScore);
void playGame(Score *player, int i);
void playGame10Frame(Score *player);

#endif // BOWLING_H