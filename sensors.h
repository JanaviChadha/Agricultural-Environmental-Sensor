#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "plants.h"

#ifndef SENSORS_H_
#define SENSORS_H_

class Sensor
{
public:
	int raw;
	virtual Sensor() { raw = 0; }
	virtual int setup();
	virtual char *getName(char *buffer);
	virtual int getRaw();
	virtual int update();
	virtual char *getFriendlyReading(char *buffer);
	virtual bool goodForPlant(Plant p);
	virtual ~Sensor() {}
};

class DHTTempSensor : public Sensor {
public:
	int pin;
	DHT *dht;

	DHTTempSensor();
	DHTTempSensor(int pin);

	int setup();
	char *getName(char *buffer);
	int update();
	char *getFriendlyReading(char *buffer);
	bool goodForPlant(Plant p);
	virtual ~DHTTempSensor() {}
};

class DHTHumidSensor : public Sensor {
public:
	int pin;
	DHT *dht;

	DHTHumidSensor();
	DHTHumidSensor(int pin);

	int setup();
	char *getName(char *buffer);
	int update();
	char *getFriendlyReading(char *buffer);
	virtual ~DHTHumidSensor() {}

};

class LightSensor : public Sensor {
public:
	int pin;

	LightSensor();
	LightSensor(int pin);

	char *getName(char *buffer);
	int update();
	char *getFriendlyReading(char *buffer);
	bool goodForPlant(Plant p);
	virtual ~LightSensor() {}

};

class SMSensor : public Sensor {
public:
	int pin;

	SMSensor();
	SMSensor(int pin);

	char *getName(char *buffer);
	int update();
	char *getFriendlyReading(char *buffer);
	virtual ~SMSensor() {}

};

class RainSensor : public Sensor {
public:
	int pin;

	RainSensor();
	RainSensor(int pin);

	char *getName(char *buffer);
	int update();
	char *getFriendlyReading(char *buffer);
	bool goodForPlant(Plant p);
	virtual ~RainSensor() {}
};

class PHSensor : public Sensor {
private:
	double getPH();
public:
	int pin;

	PHSensor();
	PHSensor(int pin);

	char *getName(char *buffer);
	int update();
	char *getFriendlyReading(char *buffer);
	bool goodForPlant(Plant p);
	virtual ~PHSensor() {}
};

#endif /* SENSORS_H_ */
