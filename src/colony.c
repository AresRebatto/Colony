#include "../include/colony.h"
#include "../include/colonist.h"

#include <stdlib.h>

#define IS_OUT_OF_TERM (new_x < 0 || new_x >= cols || new_y < 0 || new_y >= rows)
static const int dx[8] = {
    -1, 0, 1,
     -1, 1, -1,
    0,-1
};

static const int dy[8] = {
    -1,-1,-1,
     0, 1, 1,
     1, 0
};

int generate_colonist(Colony* colony){
 	ColonistNode *new_node = malloc(sizeof(ColonistNode));
    if (new_node == NULL) return 1;

    new_node->next_colonist = NULL;
    new_node->colonist.id       = colony->colonist_num;
    new_node->colonist.hungry   = 0;
    new_node->colonist.sex      = rand() % 2;
    new_node->colonist.x        = colony->x;
    new_node->colonist.y        = colony->y;

    if (colony->colonists == NULL) {
        colony->colonists = new_node;
    } else {
        ColonistNode *last = colony->colonists;
        while (last->next_colonist != NULL)
            last = last->next_colonist;
        last->next_colonist = new_node;
    }

    colony->colonist_num++;

	return 0;
}

void move_all_colonists(Colony *colony, char *world,  int cols, int rows){
	for(ColonistNode *cn = colony->colonists; cn; cn = cn->next_colonist){
		/*
			0 1 2
			3 c 4
			5 6 7
		 */
		int new_y = 0;
		int new_x = 0;

		do{
			int step = rand()%8;

			new_x = cn->colonist.x + dx[step];
			new_y = cn->colonist.y + dy[step];

		}while(IS_OUT_OF_TERM);

		world[cn->colonist.y + cn->colonist.x] = ' ';

		cn->colonist.x = new_x;
		cn->colonist.y = new_y;

		world[cn->colonist.y + cn->colonist.x] = 'o';

	}
}
