#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    int status;
    
    pid = fork();

    if(pid == 0){ // Son Process
        sleep(5);
    } else if (pid > 0){ // Parent Process
        while (wait(&status) != pid)
                continue;
        sleep(5);
    } else { // If fork is failed.
        printf("Fork Fail");
    }
    return 0;
}