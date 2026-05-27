#include <stdint.h>

#ifndef COLONIST_H
#define COLONIST_H
	typedef enum{
		MALE,
		FEMALE
	}Sex;
	typedef struct {
		uint8_t id; //max=255
		uint8_t hungry; //From 0 to 255


		//If two settlers of the opposite sex meet
		// and have a hunger level below 50, they
		// produce a new colonist in addition to
		// those produced by the colony
		Sex sex;

		int x, y;

	}Colonist;

#endif
