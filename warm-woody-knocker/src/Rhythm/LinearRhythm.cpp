#include "LinearRhythm.h"

#define BPM_TO_MICRO 60000000lu


String LinearRhythm::title() {
	return String("Linear");
}


LinearRhythm::~LinearRhythm() {

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
