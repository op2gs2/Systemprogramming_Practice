#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void printmsg(void){
    char *print_message = "printmsg";
    printf("%s\n",print_message);
}

void *start_thread(void *message){
    int i;
    for(i=0; i<5; i++){
        printf("%s\n",(const char *)message);
    }
    printmsg(); 
}

int main(void){
    pthread_t thing1, thing2;
    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";

    while(1){ // 스레드 생성 (교착상태 유발)
        pthread_create(&thing1, NULL, start_thread, (void *) message1);
        pthread_create(&thing2, NULL, start_thread, (void *) message2);
    }

    // 스레드가 종료할 때 까지 기다림.
    pthread_join(thing1, NULL);
    pthread_join(thing2, NULL);
}