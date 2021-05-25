#include "TempoParameter.h"
#include "../Time/TimeConversion.h"
#include "../Display/CustomCharacters.h"


TempoParameter::TempoParameter(void (*onChange)(TempoParameter *sender)) : 
	IntegerParameter(new String("TEMPO"), 15, 300, 90, onChange) {
	
	this->beatDuration = beatDurationFromBPM(this->value);
}

void TempoParameter::notify() {
	this->beatDuration = beatDurationFromBPM(this->value);

	IntegerParameter::notify();
}

String TempoParameter::printableValue() {
	float msValue = 60000.0f / float(value);
	return String(value) + String("/") + String(msValue, 1) + String(millisecondCharacter.stringAlias);
}

TempoParameter::~TempoParameter() {	
}