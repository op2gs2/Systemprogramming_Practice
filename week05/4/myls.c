#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    DIR *dp;
    struct dirent *dent;
    char current_dir[BUFSIZ]={};
    char *directory = NULL;
    char *regular_names[BUFSIZ]={NULL};
    int regular_cnt = 0;
    char *directory_names[BUFSIZ]={NULL};
    int directory_cnt = 0;

    // 0. Check argc.
    if (argc != 1){
        perror("Worng Arguemnts");
        exit(1);
    }

    // 1. Read a current position.
    directory = getcwd(current_dir,BUFSIZ);
    
    // 2. Open directories of a given names.
    if (( dp = opendir(directory)) == NULL){
        perror("Opendir");
        exit(1);
    }

    // 3. Read directories of a given names.
    // And, store names if file type is regualr or directory.
    while ((dent = readdir(dp))){
        if(dent -> d_name[0] == '.') continue;
        else if (dent -> d_type == DT_DIR){
            directory_names[directory_cnt++] = dent -> d_name;
            #ifdef DEBUG
            printf("%s\n",directory_names[directory_cnt]);
            #endif
        } else if(dent -> d_type == DT_REG){
            regular_names[regular_cnt++] = dent -> d_name;
            #ifdef DEBUG
            printf("%s\n",regular_names[regular_cnt]);
            #endif
        }
    }

    // 4. Print Result.
    int i = 0;
    printf("<Regular Files>\n");
    for(i=0; i<regular_cnt; i++){
        printf("%s\n",regular_names[i]);
    }
    printf("<Directories>\n");
    for(i=0; i<directory_cnt; i++){
        printf("%s\n",directory_names[i]);
    }

    closedir(dp);
    return 0;
}