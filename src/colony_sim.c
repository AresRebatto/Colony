#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <time.h>

#include "../include/colony.h"
#include "../include/colonist.h"
#include "../include/terminal.h"
#include "../include/log.h"

struct timespec ts;

int main(void){

	//random seed
	clock_gettime(CLOCK_MONOTONIC, &ts);
	log_init("logs.txt");

	srand(ts.tv_nsec);

	enableRawMode();
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); //Read doesn't block the program
	write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);
	int seconds = 0;
	char c;

	//Obtain terminal size in order to generate colony
	struct winsize terminalSize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);

	//The area of the terminal
	char *world = malloc(sizeof(char) * terminalSize.ws_col * terminalSize.ws_row);


	//Generate the colony
	Colony colony = {
		.x = rand()%terminalSize.ws_col,
		.y = rand()%terminalSize.ws_row,
		.colonist_num = 0
	} ;

	put_pixel(colony.y, colony.x, '#');
	world[colony.y * terminalSize.ws_col + colony.x] = '#';


	while (1) {
		//Generate a new colonist every 5 seconds
		if(seconds%5 == 0 && generate_colonist(&colony, world, terminalSize.ws_col, terminalSize.ws_row )){
			disableRawMode();
			fprintf(stderr, "Allocation error");
			log_close();
			exit(1);
		}

		if(move_all_colonists(&colony, world, terminalSize.ws_col, terminalSize.ws_row)){
			disableRawMode();
			fprintf(stderr, "Allocation error");
			log_close();
			exit(1);
		}


		sleep(1);
		terminal_rerender(world, terminalSize.ws_col, terminalSize.ws_row);
		seconds++;

	    if (read(STDIN_FILENO, &c, 1) == 1 && c == 'q')
	        break;
	}

	log_close();
   	disableRawMode();
	return 0;
}
