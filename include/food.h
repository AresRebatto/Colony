#ifndef FOOD
#define FOOD

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