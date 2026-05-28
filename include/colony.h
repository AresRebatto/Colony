#ifndef COLONY_H
#define COLONY_H
	#include "colonist.h"
	#include "coordinates.h"

	typedef struct ColonistNode ColonistNode;

	struct ColonistNode{
		Colonist colonist;
		ColonistNode *next_colonist;
	};

	typedef struct Colony{
		int x,y;//Where colonist will be generated
		ColonistNode* colonists;
		int colonist_num;
	}Colony;

	static Coordinates *new_position(ColonistNode *cn,  char *world,  int cols, int rows );
	int generate_colonist(Colony*,  char *world,  int cols, int rows);
	int move_all_colonists(Colony *, char *, int, int);
#endif
