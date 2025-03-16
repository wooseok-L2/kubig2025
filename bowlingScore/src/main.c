#include <stdio.h>

#define FRAMES 10

int main() {
    int rolls[21] = {0}; // 최대 21번의 투구 가능 (10 프레임 + 스트라이크 보너스)
    int totalScore = 0;
    int rollIndex = 0;

    // 입력 받기
    printf("볼링 점수 계산기\n");
    for (int i = 0; i < FRAMES; i++) {
        printf("프레임 %d 첫 번째 투구: ", i + 1);
        scanf("%d", &rolls[rollIndex]);
        if (rolls[rollIndex] == 10) { // 스트라이크
            printf("스트라이크!\n");
            rollIndex++;
            continue; // 다음 프레임으로 이동
        }

        printf("프레임 %d 두 번째 투구: ", i + 1);
        scanf("%d", &rolls[rollIndex + 1]);
        rollIndex += 2;
    }

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

    return 0;
}
