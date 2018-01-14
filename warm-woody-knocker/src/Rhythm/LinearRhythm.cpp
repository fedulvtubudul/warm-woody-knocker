#include "LinearRhythm.h"
#include "../Parameters/TempoParameter.h"

#define BPM_TO_MICRO 60000000lu


LinearRhythm::LinearRhythm(TempoParameter *tempoParameter) {
	this->setupParameters(tempoParameter);
	this->resetState();
}


LinearRhythm::~LinearRhythm() {

}

void LinearRhythm::setupParameters(TempoParameter *tempoParameter) {
	this->parametersCount = 1;
	this->parameters = new Parameter*[this->parametersCount];
	
	this->parameters[0] = tempoParameter;
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
