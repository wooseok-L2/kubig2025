#include <fcntl.h>  // O_CREAT, O_RDONLY 등의 플래그를 위해 포함
#include <mqueue.h> // POSIX 메시지 큐 함수(mq_open, mq_receive 등)를 위해 포함
#include <stdio.h>  // 표준 입출력 함수(printf, perror)를 위해 포함
#include <stdlib.h> // exit 함수를 위해 포함
#include <string.h> // 문자열 조작 함수(strcpy)를 위해 포함

#define QUEUE_NAME "/myqueue" // 메시지 큐의 이름(파일 시스템 경로)
#define MAX_MSG_SIZE 128      // 최대 메시지 크기(128바이트)
#define QUEUE_PERMS 0666      // 메시지 큐 접근 권한(rw-rw-rw-)

int main()
{
    // 메시지 큐 속성 설정
    struct mq_attr attr;
    attr.mq_flags = 0;              // 비블록킹 플래그(0: 블록킹)
    attr.mq_maxmsg = 10;            // 큐에 저장 가능한 최대 메시지 수
    attr.mq_msgsize = MAX_MSG_SIZE; // 각 메시지의 최대 크기
    attr.mq_curmsgs = 0;            // 현재 메시지 수(초기화용)

    // 메시지 큐 생성 또는 열기(O_CREAT: 없으면 생성, O_RDONLY: 수신 전용)
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, QUEUE_PERMS, &attr);
    if (mq == -1)
    { // 실패 시 에러 출력 및 종료
        perror("mq_open");
        exit(1);
    }

    // 메시지 수신 버퍼
    char buffer[MAX_MSG_SIZE + 1]; // 널 종료 문자 포함
    ssize_t bytes_read;

    // 메시지 수신
    for (int i = 0; i < 5; i++)
    {
        // 메시지 수신(우선순위는 NULL로 설정)
        bytes_read = mq_receive(mq, buffer, MAX_MSG_SIZE + 1, NULL);
        if (bytes_read == -1)
        { // 실패 시 에러 출력
            perror("mq_receive");
            exit(1);
        }
        buffer[bytes_read] = '\0'; // 문자열 종료
        printf("Server received: %s\n", buffer);
    }

    // 메시지 큐 닫기
    if (mq_close(mq) == -1)
    {
        perror("mq_close");
        exit(1);
    }

    // 메시지 큐 삭제(파일 시스템에서 제거)
    if (mq_unlink(QUEUE_NAME) == -1)
    {
        perror("mq_unlink");
        exit(1);
    }

    return 0; // 프로그램 정상 종료
}