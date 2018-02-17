#include "LinearRhythm.h"
#include "../Parameters/TempoParameter.h"



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
	this->tempo = tempoParameter;
}


String LinearRhythm::title() {
	return String("Linear");
}


bool ledState = LOW;

void LinearRhythm::resetState() {
	this->measureStart = 0;

	digitalWrite(LED_BUILTIN, LOW);
}


void LinearRhythm::check(unsigned long now) {
	unsigned long timeSinceMeasureStart = now - this->measureStart;

	if (timeSinceMeasureStart >= this->tempo->beatDuration) {
		ledState = !ledState;
		digitalWrite(LED_BUILTIN, ledState);
		this->measureStart = now;
	}
	
}
