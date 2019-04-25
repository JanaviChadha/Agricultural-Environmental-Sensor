#include <Arduino.h>
#include <avr/pgmspace.h>

#ifndef PLANTS_H_
#define PLANTS_H_

#define LOWRAIN 0
#define MEDRAIN 1
#define HIGHRAIN 2

#define LOWSUN 0
#define MEDSUN 1
#define FULLSUN 2

#define PLANT_COUNT 17

struct Plant
{
	char plantName[20];
	char minTemp;
	char maxTemp;
	char rainAmount;
	float minPH;
	float maxPH;
	char sunAmount;
};

const Plant plants[PLANT_COUNT] PROGMEM = {

	{"Sunflower",		50,	80,	LOWRAIN,	6,		7.5,	FULLSUN},
	{"Rosemary",		59,	68,	MEDRAIN,	5,		6,		FULLSUN},
	{"Mint",			70,	75,	HIGHRAIN,	6,		7,		MEDSUN},
	{"Tomato",			61,	95,	LOWRAIN,	6,		6.8,	MEDSUN},
	{"Chillies",		64,	95,	LOWRAIN,	5,		6,		MEDSUN},
	{"Okra",			68,	95,	MEDRAIN,	6.5,	7,		MEDSUN},
	{"Onion",			46,	86,	HIGHRAIN,	5.5,	6.5,	FULLSUN},
	{"Strawberries",	50,	68,	HIGHRAIN,	5.5,	6.5,	MEDSUN},
	{"Corn",			61,	95,	LOWRAIN,	5.8,	6.8,	FULLSUN},
	{"Radish",			46,	86,	MEDRAIN,	7,		7,		FULLSUN},
	{"Peas",			46,	75,	LOWRAIN,	5.8,	7,		MEDSUN},
	{"Celery",			54,	70,	MEDRAIN,	5.7,	6,		MEDSUN},
	{"Potato",			50,	88,	MEDRAIN,	4.8,	5.4,	LOWSUN},
	{"Cucumber",		61,	95,	HIGHRAIN,	5.5,	7,		FULLSUN},
	{"Carrot",			46,	86,	HIGHRAIN,	5.5,	7.5,	FULLSUN},
	{"Sage",			50,	77,	LOWRAIN,	6,		7,		MEDSUN},
	{"Cauliflower",		50,	86,	MEDRAIN,	6,		7,		MEDSUN}

};

Plant getPlant(int i);

#endif /* PLANTS_H_ */
