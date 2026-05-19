#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "../include/colony.h"
#include "../include/colonist.h"
#include "../include/terminal.h"

int main(void){

	enableRawMode();
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); //Read doesn't block the program
	write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);

	char c;

	//Obtain terminal size in order to generate colony
	struct winsize terminalSize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);

	//The area of the terminal
	char *world = malloc(sizeof(char) * terminalSize.ws_col * terminalSize.ws_row);


	Colony colony = {
		.x = rand()%terminalSize.ws_col,
		.y = rand()%terminalSize.ws_row,
	} ;

	put_pixel(colony.y, colony.x, '#');
	// accesso: world[y * terminalSize.ws_col + x]
	world[colony.y * terminalSize.ws_col + colony.x] = '#';

	while (1) {

		sleep(1);


	    if (read(STDIN_FILENO, &c, 1) == 1 && c == 'q')
	        break;
	}

   disableRawMode();
	return 0;
}
