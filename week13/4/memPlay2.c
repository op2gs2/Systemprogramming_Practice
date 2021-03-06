#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &statbuf) == -1) { // 파일의 상세 정보 검색
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, \
    MAP_SHARED, fd, (off_t)0); // 메모리 매핑
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);

    switch(pid = fork()){
        case -1 : /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0 : /* child process */
            for(int i = 0; i < 100; i++){
                int random = rand()%99;
                addr[random] = 'c';
                msync(addr, statbuf.st_size, MS_SYNC); // 수정 내용 동기화
                sleep(1);
            }
            break;
        default : /* parent process */
            for(int i = 0; i < 100; i++){
                int random = rand()%49;
                addr[random] = 'p';
                msync(addr, statbuf.st_size, MS_SYNC); // 수정 내용 동기화
                sleep(1);
            }
            break;
    }
    return 0;
}