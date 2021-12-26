#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct utsname uts;
    int option = -99;
    char *s_buf = " ";
    char n_buf[20] = " ";
    char v_buf[20] = " ";
    char m_buf[20] = " ";

    #ifdef DEBUG
        printf("변수선언 완료\n");
    #endif

    // uname으로 시스템의 정보를 받아와서, utsname 구조체에 저장
    if (uname(&uts) == -1) {
        perror("uname");
        exit(1);
    }

    #ifdef DEBUG
        printf("초기함수 실행 완료\n");
    #endif

    // getopt()에 따라 얻은 인자에 따라, 프로그램을 실행
    while((option = getopt(argc, argv, "snvm")) != -1){
        switch (option){
            case 's':
                s_buf = uts.sysname;
                strcat(s_buf," machine");

                #ifdef DEBUG
                    printf("s_buf: %s\n",s_buf);
                #endif

                break;
            
            case 'n':
                strcpy(n_buf, "named ");
                strcat(n_buf, uts.nodename);

                #ifdef DEBUG
                    printf("n_buf: %s\n",n_buf);
                #endif

                break;
            
            case 'v':
                strcat(v_buf, uts.release);

                #ifdef DEBUG
                    printf("v_buf: %s\n",v_buf);
                #endif

                break;

            case 'm':
                strcat(m_buf, uts.machine);

                #ifdef DEBUG
                    printf("m_buf: %s\n",m_buf);
                #endif

                break;
            
            default:
                break;
        }
    }    

    printf("This is a%s%s %s %s.\n", m_buf, v_buf, s_buf, n_buf);
    
 return 0;
}