#include <fcntl.h>  // O_WRONLY 플래그를 위해 포함
#include <mqueue.h> // POSIX 메시지 큐 함수(mq_open, mq_send 등)를 위해 포함
#include <stdio.h>  // 표준 입출력 함수(printf, perror)를 위해 포함
#include <stdlib.h> // exit 함수를 위해 포함
#include <string.h> // 문자열 조작 함수(strcpy)를 위해 포함

#define QUEUE_NAME "/myqueue" // 메시지 큐의 이름(서버와 동일)
#define MAX_MSG_SIZE 128      // 최대 메시지 크기(서버와 동일)

int main()
{
    // 메시지 큐 열기(O_WRONLY: 전송 전용)
    mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1)
    { // 실패 시 에러 출력 및 종료
        perror("mq_open");
        exit(1);
    }

    // 전송할 메시지 준비
    char message[] = "Hello from Client!";
    // 메시지 전송(우선순위 0, 기본값)
    if (mq_send(mq, message, strlen(message) + 1, 0) == -1)
    {
        perror("mq_send");
        exit(1);
    }
    printf("Client sent: %s\n", message);

    // 메시지 큐 닫기
    if (mq_close(mq) == -1)
    {
        perror("mq_close");
        exit(1);
    }

    return 0; // 프로그램 정상 종료
}