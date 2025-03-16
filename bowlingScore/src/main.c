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
      scanf("%d", &score[i][j]);             // 첫번째 공 넘어간 핀 갯수 입력
      
      if (res[i][j] == 10){                // 스트라이크
        printf("Strike!! \n");
        stcount++;
        strike(score, stcount);
      }               // 프레임에 넘어간 핀 갯수 입력
      esls{
        scanf("%d", &score[i][j]);}          // 두번째 공 넘어간 핀 갯수 입력
  
      if((x1 != 10) && ((x1 + x2) == 10)){          // 스페어
        printf("Spare! \n");
        res[i] = x1 + x2;           // 첫번째 두번째에 넘어간 핀 갯 수 입력
        spcount++;
      else{
        res[i] = x1 + x2;
  
      x1 = 0;                       // 핀 갯수 초기화
      x2 = 0;



int strike(int *res, stcount){
    int bonus = 0;
    if (stcount % 3 == 0){        // 스트라이크 0 or 3회
        bonus = 0;}
    esle if (stcount % 3 == 1){   // 스트라이크 1회 
        bonus += res[i]; 
    else if (stcount % 3 == 2){   // 스트라이크 2회
        bonus += res[i];
  
    res[i-1] += bonus;  
    res[i] = res[i-1];
}  

int spare(int *res, spcount){
    int bonus = 0;
    if(spcount == 1){
      bonus = x1;
  
    res[i-1] += bonus;  
    res[i] = res[i-1];
} 






