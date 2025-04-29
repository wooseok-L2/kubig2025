#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define BUFFER_SIZE 256

int main()
{
    int pipe1[2]; // 부모 -> 자식
    int pipe2[2]; // 자식 -> 부모
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // 파이프 생성
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 자식 프로세스 생성
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {                    // 자식 프로세스
        close(pipe1[1]); // 부모 -> 자식 파이프의 쓰기 끝 닫기
        close(pipe2[0]); // 자식 -> 부모 파이프의 읽기 끝 닫기

        // 부모로부터 메시지 읽기
        read(pipe1[0], buffer, BUFFER_SIZE);
        printf("Child received: %s\n", buffer);

        // 부모에게 응답 메시지 보내기
        char *response = "Hello from Child!";
        write(pipe2[1], response, strlen(response) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {                    // 부모 프로세스
        close(pipe1[0]); // 부모 -> 자식 파이프의 읽기 끝 닫기
        close(pipe2[1]); // 자식 -> 부모 파이프의 쓰기 끝 닫기

        // 자식에게 메시지 보내기
        char *message = "Hello from Parent!";
        write(pipe1[1], message, strlen(message) + 1);

        // 자식으로부터 응답 메시지 읽기
        read(pipe2[0], buffer, BUFFER_SIZE);
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL); // 자식 프로세스 종료 대기
        printf("Child process has terminated.\n");
    }

    return 0;
}