#pragma once

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#define FRAMES 10

typedef struct{
    char username[40];
    char playdate[40];
    char playmonth[40];
    int score;
    int numgames;
}Bowling;


enum menu{
    START,
    SCORE,
    HISTORY
};


void printf_menu(void);
int gamestart(void);
void playerRegister(void);
void add_score(MYSQL *conn);
void checkscore(MYSQL *conn);
void checkHistory(MYSQL *conn);
void waitEnter(void);


