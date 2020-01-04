#include "PatternRhythm.h"

#include "../Parameters/TempoParameter.h"
#include "../Parameters/EnumParameter.h"

#include "../Animation/Animation.h"
#include "../Player/Player.h"
#include "Pattern.h"


PatternRhythm::PatternRhythm(Player *player, TempoParameter *tempoParameter, Animation *animation):
	Rhythm(player),
	animation(animation) {

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

	this->patternParameter = this->makePatternParameter();

	this->parametersCount = 2;
	this->parameters = new Parameter*[this->parametersCount];
	this->parameters[0] = this->patternParameter;
	this->parameters[1] = tempoParameter;
}

String PatternRhythm::title() {
	return String("Pattern");
}

void PatternRhythm::resetState() {
	this->measureStart = 0;
	this->beatStart = 0;
	this->animationBeatStart = 0;
}

void PatternRhythm::check(unsigned long now) {
	unsigned long timeSinceMeasureStart = now - measureStart;
	unsigned long timeSinceBeatStart = now - beatStart;
	unsigned long timeSinceAnimationBeatStart = now - animationBeatStart;

	int patternIndex = this->patternParameter->getRawValue();
	Pattern pattern = this->patterns[patternIndex];

	unsigned long animationBeatDuration = tempo->beatDuration;
	unsigned long beatDuration = tempo->beatDuration * 4 / pattern.meter;
	unsigned long beatCount = pattern.length;
	unsigned long measureDuration = beatDuration * beatCount;

	if (timeSinceMeasureStart >= measureDuration) {
		measureStart = now;
		beatIndex = 0;
	} 
	
	if (timeSinceBeatStart >= beatDuration) {
		beatStart = now;
		player->play(soundLow, pattern.lowChannelValues[beatIndex]);
		player->play(soundHigh, pattern.highChannelValues[beatIndex]);
		++beatIndex;
	}

	if (timeSinceAnimationBeatStart >= animationBeatDuration) {
		animationBeatStart = now;
		animation->step();
	}
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
