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
    struct mymsgbuf inmsg;
    struct mymsgbuf mesg;
    key_t key;
    int recv_msgid, send_msgid;

    key = ftok("keyfile", 1); // 송신측과 같은 키값 생성
    if ((recv_msgid = msgget(key, 0)) < 0) {
        perror("msgget");
        exit(1);
    }

    key = ftok("keyfile2", 2); // 송신측과 같은 키값 생성
    if ((send_msgid = msgget(key, 0)) < 0) {
        perror("msgget");
        exit(1);
    }

    strcpy(inmsg.mtext, "\0");

    msgrcv(recv_msgid, &inmsg, 80, 0, 0);
    printf("Received Msg = %s\n", inmsg.mtext);
    while(1){
        // 메시지 송,수신
        if(msgrcv(recv_msgid, &inmsg, 80, 0, IPC_NOWAIT) == -1){ // 메시지 큐가 비어있으면, 메시지를 보내고
            printf("Input Message: ");
            scanf("%s",mesg.mtext);
            if (msgsnd(send_msgid, (void *)&mesg, 80, 0) == -1) {
                perror("msgsnd");
                exit(1);
            }
        } else { // 메시지 큐가 비어있지 않으면, 받는다.
            if(strcmp(inmsg.mtext,mesg.mtext) == 0){ // 받으려는 메시지 큐가, 보낸 큐와 같으면 다시 보낸다.
                msgsnd(send_msgid, (void *)&mesg, 80, IPC_NOWAIT);
            } else { // 받는 메시지 큐가, 보낸 메시지 큐와 같지 않으면 출력한다.
                printf("Received Msg = %s\n", inmsg.mtext);
            }
        }
    }
    
    return 0;
}