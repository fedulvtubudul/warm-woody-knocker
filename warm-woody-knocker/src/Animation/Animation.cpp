#include "Animation.h"

#include <LiquidCrystal.h>


Animation::Animation(LiquidCrystal *lcd, int screenLine, int screenWidth):
	lcd(lcd),
	currentState(0),
	screenLine(screenLine),
	screenWidth(screenWidth) {

	printState(currentState);
}

void Animation::check(unsigned long now) {
	unsigned long timeSinceBeatStart = now - beatStart;
	if (timeSinceBeatStart >= beatDuration) {
		beatStart = now;
		currentState = (currentState + 1) % 2;
		printState(currentState);
	}
}

void Animation::setTempo(unsigned long beatDuration) {
	this->beatDuration = beatDuration;
}

void Animation::printState(int state) {
	lcd->setCursor(0, screenLine);
	switch (state) {
		case 0:
			printFilledHalf();
			printBlankHalf();
		case 1:
			printBlankHalf();
			printFilledHalf();
	}
}

void Animation::printBlankHalf() {
	for (int i = 0; i < screenWidth / 2; ++i) {
		lcd->print((char)32);
	}
}

void Animation::printFilledHalf() {
	for (int i = 0; i < screenWidth / 2; ++i) {
		lcd->print((char)255);
	}
}