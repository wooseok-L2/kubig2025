#ifndef BOARD_H
#define BOARD_H

// 점수 정보 구조체는 bowling.h로 이동
#include "bowling.h"

// 보드 출력 관련 함수
void printBoard(Score *player);
void setScore(int frame, int bow, Score *player);
void setFrameScore(int frame, Score *player);

#endif // BOARD_H