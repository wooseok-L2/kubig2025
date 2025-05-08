// gcc -fPIC -shared -o libplugin.so plugin.c
// file , objdump, strings, readelf
#include <stdio.h>

void hello()
{
    printf("안녕하세요! 저는 플러그인 입니다.\n");
}