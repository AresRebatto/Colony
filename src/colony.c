#include "../include/colony.h"
#include "../include/colonist.h"
#include "../include/coordinates.h"

#include <stdlib.h>

#define IS_OUT_OF_TERM (new_x < 0 || new_x >= cols || new_y < 0 || new_y >= rows)
#define IS_NEW_CELL_EMPTY (world[new_y * cols + new_x] != 'o' && world[new_y * cols + new_x] != '#')
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
static Coordinates *new_position(ColonistNode *cn,  char *world,  int cols, int rows ){
	int new_y = 0;
	int new_x = 0;

	do{
		int step = rand()%8;

		new_x = cn->colonist.x + dx[step];
		new_y = cn->colonist.y + dy[step];

	}while(IS_OUT_OF_TERM && IS_NEW_CELL_EMPTY);

	Coordinates *coordinates = malloc(sizeof(Coordinates));

	if(coordinates == NULL) return NULL;

	coordinates->x = new_x;
	coordinates->y = new_y;

	return coordinates;
}

int generate_colonist(Colony* colony,  char *world,  int cols, int rows){
 	ColonistNode *new_node = malloc(sizeof(ColonistNode));
    if (new_node == NULL) return 1;


    new_node->next_colonist = NULL;
    new_node->colonist.id       = colony->colonist_num;
    new_node->colonist.hungry   = 0;
    new_node->colonist.sex      = rand() % 2;
    new_node->colonist.x        = colony->x;
    new_node->colonist.y        = colony->y;

    Coordinates *coordinates = new_position(new_node, world, cols, rows);

    if(coordinates == NULL) return 1;

    //It starts from the colony, but it can't overwrite it
    new_node->colonist.x        = coordinates->x;
    new_node->colonist.y        = coordinates->y;

    if (colony->colonists == NULL) {
        colony->colonists = new_node;
    } else {
        ColonistNode *last = colony->colonists;
        while (last->next_colonist != NULL)
            last = last->next_colonist;
        last->next_colonist = new_node;
    }

    colony->colonist_num++;
    free(coordinates);
	return 0;
}

int move_all_colonists(Colony *colony, char *world,  int cols, int rows){
	for(ColonistNode *cn = colony->colonists; cn; cn = cn->next_colonist){

		Coordinates *new_coordinates = new_position(cn, world, cols, rows);

		if(new_coordinates == NULL) return 1;

		world[cn->colonist.y * cols + cn->colonist.x] = ' ';

		cn->colonist.x = new_coordinates->x;
		cn->colonist.y = new_coordinates->y;

		world[cn->colonist.y * cols + cn->colonist.x] = 'o';

		free(new_coordinates);
	}

	return 0;
}
