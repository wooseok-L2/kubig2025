#include <stdio.h>

int main(void)
{
    FILE *fp;
    fp = fopen("output.txt", "a");
    if (fp == NULL)
    {
        printf("파일 열기 실패");
        return 1;
    }
    putc('A', fp);
    putc('A', stdout);
    fputc('B', fp);
    fputc('B', stdout);
    // gets deprecate 지원 종료
    fputs("puts로 문자가 간다.", fp);
    fputs("puts로 문자`가 간다.", stdout);

    fprintf(fp, "printf로 문자가 간다.");
    fprintf(stdout, "printf로 문자가 간다.\n");
    // EOF == -1;
    fclose(fp);
    return 0;
}