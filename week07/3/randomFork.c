#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char * argv[]){
    pid_t pid;
    int status;
    int count=1;
    double in_probability = atof(argv[1]);
    double probability = 0.0;
    
    printf("Probability: %f\n", in_probability);

    if(argc != 2){
        perror("Check Argument Number");
        exit(2);
    }

    srand(time(0));

    while ((rand() / (RAND_MAX * 1.0))<=in_probability){
        pid = fork();
        printf("PID: %d\t PPID: %d\n",(int)getpid(),(int)getppid());

        if(pid>0){ // 부모프로세스
            printf("waited PID: %d\n",wait(&status)); // 자식프로세스를 wait 한 뒤, 반환값 출력
        }

        else if(pid == 0){ // 자식프로세스
            #ifdef DEBUG
                printf("Child Process.\n");
                printf("Count: %d\n",count);
            #endif
            count++; 
        }
    }


    
    return 0;

}