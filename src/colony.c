#include "../include/colony.h"
#include "../include/colonist.h"

#include <stdlib.h>

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
