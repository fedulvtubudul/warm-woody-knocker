#include "PatternRhythm.h"


String PatternRhythm::title() {
	return String("Pattern");
}


PatternRhythm::~PatternRhythm() {

}


void PatternRhythm::resetState() {
	digitalWrite(LED_BUILTIN, LOW);
}

void PatternRhythm::check(unsigned long now) {

}
