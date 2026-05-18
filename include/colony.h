#include "colonist.h"

#ifndef COLONY
#define COLONY
	typedef struct ColonistNode ColonistNode;

	struct ColonistNode{
		Colonist colonist;
		Colonist *next_colonist;
	};

	typedef struct Colony{
		int x,y;//Where colonist will be generated
		ColonistNode* colonists;
	}Colony;
#endif