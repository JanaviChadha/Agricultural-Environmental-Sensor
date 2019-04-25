#include "PROGMEM_readAnything.h"
#include "plants.h"

Plant getPlant(int plant) {
	return PROGMEM_getAnything(&plants[plant]);
}
