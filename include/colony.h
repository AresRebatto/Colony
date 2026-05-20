#include "colonist.h"

#ifndef COLONY
#define COLONY
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

	int generate_colonist(Colony*);
#endif