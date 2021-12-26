#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void printmsg(void){
    char *print_message = "printmsg";
    printf("%s\n",print_message);
}

void *start_thread(void *message){
    pthread_mutex_lock(&mutex); // 뮤텍스 잠금
    int i;
    for(i=0; i<5; i++){
        printf("%s\n",(const char *)message);
    }
    printmsg();
    pthread_mutex_unlock(&mutex); // 뮤텍스 해제
}

int main(void){
    pthread_t thing1, thing2;
    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";

    while(1){ // 쓰레드 무제한 생성 (교착상태 유발)
        pthread_create(&thing1, NULL, start_thread, (void *) message1);
        pthread_create(&thing2, NULL, start_thread, (void *) message2);
    }

    pthread_join(thing1, NULL);
    pthread_join(thing2, NULL);
}