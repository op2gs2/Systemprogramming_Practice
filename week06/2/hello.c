#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void){
    int rand_time = 0;

    // 시간관련 데이터를 저장하는 자료형
    time_t tt;
    // 현재시간을 기반으로, 랜덤 시드 초기화
    srand(time(&tt));
    // 1~30 중에서 랜덤한 숫자를 저장함
    rand_time = rand() % 30 + 1;

    #ifdef DEBUG
        printf("rand time is %d\n",rand_time);
    #endif

    printf("Hello world begins\n");
    sleep(rand_time);
    printf("Hello world ends\n");
}