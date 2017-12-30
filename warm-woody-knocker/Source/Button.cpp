#include "Arduino.h"
#include "Button.h"


Button::Button(uint8_t pin, uint32_t clickThreshold, void (*clickHandler)(void),
 	uint32_t holdThreshold, void (*holdHandler)(void)) {
	
	this->pin = pin;
	this->clickThreshold = clickThreshold;
	this->clickHandler = clickHandler;
	this->holdThreshold = holdThreshold;
	this->holdHandler = holdHandler;
	this->state = buttonStateNotPressed;
	this->buttonPressedLoops = 0;
	
	pinMode(pin, INPUT_PULLUP);
}

void Button::check() {
	boolean buttonPressed = !digitalRead(pin);
	
	if (buttonPressed) {
		checkPressed();
	} else {
		checkReleased();
	}
}

void Button::checkPressed() {
	switch (state) {
		case buttonStateNotPressed: {
			state = buttonStateStartPressing;
			buttonPressedLoops = 0;
			break;
		}
			
		case buttonStateStartPressing: {
			if (buttonPressedLoops >= clickThreshold) {
				state = buttonStatePressed;
			}
			buttonPressedLoops += 1;
			break;
		}
			
		case buttonStatePressed: {
			if (buttonPressedLoops >= holdThreshold) {
				state = buttonStateHeld;
				held();
			}
			buttonPressedLoops += 1;
			break;
		}
			
		case buttonStateHeld: {
			break;
		}
	}
}

void Button::checkReleased() {
	switch (state) {
		case buttonStatePressed: {
			clicked();
			break;
		}
		case buttonStateNotPressed:
		case buttonStateStartPressing:
		case buttonStateHeld: {
			break;
		}
	}

	buttonPressedLoops = 0;
	state = buttonStateNotPressed;
}

void Button::clicked() {
	if (clickHandler != NULL) {
		(*clickHandler)();
	}
}

void Button::held() {
	if (holdHandler != NULL) {
		(*holdHandler)();
	}
}
