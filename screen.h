#include "SPI.h"
#include <Adafruit_GFX.h>
#include <Adafruit_RA8875.h>

#ifndef SCREEN_H_
#define SCREEN_H_

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

int screenSetup();

void screenTextMode();

void screenSetCursor(int x, int y);

void screenPrintln(char *line);

void screenGraphicsMode();

void screenDrawRect(int x, int y, int mx, int my, int color);

#endif /* SCREEN_H_ */
