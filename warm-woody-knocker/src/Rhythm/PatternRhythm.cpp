#include "PatternRhythm.h"


PatternRhythm::PatternRhythm(Player *player):
	Rhythm(player) {

	this->setupParameters();
	this->resetState();
}

PatternRhythm::~PatternRhythm() {

}


void PatternRhythm::setupParameters() {
	parametersCount = 0;
}


String PatternRhythm::title() {
	return String("Pattern");
}

void PatternRhythm::resetState() {
	digitalWrite(LED_BUILTIN, LOW);
}

void PatternRhythm::check(unsigned long now) {

}
