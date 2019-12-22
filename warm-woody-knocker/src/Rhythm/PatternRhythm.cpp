#include "PatternRhythm.h"

#include "../Parameters/TempoParameter.h"
#include "../Parameters/EnumParameter.h"

#include "../Player/Player.h"
#include "Pattern.h"


PatternRhythm::PatternRhythm(Player *player, TempoParameter *tempoParameter):
	Rhythm(player) {

	this->setupPatterns();
	this->setupParameters(tempoParameter);
	this->resetState();
}

PatternRhythm::~PatternRhythm() {

}

void PatternRhythm::setupPatterns() {
	this->patternsCount = 2;
	this->patterns = new Pattern[this->patternsCount];
	patterns[0] = makeClavePattern();
	patterns[1] = makeSaiidiPattern();
}



void PatternRhythm::setupParameters(TempoParameter *tempoParameter) {
	this->tempo = tempoParameter;

	this->parametersCount = 2;
	this->parameters = new Parameter*[this->parametersCount];
	this->parameters[0] = this->makePatternParameter();
	this->parameters[1] = tempoParameter;
}


String PatternRhythm::title() {
	return String("Pattern");
}

void PatternRhythm::resetState() {
	this->measureStart = 0;
	digitalWrite(LED_BUILTIN, LOW);
}

void PatternRhythm::check(unsigned long now) {

}

EnumParameter *PatternRhythm::makePatternParameter() {
	String *values = new String[this->patternsCount];
	for (int16_t i = 0; i < this->patternsCount; ++i) {
		values[i] = this->patterns[i].title;
	}

	EnumParameter *parameter = new EnumParameter(
			new String("METER"),
			this->patternsCount,
			values,
			0
		);

	return parameter;
}
