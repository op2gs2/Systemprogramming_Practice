#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE* fp;
    char c;
    int parent_num, child_num;
    fp = fopen(argv[1], "r");

    while((c = (char)fgetc(fp)) != -1){
        if(c == 'p'){
            parent_num++;
        } else if (c == 'c'){
            child_num++;
        }
    }

    if (parent_num > child_num){
        printf("Parent won! (%d)\n", parent_num);
    } else if(parent_num < child_num){
        printf("Child on! (%d)\n", child_num);
    } else{
        printf("Even!\n");
    }
    
}