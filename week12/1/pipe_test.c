#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    char buf[256];

    fp = popen("ls / | grep s", "r"); // 파이프 통신을 위한 FILE 포인터 획득
    if (fp == NULL) {
        fprintf(stderr, "popen failed\n");
        exit(1);
    }
    
    while (fgets(buf, sizeof(buf), fp) != NULL){
        printf(buf);
        continue;
    }
    

    pclose(fp); // 파이프 닫기

    return 0;
}