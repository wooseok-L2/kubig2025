#include <stdio.h>

int frame[11] = {0);
int res[10] = {0};
int x1, x2;
int score[2][10] = {0};
int bonus = 0;
int stcount = 0;
int spcount = 0;

int main(void){
  int i;                      // 게임 시작
  int j;
  for (i = 1; i < 11; i++){ 
    for (j = 1; j < 3; j++){
      printf("frame[i] \n");
      printf("넘어간 핀 갯수 입력: );
      scanf("%d", &score[i][j]);             // 넘어간 핀 갯수 입력
      
      if (score[i][j] == 10){                  // 스트라이크
        printf("Strike!! \n");
        stcount++;
        res[i] = score[i][j];
        break;
      }                                      // 프레임에 넘어간 핀 갯수 입력
    }

    res[i] = score[i][j-1] + score[i][j];

    if (res[i] == 10){
      printf("Spare! \n");
      spcount++;
      res[i] += res[i-1];
      continue;
    }
    else { 
      printf("great! \n");
      res[i] += res[i-1];
    }

    if (stcount % 3 != 0){
      bonus = res[i];
      res[i-1] += bonus;
      res[i] += res[i-1];
    }
    else { bonus = 0; }

    if (spcount == 1){
      bonus = score[i][j-1];
      res[i-1] += bonus;
      res[i] += res[i-1];
    }
    
}






