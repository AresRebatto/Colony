#include "../include/terminal.h"

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
struct termios orig;

void move_cursor(int row, int col) {
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", row, col);
    write(STDOUT_FILENO, buf, len);
}

void put_pixel(int row, int col, char c) {
    move_cursor(row, col);
    write(STDOUT_FILENO, &c, 1);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);

    //Show the cursor
    write(STDOUT_FILENO, "\x1b[?25h", 6);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig);
    atexit(disableRawMode);

    struct termios raw = orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    //Hide the cursor
    write(STDOUT_FILENO, "\x1b[?25l", 6);
}

void terminal_rerender(char *world, int cols, int rows){
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++)
			put_pixel(y, x, world[x+y]);
	}
}