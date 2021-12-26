#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    // 인자가 맞지 않다면, 종료
    if(argc != 3){
        printf("Argument Error!");
        exit(1);
    }

    char *val;
    
    val = getenv(argv[1]);
    
    // 환경변수를 가져올 수 있는지 판별함
    if (val == NULL)
        printf("%s not defined\n", argv[1]);
    else{
        // 환경변수 안에 입력한 문자열이 있는지 확인함
        if(strstr(val,argv[2])!=NULL){
            printf("%s has %s!\n",argv[1], argv[2]);
        }
        else{
            printf("%s does not have %s!\n",argv[1], argv[2]);
        }
    }
        
        
    return 0;
}