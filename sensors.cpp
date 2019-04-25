#include "sensors.h"
#include "Adafruit_Sensor.h"
#include "DHT.h"

#define READING_STRING_LENGTH 64

int readAverage(int pin, int count, int dt) {
	int sum = 0;

	for (int i = 0; i < count; i++) {
		sum += analogRead(pin);
		delay(dt);
	}

	return sum / count;
}

int Sensor::setup() { return 1; }
char* Sensor::getName(char *buffer) { strcpy(buffer, "Generic Sensor"); return buffer; }
int Sensor::update() { return this->raw; }
int Sensor::getRaw() { return this->raw; }
bool Sensor::goodForPlant(Plant p) { return false; }
char* Sensor::getFriendlyReading(char *buffer) { strcpy(buffer, "NO DATA"); return buffer; }

/****************************************************/
/*					TEMP SENSOR						*/
/****************************************************/

DHTTempSensor:: DHTTempSensor(int p):Sensor() {
	pin = p;
	dht = 0;
}

char* DHTTempSensor::getName(char *buffer) {
	strcpy(buffer, "Temperature");
	return buffer;
}

int DHTTempSensor::setup() {
	dht = new DHT(pin, DHT11);
	dht->begin();
	return dht;
}

int DHTTempSensor::update() {
	raw = dht->readTemperature(true);
	return raw;
}

bool DHTTempSensor::goodForPlant(Plant p) { return raw >= p.minTemp && raw <= p.maxTemp; }

char *DHTTempSensor::getFriendlyReading(char *buffer) {
	char rawStr[3];
	itoa(getRaw(), rawStr, 10);
	strcpy(buffer, (String(rawStr) + String("F")).c_str());
	return buffer;
}

/****************************************************/
/*					HUMID SENSOR					*/
/****************************************************/

DHTHumidSensor:: DHTHumidSensor(int p):Sensor() {
	pin = p;
	dht = 0;
}

char* DHTHumidSensor::getName(char *buffer) {
	strcpy(buffer, "Humidity");
	return buffer;
}

int DHTHumidSensor::setup() {
	dht = new DHT(pin, DHT11);
	dht->begin();
	return dht;
}

int DHTHumidSensor::update() {
	raw = dht->readHumidity();
	return raw;
}

char *DHTHumidSensor::getFriendlyReading(char *buffer) {
	char rawStr[3];
	itoa(getRaw(), rawStr, 10);
	strcpy(buffer, (String(rawStr) + String("%")).c_str());
	return buffer;
}

/****************************************************/
/*					LIGHT SENSOR					*/
/****************************************************/

LightSensor::LightSensor(int p) {
	pin = p;
}

char *LightSensor::getName(char *buffer) {
	strcpy(buffer, "Light Level");
	return buffer;
}

int LightSensor::update() {
	raw = 1023 - readAverage(pin, 5, 50);
	return raw;
}

bool LightSensor::goodForPlant(Plant p) {
	if (p.sunAmount == FULLSUN) {
		return raw > 900;
	} else if (p.sunAmount == MEDSUN) {
		return raw > 500 && raw <= 900;
	} else if (p.sunAmount == LOWSUN) {
		return raw > 200 && raw <= 500;
	}
	return false;
}

char *LightSensor::getFriendlyReading(char *buffer) {
	itoa(getRaw(), buffer, 10);
	return buffer;
}

/****************************************************/
/*				SOIL MOISTURE SENSOR				*/
/****************************************************/

SMSensor::SMSensor(int p) {
	pin = p;
}

char *SMSensor::getName(char *buffer) {
	strcpy(buffer, "Soil Moisture");
	return buffer;
}

int SMSensor::update() {
	raw = readAverage(pin, 5, 50);
	return raw;
}

char *SMSensor::getFriendlyReading(char *buffer) {
	char *str;
	if (raw > 500) {
		str = "WET";
	} else {
		str = "DRY";
	}
	strcpy(buffer, str);
	return buffer;
}

/****************************************************/
/*					RAIN SENSOR						*/
/****************************************************/

RainSensor::RainSensor(int p) {
	pin = p;
}

char *RainSensor::getName(char *buffer) {
	strcpy(buffer, "Rain Level");
	return buffer;
}

int RainSensor::update() {
	raw = readAverage(pin, 5, 50);
	return raw;
}

bool RainSensor::goodForPlant(Plant p) {
	if (p.rainAmount == HIGHRAIN) {
		return raw > 100;
	} else if (p.rainAmount == MEDRAIN) {
		return raw > 50 && raw <= 100;
	} else if (p.rainAmount == LOWRAIN) {
		return raw > 0 && raw <= 50;
	}
	return false;
}

char *RainSensor::getFriendlyReading(char *buffer) {
	itoa(getRaw(), buffer, 10);
	return buffer;
}

/****************************************************/
/*					PH SENSOR						*/
/****************************************************/

PHSensor::PHSensor(int p) {
	pin = p;
}

char *PHSensor::getName(char *buffer) {
	strcpy(buffer, "PH");
	return buffer;
}

int PHSensor::update() {
	raw = 392;//readAverage(pin, 10, 50);
	return raw;
}

double PHSensor::getPH() {
	double v = raw * 5.0 / 1024;
	return 3.5 * v;
}

bool PHSensor::goodForPlant(Plant p) { double ph = getPH(); return ph >= p.minPH && ph <= p.maxPH; }

char *PHSensor::getFriendlyReading(char *buffer) {
	dtostrf(getPH(), 4, 1, buffer);
	return buffer;
}
