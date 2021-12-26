#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

void handler(void){
    printf("Nice to meet you!\n");
}

int main(void) {
    struct itimerval it;
    void (*hand)(int); // 시그널 핸들러 호출 결과 저장
    
    hand = signal(SIGALRM, handler); // 시그널 핸들러 호출
    if (hand == SIG_ERR) { 
        perror("signal"); // 시그널 핸들러 호출 에러 발생!
        exit(1);
    }

    sigset(SIGALRM, handler);
    it.it_value.tv_sec = 1; // 타이머 최초 시작 시간을 1초 뒤로 설정
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 1; // 타이머 간격을 1초로 설정
    it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &it, (struct itimerval *)NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1) {
        if (getitimer(ITIMER_REAL, &it) == -1) {
            perror("getitimer");
            exit(1);
        }
        pause(); // 시그널 입력을 기다림
    }

    return 0;
}