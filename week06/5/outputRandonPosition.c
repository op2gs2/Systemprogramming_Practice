#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char mesg[]="Just a string";
    int row, col;
    srand(time(NULL));
    int rand_row = 0, rand_col=0;

    initscr();
    getmaxyx(stdscr,row,col);

    // 위치에 대한 랜덤값을 구함
    rand_row = rand()%row+1;
    rand_col = rand()%col+1;
    // 위에서 구한 위치 정보로 mesg를 출력함
    mvprintw(rand_row/2,rand_col/2,mesg,row,col);
    refresh();
    getch();
    endwin();

    return 0;
}