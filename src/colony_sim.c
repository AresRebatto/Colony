#include <asm-generic/ioctls.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>


#include "../include/colony.h"
#include "../include/colonist.h"
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
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig);
    atexit(disableRawMode);

    struct termios raw = orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void){

	enableRawMode();
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); //Read doesn't block the program
	write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);

	char c;

	//Obtain terminal size in order to generate colony
	struct winsize terminalSize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);

	Colony colony = {
		.x = rand()%terminalSize.ws_col+1,
		.y = rand()%terminalSize.ws_row+1,
	} ;

	put_pixel(colony.y, colony.x, '#');

	while (1) {

		sleep(1);


	    if (read(STDIN_FILENO, &c, 1) == 1 && c == 'q')
	        break;
	}

   disableRawMode();
	return 0;
}
