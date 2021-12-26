#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <unistd.h>

struct mymsgbuf {
    long mtype;
    char mtext[80];
};

int main(void) {
    key_t key;
    int msgid_send, msgid_recv;
    struct mymsgbuf mesg;
    struct mymsgbuf inmsg;

    // 송신 메시지 큐 생성
    key = ftok("keyfile", 1);
    msgid_send = msgget(key, IPC_CREAT|0644);
    if (msgid_send == -1) {
        perror("msgget");
        exit(1);
    }

    // 수신 메시지 큐 생성
    key = ftok("keyfile2", 2);
    msgid_recv = msgget(key, IPC_CREAT|0644);
    if (msgid_recv == -1) {
        perror("msgget");
        exit(1);
    }

    mesg.mtype = 1; // 유형을 1로 정의
    strcpy(inmsg.mtext, "\0");

    printf("Input Message: ");
    scanf("%s",mesg.mtext);
    if (msgsnd(msgid_send, (void *)&mesg, 80, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    while(1){
        // 메시지 송,수신
        if(msgrcv(msgid_recv, &inmsg, 80, 0, IPC_NOWAIT) == -1){ // 메시지 큐가 비어있으면, 메시지를 보내고
            printf("Input Message: ");
            scanf("%s",mesg.mtext);
            if (msgsnd(msgid_send, (void *)&mesg, 80, 0) == -1) {
                perror("msgsnd");
                exit(1);
            }
        } else { // 메시지 큐가 비어있지 않으면, 받는다.
            if(strcmp(inmsg.mtext,mesg.mtext) == 0){ // 받으려는 메시지 큐가, 보낸 큐와 같으면 다시 보낸다.
                msgsnd(msgid_send, (void *)&mesg, 80, IPC_NOWAIT);
            } else { // 받는 메시지 큐가, 보낸 메시지 큐와 같지 않으면 출력한다.
                printf("Received Msg = %s\n", inmsg.mtext);
            }
        }
    }

    return 0;
}