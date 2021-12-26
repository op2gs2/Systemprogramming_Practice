#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#define CLK_TCK sysconf(_SC_CLK_TCK)
#define SIZ 1000000

void func_O1(time_t);
void func_ON(time_t);
void func_ON2(time_t);

// 함수 내부에서 변수를 선언하는 것도, 
// 실행시간에 영향을 미치므로, 전역변수로 선언함
int i = 0, j = 0, result = 0;

int main(void){
    time_t t;
    struct tms mytms;
    clock_t start_time, end_time;
    double time_O1 = 0, time_ON = 0, time_ON2 = 0;

    //O(1)에 대한 실행시간 측정
    if((start_time = times(&mytms)) == -1){
        perror("start_time_O1");
        exit(1);
    }
    func_O1(t);
    if((end_time = times(&mytms)) == -1){
        perror("end_time_O1");
        exit(1);
    }
    time_O1 = (double)(end_time-start_time) / CLK_TCK;
    printf("func_O1 takes %.1f seconds\n",time_O1);

    //O(N)에 대한 실행시간 측정
    if((start_time = times(&mytms)) == -1){
        perror("start_time_ON");
        exit(1);
    }
    func_ON(t);
    if((end_time = times(&mytms)) == -1){
        perror("end_time_ON");
        exit(1);
    }
    time_ON = (double)(end_time-start_time) / CLK_TCK;
    printf("func_ON takes %.1f seconds\n",time_ON);

    //O(N^2)에 대한 실행시간 측정
    if((start_time = times(&mytms)) == -1){
        perror("start_time_ON2");
        exit(1);
    }
    func_ON2(t);
    if((end_time = times(&mytms)) == -1){
        perror("end_time_ON2");
        exit(1);
    }
    time_ON2 = (double)(end_time-start_time) / CLK_TCK;
    printf("func_ON2 takes %.1f seconds\n",time_ON2);

    return 0;
}

// O(1) 시험용 함수
void func_O1(time_t t){
    srand(time(&t));
}

// O(N) 시험용 함수
void func_ON(time_t t){
    for(i=0; i<SIZ; i++){
        srand(time(&t));
    }
}

// O(N^2) 시험용 함수
void func_ON2(time_t t){
    for(i=0; i<100; i++){
        for(j=0; j<SIZ; j++){
            srand(time(&t));
        }
    }
}