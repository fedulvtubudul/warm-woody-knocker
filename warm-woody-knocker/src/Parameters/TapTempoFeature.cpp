#include "TapTempoFeature.h"
#include "TempoParameter.h"


TapTempoFeature::TapTempoFeature(TempoParameter *tempoParameter) :
	Feature(new String("TAP TEMPO")),
	tempoParameter(tempoParameter) {
}

String TapTempoFeature::printableValue() {
	return tempoParameter->printableValue();
}

bool TapTempoFeature::canFocus() {
	return false;
}

void TapTempoFeature::tap() {
}

void TapTempoFeature::scroll(int stepValue) {
}

TapTempoFeature::~TapTempoFeature() {	
}
