#ifndef FOOD_H
#define FOOD_H

typedef enum{
	APPLE=2,
	COW=10,
	LARVA=4
}FoodKind;

typedef struct{
	int x,y;
	FoodKind foodKind;
}Food;
#endif