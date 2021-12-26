#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct studentinfo{
    char *name;
    char *major;
    char *univ;
}StudentInfo;

void *start_thread(void *student){
    int i;
    StudentInfo *stu = (StudentInfo *)student;
    for(i=0; i<=9; i++){
        //sleep(1);
        printf("%s\n", stu->name);
        printf("%s\n", stu->major);
        printf("%s\n", stu->univ);
        //sleep(1);
    }
}

int main(void){
    StudentInfo stu1 = {"Brad Pitt", "Computer Engineering", "Holly University"};
    StudentInfo stu2 = {"Angelina Jollie", "Computer Science", "Wood University"};
    pthread_t thing1, thing2;

    pthread_create(&thing1, NULL, start_thread, (void *) &stu1);
    pthread_create(&thing2, NULL, start_thread, (void *) &stu2);

    pthread_join(thing1, NULL);
    pthread_join(thing2, NULL);
}