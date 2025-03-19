#include "bbowling.h"
#define FRAMES 10

Bowling newgame;


void printf_menu(void){
    system("clear");
    printf("=====Welcome to bowling game===== \n");
    printf("0. Game Start \n");
    printf("1. Check Score \n");
    printf("2. Check History \n");
}

void gamestart(void) {
    int rolls[21] = {0}; // 최대 21번의 투구 가능 (10 프레임 + 스트라이크 보너스)
    int totalScore = 0;
    int rollIndex = 0;

    // 입력 받기
    printf("볼링 점수 계산기\n");
    
    playerRegister();

    for (int i = 0; i < FRAMES; i++) {
        printf("프레임 %d 첫 번째 투구: ", i + 1);
        scanf("%d", &rolls[rollIndex]);

        if (rolls[rollIndex] == 10) { // 스트라이크
            printf("스트라이크!\n");
            rollIndex++;
            if (i == 9){
                printf("one more time! \n");
                scanf("%d", &rolls[rollIndex]);
                if (rolls[rollIndex] == 10){
                    printf("스트라이크!\n");
                    printf("last time! \n");
                    rollIndex++;
                    scanf("%d", &rolls[rollIndex]);
                }else{
                    printf("last time! \n");
                    scanf("%d", &rolls[rollIndex + 1]);
                }
            }
            continue; // 다음 프레임으로 이동
        }

        printf("프레임 %d 두 번째 투구: ", i + 1);
        scanf("%d", &rolls[rollIndex + 1]);
        rollIndex += 2;
        if (i == 9){
            if (rolls[rollIndex-2] + rolls[rollIndex-1] == 10){
                printf("spare! \n");
                printf("last time! \n");
                scanf("%d", &rolls[rollIndex]);
            }
        }
    }
    // frame 10 bonus
  
    // 점수 계산
    rollIndex = 0;
    for (int i = 0; i < FRAMES; i++) {
        if (rolls[rollIndex] == 10) { // 스트라이크
            totalScore += 10 + rolls[rollIndex + 1] + rolls[rollIndex + 2];
            rollIndex++;
        } else if (rolls[rollIndex] + rolls[rollIndex + 1] == 10) { // 스페어
            totalScore += 10 + rolls[rollIndex + 2];
            rollIndex += 2;
        } else { // 일반 프레임
            totalScore += rolls[rollIndex] + rolls[rollIndex + 1];
            rollIndex += 2;
        }
    }

    // 최종 점수 출력
    printf("총 점수: %d\n", totalScore);

    newgame.score = totalScore;


    //add_score(conn);
    waitEnter();

}


void playerRegister(void){
    printf("Enter your name: ");
    scanf("%s%*c", newgame.username);
    printf("Enter date: ");
    scanf("%s%*c", newgame.playdate);
}

void add_score(MYSQL *conn){
    printf("---Add Score--- \n");

    char query[255];

    sprintf(query, "insert into SRecord(username, playdate, score) values ('%s', '%s', %d);", newgame.username, newgame.playdate, newgame.score);

    if (mysql_query(conn, query)){
        printf("Fail add data : %s \n", mysql_error(conn));
    }
    else{
        printf("Success Insert data! \n");
    }

    waitEnter();

}

void checkscore(MYSQL *conn){

    printf("---Score--- \n");
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    strcpy(query, "select * from SRecord;");

    if (mysql_query(conn, query)){
        printf("Fail query \n");
        return;
    }

    res = mysql_store_result(conn);

    if (!res){
        printf("Fail read \n");
        return;
    }

    Bowling *pbowling;
    pbowling = (Bowling *)malloc(sizeof(Bowling));
    if (pbowling == NULL){
        printf("Out of memory");
        return;
    }

    int i = 0;
    
    while (row = mysql_fetch_row(res)){
        strcpy((pbowling + i)->username, row[0]);
        strcpy((pbowling + i)->playdate, row[1]);
        (pbowling + i)->score, atoi(row[2]);
        i++;
        pbowling = realloc(pbowling, sizeof(Bowling) * (i + 1));
    }

    for (int j = 0; j < i; ++j)
    {
        printf("%s \t%s \t%d \n",
               (pbowling + j)->username, (pbowling + j)->playdate,
               (pbowling + j)->score);
    }

    free(pbowling);

}

void checkHistory(MYSQL *conn){
    printf("---History--- \n");

    printf("---Score--- \n");
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];


    strcpy(query, "INSERT INTO TRecord (username, playmonth, numgames)"
        "SELECT username, MONTH(playdate), COUNT(*) "
        "FROM SRecord;"
        "GROUP BY username, month(playdate)");
    
    //printf("Executing query: %s\n", query);
    if (mysql_query(conn, query)){
        printf("Fail query : %s \n", mysql_error(conn));
        return;
    }

    strcpy(query, "select username,  from TRecord;");

    if (mysql_query(conn, query)){
        printf("Fail query : %s \n", mysql_error(conn));
        return;
    }


    res = mysql_store_result(conn);

    if (res == NULL){
        printf("Fail read \n");
        return;
    }

    Bowling *pbowling;
    pbowling = (Bowling *)malloc(sizeof(Bowling));
    if (pbowling == NULL){
        printf("Out of memory");
        return;
    }

    int i = 0;
    
    while (row = mysql_fetch_row(res)){        
        strcpy((pbowling + i)->username, row[0]);
        strcpy((pbowling + i)->playmonth, row[1]);
        (pbowling + i)->numgames, atoi(row[2]);
        i++;
        pbowling = realloc(pbowling, sizeof(Bowling) * (i + 1));
    }

    for (int j = 0; j < i; ++j)
    {
        printf("%s \t%s \t%d \n",
               (pbowling + j)->username, (pbowling + j)->playmonth,
               (pbowling + j)->numgames);
    }


    free(pbowling);

}

void waitEnter(void)
{
    printf("엔터를 쳐 주세요....\n");
    char temp;
    while (temp != '\n')
        scanf("%c%*c", &temp);
}