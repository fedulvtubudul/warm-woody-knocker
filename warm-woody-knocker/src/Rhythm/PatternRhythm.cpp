#include "PatternRhythm.h"

#include "../Parameters/TempoParameter.h"
#include "../Parameters/EnumParameter.h"

#include "../Player/Player.h"


PatternRhythm::PatternRhythm(Player *player, TempoParameter *tempoParameter):
	Rhythm(player) {

	this->setupParameters(tempoParameter);
	this->resetState();
}

PatternRhythm::~PatternRhythm() {

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
	int valuesCount = 2;
	String *values = new String[valuesCount];
	values[0] = String("Clave");
	values[1] = String("Saiidi");

	EnumParameter *parameter = new EnumParameter(
			new String("METER"),
			2,
			values,
			0
		);

	return parameter;
}
