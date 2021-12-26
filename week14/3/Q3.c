#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(void) {
    sigset_t new;

    sigemptyset(&new); // 시그널 집합에서 모든 시그널을 0으로 설정
    sigaddset(&new, SIGINT); // SIGINT를 시그널 집합에 추가
    sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL); // 시그널 집합에 대해 블로킹 설정

    for(int i = 0; i< 9; i++){
        printf("Hallym Software\n");
        sleep(1);
    }

    printf("Unblock Signal\n");
    sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL); // 시그널 집합에 대해 언블로킹 설정
    return 0;
}