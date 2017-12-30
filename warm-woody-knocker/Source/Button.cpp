#include "Button.h"


Button::Button(uint8_t pin, uint32_t clickThreshold, void (*clickHandler)(void),
 	uint32_t holdThreshold, void (*holdHandler)(void)) {
	
	this->pin = pin;
	this->clickThreshold = clickThreshold;
	this->clickHandler = clickHandler;
	this->holdThreshold = holdThreshold;
	this->holdHandler = holdHandler;
	this->state = buttonStateNotPressed;
	
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
	uint32_t now = millis();
	uint32_t pressedTime = now - pressStarted;
	
	switch (state) {
		case buttonStateNotPressed: {
			state = buttonStateStartPressing;
			pressStarted = now;
			break;
		}
			
		case buttonStateStartPressing: {
			if (pressedTime >= clickThreshold) {
				state = buttonStatePressed;
			}
			break;
		}
			
		case buttonStatePressed: {
			if (pressedTime >= holdThreshold) {
				state = buttonStateHeld;
				held();
			}
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
