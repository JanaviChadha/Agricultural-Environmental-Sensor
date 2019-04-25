#include "screen.h"

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

int screenSetup() {

	if (!tft.begin(RA8875_800x480))
		return 0;

	tft.displayOn(true);
	tft.GPIOX(true);
	tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
	tft.PWM1out(255);
	tft.fillScreen(RA8875_BLACK);

	return 1;
}

void screenTextMode() {
	tft.textMode();
	tft.textTransparent(RA8875_WHITE);
}

void screenGraphicsMode() {
	tft.graphicsMode();
}

void screenSetCursor(int x, int y) {
	tft.textSetCursor(x, y);
}

void screenPrintln(char *line) {
	tft.textWrite(line);
}

void screenDrawRect(int x, int y, int mx, int my, int color) {
	tft.fillRect(x, y, (mx-x), (my-y), color);
}

