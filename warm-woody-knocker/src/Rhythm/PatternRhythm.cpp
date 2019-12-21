#include "PatternRhythm.h"

#include "../Parameters/TempoParameter.h"


PatternRhythm::PatternRhythm(Player *player, TempoParameter *tempoParameter):
	Rhythm(player) {

	this->setupParameters(tempoParameter);
	this->resetState();
}

PatternRhythm::~PatternRhythm() {

}


void PatternRhythm::setupParameters(TempoParameter *tempoParameter) {
	this->tempo = tempoParameter;

	this->parametersCount = 1;
	this->parameters = new Parameter*[this->parametersCount];
	this->parameters[0] = tempoParameter;
}


String PatternRhythm::title() {
	return String("Pattern");
}

void PatternRhythm::resetState() {
	digitalWrite(LED_BUILTIN, LOW);
}

void PatternRhythm::check(unsigned long now) {

}
