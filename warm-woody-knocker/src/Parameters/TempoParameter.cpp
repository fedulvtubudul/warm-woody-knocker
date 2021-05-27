#include "TempoParameter.h"
#include "../Time/TimeConversion.h"
#include "../Display/CustomCharacters.h"
#include "../Storage/Storage.h"


int minTempo = 15;
int maxTempo = 300;

TempoParameter::TempoParameter(Storage *storage, void (*onChange)(TempoParameter *sender)) : 
	IntegerParameter(new String("TEMPO"), storage, storedParameterTempo, minTempo, maxTempo, onChange) {

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