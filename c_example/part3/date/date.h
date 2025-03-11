#pragma once
#include <stdio.h>

typedef struct
{
    /* data */
    int year;
    int month;
    int day;
    int temp[5];
}Date;

void printDate(Date *);
