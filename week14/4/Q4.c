#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(void){
    printf("At handler : Wake up!\n");
}

int main(void) {
    void (*hand)(int); // 시그널 핸들러 호출 결과 저장
    hand = signal(SIGALRM, handler); // 시그널 핸들러 호출
    if (hand == SIG_ERR) { 
        perror("signal"); // 시그널 핸들러 호출 에러 발생!
        exit(1);
    }

    for( int i = 0 ; i < 5 ; i++ ) {
            alarm(2); // 2초 설정
            printf("Pause ...\n");
            pause(); // 시그널 입력을 기다림
    }
    printf("Bye~\n");
    return 0;
}