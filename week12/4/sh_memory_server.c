#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <stdlib.h>

void handler(int dummy){
    ;
}

int main(int argc, char *argv[]) {
    key_t key;
    int shmid, index;
    void *shmaddr;
    char buf[128];
    sigset_t mask;

    key = ftok("shmfile", 1); // 키 생성
    shmid = shmget(key, 128, IPC_CREAT|0666); // 공유 메모리 생성

    /* 시그널 처리를 설정하는 부분 (학기말에 배울 내용…) */
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1); // SIGUSR1 라는 시그널을 제외하고 모든 시그널을 블록함
    sigset(SIGUSR1, handler); // SIGUSR1 시그널 수신 시, 처리를 담당할 함수 설정

    printf("Listener wait for Talker\n");
    sigsuspend(&mask); // SIGUSR1 시그널을 받을 때까지 기다림

    /* 공유메모리에 읽기*/
    printf("Listener Start =====\n");
    shmaddr = shmat(shmid, NULL, 0);
    strcpy(buf, shmaddr); // 공유 메모리 읽기
    sigsuspend(&mask); // SIGUSR1 시그널을 받을 때까지 기다림
    // 파일 다운 받기
    if (buf[0] == '0'){
        strcpy(buf, shmaddr); // 공유 메모리 읽기
        FILE *fp;
        if((fp = fopen(buf,"r")) == NULL){
            strcpy(buf, "No Such File\n");
            perror("fopen");
            exit(1);
        }
        // 파일 사이즈 구하기
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        
        // 데이터 읽어 들이기
        size_t result = fread(buf, size, 1, fp);
        if (result != size) {
            fputs("Reading error", stderr);
            strcpy(buf,"Reading error");
            exit(3);
        }

    } 
    
    // 클라이언트 메시지 받기
    if(buf[0] == '1') {
        strcpy(buf, shmaddr); // 공유 메모리 읽기
        printf("Client Message: %s\n",buf);
    }

    /* 공유메모리에 쓰기*/
    strcpy(shmaddr, buf); // 공유 메모리에 쓰기
    sleep(3); // 공유 메모리 상태를 조회할 시간을 벌기 위해 딜레이 추가
    shmdt(shmaddr); // 공유 메모리 연결 해제
    exit(1);
}