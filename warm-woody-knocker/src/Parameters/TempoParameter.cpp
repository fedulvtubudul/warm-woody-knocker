#include "TempoParameter.h"
#include "../Time/TimeConversion.h"
#include "../Display/CustomCharacters.h"
#include "../Storage/Storage.h"


TempoParameter::TempoParameter(Storage *storage, void (*onChange)(TempoParameter *sender)) :
	minTempo(15),
	maxTempo(300),
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

void TempoParameter::setTempoWithBeatDuration(unsigned long beatDuration) {
	int tempo = bpmTempoFromBeatDuration(beatDuration);
	if (tempo >= minTempo && tempo <= maxTempo) {
		value = tempo;
		notify();
	}
}

TempoParameter::~TempoParameter() {	
}