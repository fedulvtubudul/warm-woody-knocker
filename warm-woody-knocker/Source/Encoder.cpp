#include "Encoder.h"
#include <Arduino.h>


Encoder::Encoder(uint8_t pinA, uint8_t pinB, uint32_t debounceThreshold, void (*spinHandler)(SpinDirection direction)) {
	this->pinA = pinA;
	this->pinB = pinB;
	this->debounceThreshold = debounceThreshold;
	this->spinHandler = spinHandler;
	
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);
	
	this->switchToState(this->readState());
}

void Encoder::check() {
	EncoderState newState = readState();
	
	if (newState == knownState) {
		debounced = debounced || (millis() - knownStateStarted >= debounceThreshold);
	} else {
		if (debounced) {
			handleSwitchingToState(newState);
		}
		switchToState(newState);
	}
}

void Encoder::handleSwitchingToState(EncoderState state) {
	switch (state) {
		case encoderState_0: {
			if (knownState == encoderState_1) {
				spinned(spinDirectionCCW);
			} else if (knownState == encoderState_2) {
				spinned(spinDirectionCW);
			}
			
    		break;
		}
		case encoderState_3: {
			if (knownState == encoderState_1) {
				spinned(spinDirectionCW);
			} else if (knownState == encoderState_2) {
				spinned(spinDirectionCCW);
			}
			
    		break;
		}
		case encoderState_1:
		case encoderState_2: {
    		break;
		}
	}
}

void Encoder::switchToState(EncoderState state) {
	knownState = state;
	knownStateStarted = millis();
	debounced = false;
}

EncoderState Encoder::readState() {
	boolean pinAState = !digitalRead(pinA);
	boolean pinBState = !digitalRead(pinB);
	
	int state = 0;
	state += pinAState ? 0b01 : 0;
	state += pinBState ? 0b10 : 0;

	return state;
}

void Encoder::spinned(SpinDirection direction) {
	if (spinHandler != NULL) {
		(*spinHandler)(direction);
	}
}
