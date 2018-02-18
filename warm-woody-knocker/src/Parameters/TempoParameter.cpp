#include "TempoParameter.h"
#include "../Time/TimeConversion.h"


TempoParameter::TempoParameter(void (*onChange)(TempoParameter *sender)) : 
	IntegerParameter(new String("TEMPO"), onChange, 15, 300, 60) {

}

void TempoParameter::notify() {
	this->beatDuration = beatDurationFromBPM(this->value);

	IntegerParameter::notify();
}

TempoParameter::~TempoParameter() {
	
}
