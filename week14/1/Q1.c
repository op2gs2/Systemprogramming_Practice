#include <signal.h>
#include <stdio.h>

int main(void) {
    sigset_t st; // 시그널 집합을 정의

    sigemptyset(&st); // 시그널 집합을 0으로 초기화(비우기)

    sigfillset(&st); // 시그널 집합을 모두 활성화

    if (sigismember(&st, SIGBUS)) // SIGINT가 설정되어 있는지 여부를 확인
        printf("SIGINT is set.\n");
    else
        printf("SIGINT is not set.\n");

    return 0;
}