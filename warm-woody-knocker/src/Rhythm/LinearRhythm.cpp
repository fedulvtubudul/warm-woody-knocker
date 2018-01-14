#include "LinearRhythm.h"

#define BPM_TO_MICRO 60000000lu


LinearRhythm::LinearRhythm() {
	this->setupParameters();
}


LinearRhythm::~LinearRhythm() {

}


void LinearRhythm::setupParameters() {
	parametersCount = 3;
}


String LinearRhythm::title() {
	return String("Linear");
}


bool ledState = LOW;

void LinearRhythm::resetState() {
	this->tempo = 120;
	this->beatDuration = BPM_TO_MICRO / tempo;
	this->measureStart = 0;

	digitalWrite(LED_BUILTIN, LOW);
}


void LinearRhythm::check(unsigned long now) {
	unsigned long timeSinceMeasureStart = now - this->measureStart;

	if (timeSinceMeasureStart >= this->beatDuration) {
		ledState = !ledState;
		digitalWrite(LED_BUILTIN, ledState);
		this->measureStart = now;
	}
	
}
