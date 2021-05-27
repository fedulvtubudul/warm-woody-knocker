#include "Animation.h"

#include <LiquidCrystal.h>


Animation::Animation(LiquidCrystal *lcd, int left, int top, int width, int height):
	lcd(lcd),
	currentState(0),
	left(left),
	top(top),
	width(width),
	height(height) {

	printState(currentState);
}

void Animation::step() {
		currentState = (currentState + 1) % 2;
		printState(currentState);
}

void Animation::printState(int state) {
	char fillingChar = state ? 255 : 32;
	for (int line = top; line < top + height; line++) {
		lcd->setCursor(left, line);
		for (int col = 0; col < width; col++) {
				lcd->print(fillingChar);
		}
	}
}
