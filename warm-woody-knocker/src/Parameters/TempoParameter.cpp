#include "TempoParameter.h"
#include "../Time/TimeConversion.h"


TempoParameter::TempoParameter(void (*onChange)(TempoParameter *sender)) : 
	IntegerParameter(new String("TEMPO"), 15, 300, 90, onChange) {
	
	this->beatDuration = beatDurationFromBPM(this->value);
}

void TempoParameter::notify() {
	this->beatDuration = beatDurationFromBPM(this->value);

	IntegerParameter::notify();
}

TempoParameter::~TempoParameter() {
	
}
