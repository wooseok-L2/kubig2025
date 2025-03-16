#include <stdio.h>

int fram[11] = {0);
int score = 0;
int x1, x2;
int res[11] = {0};
int bonus = 0;
int stcount = 0;
int spcount = 0;

int main(void){
  int i = 0;                      // 게임 시작
  while ( i < 11){
    printf("넘어간 핀 갯수 입력: );
    scanf("%d", &x1);             // 첫번째 공 넘어간 핀 갯수 입력
    
    if (x1 == 10){                // 스트라이크
      printf("Strike!! \n");
      stcount++;                  // 스트라이크 카운트 계산
      res[i] = x1;}               // 프레임에 넘어간 핀 갯수 입력
    esls{
      scanf("%d", &x2);}          // 두번째 공 넘어간 핀 갯수 입력

    if((x1 + x2) == 10){          // 스페어
      printf("Spare! \n");
      spcount++;
      res[i] = x1 + x2;           // 첫번째 두번째에 넘어간 핀 갯 수 입력
    else{
      res[i] = x1 + x2;
      

    i++;                          // 다음 프레임
    if (stcount % 3 == 0){
      bonus = 0;}
    esle if (stcount % 3 == 1){
      bonus += res[i];
    else if (stcount % 3 == 2){
      bonus += res[i];

    res[i-1] += bonus; 



