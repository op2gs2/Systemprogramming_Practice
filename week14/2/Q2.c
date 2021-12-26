#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo){
    printf("SIGQUIT handler is called!\n");
}

int main(void) {
    // 시그널 핸들러 호출 결과 저장
    void (*hand)(int);

    hand = signal(SIGQUIT, handler); // 시그널 핸들러 지정
    if (hand == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    pause(); // 시그널 입력을 기다림

    return 0;
}