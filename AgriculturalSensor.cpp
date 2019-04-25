#include <Arduino.h>
#include <SPI.h>
#include "screen.h"
#include "sensors.h"
#include "plants.h"

#define UPDATE_ENABLE_PIN 22
#define SENSOR_COUNT 7

char stringBuffer[256];
Sensor *sensors[SENSOR_COUNT] = { new Sensor(), new DHTTempSensor(2), new DHTHumidSensor(2), new LightSensor(0), new SMSensor(1), new RainSensor(2), new PHSensor(3) };

int setupSensors() {
	Serial.print("Setting up sensors");
	for (int i = 0; i < SENSOR_COUNT; i++) {
		Serial.print(".");
		if (!sensors[i]->setup()) {
			return 0;
			Serial.println(String("ERROR SETTING UP SENSOR: ") + sensors[i]->getName(stringBuffer));
		}
	}
	Serial.println("Set up sensors!");
	return 1;
}

void updateSensors() {
	for (int i = 0; i < SENSOR_COUNT; i++) {
		sensors[i]->update();
		Serial.println(String(sensors[i]->getName(stringBuffer)) + String(itoa(sensors[i]->getRaw(), stringBuffer, 10)));
	}
}

void drawSensorReadings() {
	Serial.print("Drawing sensor readings");

	screenTextMode();

	for (int i = 0; i < SENSOR_COUNT; i++) {
		Serial.print(".");
		sensors[i]->getName(stringBuffer);

		screenSetCursor((int)(500-8*strlen(stringBuffer)), (i + 1) * 15);
		screenPrintln(stringBuffer);
	}

	for (int i = 0; i < SENSOR_COUNT; i++) {
		Serial.print(".");
		sensors[i]->getFriendlyReading(stringBuffer);

		screenSetCursor(650, (i + 1) * 15);
		screenPrintln(stringBuffer);
	}
	Serial.println(" Done!");
}

int getPlantSensorMatches(Plant p) {
	int matches = 0;

	for (int i = 0; i < SENSOR_COUNT; i++)
		if (sensors[i]->goodForPlant(p))
			matches++;

	return matches;
}

void drawPlants() {

	Serial.print("Drawing plants");

	screenTextMode();

	for (int i = 0; i < PLANT_COUNT; i++) {
		Serial.print(".");
		Plant p = getPlant(i);

		int matches = getPlantSensorMatches(p);

		strcpy_P(stringBuffer, plants[i].plantName);

		screenSetCursor(10, (i + 1) * 15);
		screenPrintln(stringBuffer);

		itoa(matches, stringBuffer, 10);
		screenSetCursor(210, (i + 1) * 15);
		screenPrintln(stringBuffer);
	}

	Serial.println(" Done!");
}

void clearSensorReadings() {
	screenGraphicsMode();
	screenDrawRect(500, 15, 800, 465, RA8875_BLACK);
}

void setupScreen() {
	Serial.println("Setting up screen...");
	int screenStatus = screenSetup();

	if (!screenStatus) {
		Serial.println("Failed to initialize screen.");
		while (1) {}
	}

	Serial.println("Set up screen!");
}

void setup() {
	Serial.begin(115200);

	pinMode(UPDATE_ENABLE_PIN, INPUT);

	setupScreen();
	setupSensors();
	updateSensors();
	drawSensorReadings();
	drawPlants();
}

void loop() {
	delay(1000);
	if (digitalRead(UPDATE_ENABLE_PIN)) {
		updateSensors();
		clearSensorReadings();
		drawSensorReadings();
	}
}
