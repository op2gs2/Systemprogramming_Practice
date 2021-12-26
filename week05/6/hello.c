#include <ncurses.h>
#include <stdio.h>

int main(void){
    initscr();
    printw("Hello world!!!");
    refresh();
    getch();
    endwin();

    return 0;
}