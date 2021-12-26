#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int status;
    int max_proc = 5;
    int count = 1;
    int wait_time = atoi(argv[1]);
    char c = '\0';

    while((c = getopt(argc, argv, "r:")) != -1){
        switch(c){
            case 'r':
                max_proc = atoi(argv[3]);
                #ifdef DEBUG
                    printf("Count: %d\n", count);
                #endif
                break;
            case '?':
                fprintf(stderr,"argv error\n");
                exit(2);
                break;
        }
    }

    printf("\n<Process DashBoard>\n\n");
    printf("* Running Process (%d) :\n",max_proc);

    
    
    while(1){
        pid = fork();
        
        if(pid == 0){ // Child Process
            #ifdef DEBUG    
                printf("Child Process: %d\n",(int)getpid());
            #endif

            if(count <= max_proc){
                printf("%d\n",(int)getpid());
                count++;
            }
            
            sleep(wait_time);
        } 
        
        else if (pid > 0){ // Parent Process
            #ifdef DEBUG    
                printf("Parent Process: %d\n",(int)getpid());
            #endif
            
            while (wait(&status) != pid)
                    continue;
            
            sleep(wait_time);
        } 
        
        else { // If fork is failed.
            printf("Fork Fail");
        }

    }
    return 0;
}