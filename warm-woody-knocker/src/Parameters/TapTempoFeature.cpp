#include "TapTempoFeature.h"
#include "TempoParameter.h"
#include "../Time/TimeConversion.h"



TapTempoFeature::TapTempoFeature(TempoParameter *tempoParameter) :
	Feature(new String("TAP TEMPO")),
	tempo(tempoParameter),
	previousTap(0) {
	
	maxPeriod = beatDurationFromBPM(tempo->minTempo);
}

String TapTempoFeature::printableValue() {
	return tempo->printableValue();
}

bool TapTempoFeature::canFocus() {
	return false;
}

void TapTempoFeature::tap() {
	unsigned long now = micros();

	// TODO: set player measure start time to now.

	unsigned long period = now - previousTap;
	if (period <= maxPeriod) {
		tempo->setTempoWithBeatDuration(period);
	}

	previousTap = now;
}

void TapTempoFeature::scroll(int stepValue) {
}

TapTempoFeature::~TapTempoFeature() {	
}
