#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    key_t key;
    int shmid;
    void *shmaddr;
    char buf[128];

    key = ftok("shmfile", 1); // 서버(listener)와 같은 키를 생성함
    shmid = shmget(key, 128, 0); // 공유 메모리 식별자 읽어오기

    shmaddr = shmat(shmid, NULL, 0); // 공유 메모리 연결
    printf("File download is 0, Send message is 1\n");
    scanf("%s",buf);
    strcpy(shmaddr, buf); // 공유 메모리에 데이터 기록하기
    kill(atoi(argv[1]), SIGUSR1); // 인자로 받은 Listener의 PID를 지정하고 USRSIG1 신호발송

    printf("Input message or Input Filename\n");
    scanf("%s",buf);
    strcpy(shmaddr, buf); // 공유 메모리에 데이터 기록하기
 
    kill(atoi(argv[1]), SIGUSR1); // 인자로 받은 Listener의 PID를 지정하고 USRSIG1 신호발송
    sleep(2);
    strcpy(buf, shmaddr); // listener(서버)가 보낸 메시지 읽기

    printf("Listener said : %s\n", buf); // 서버가 보낸 메시지 출력
    shmdt(shmaddr); // 공유 메모리 연결 해제
    shmctl(shmid, IPC_RMID, NULL); // 공유 메모리 삭제

    return 0;
}



