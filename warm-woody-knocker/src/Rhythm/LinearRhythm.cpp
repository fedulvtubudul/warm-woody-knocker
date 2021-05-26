#include "LinearRhythm.h"

#include "../Parameters/IntegerParameter.h"
#include "../Parameters/TempoParameter.h"
#include "../Parameters/DivisionParameter.h"

#include "../Player/Player.h"
#include "../Animation/Animation.h"
#include "../Storage/StoredParameter.h"


static int const minMeterValue = 0;
static int const maxMeterValue = 16;
static int const defaultMeterValue = 4;


LinearRhythm::LinearRhythm(Storage *storage, Player *player, TempoParameter *tempoParameter, Animation *animation):
	storage(storage),
	Rhythm(player),
	animation(animation) {

	this->setupParameters(tempoParameter);
	this->resetState();
}

LinearRhythm::~LinearRhythm() {

}

void LinearRhythm::setupParameters(TempoParameter *tempoParameter) {
	this->tempo = tempoParameter;
	this->meter = makeMeasureLengthParameter();
	this->division = new DivisionParameter(nullptr);

	this->parametersCount = 3;
	this->parameters = new Parameter*[this->parametersCount];
	this->parameters[0] = meter;
	this->parameters[1] = division;
	this->parameters[2] = tempoParameter;
}

String LinearRhythm::title() {
	return String("Linear");
}

void LinearRhythm::resetState() {
	this->measureStart = 0;
	this->beatStart = 0;
	this->subBeatStart = 0;
}

void LinearRhythm::check(unsigned long now) {
	unsigned long timeSinceMeasureStart = now - measureStart;
	unsigned long timeSinceBeatStart = now - beatStart;
	unsigned long timeSinceSubBeatStart = now - subBeatStart;

	unsigned long beatDuration = tempo->beatDuration;
	unsigned long beatCount = meter->getValue();
	bool zeroBeat = beatCount == 0;
	beatCount = zeroBeat ? 1 : beatCount;
	unsigned long measureDuration = beatDuration * beatCount;

	if (timeSinceBeatStart >= beatDuration) {
		if (timeSinceMeasureStart >= measureDuration) {
			measureStart = now;
			if (zeroBeat) {
				player->play(soundLow, SoundLevel::high);
			} else {
				player->play(soundHigh, SoundLevel::high);
			}
		} else {
			player->play(soundLow, SoundLevel::high);
		}
		beatStart = now;
		subBeatStart = now;
		animation->step();
	} else if (timeSinceSubBeatStart >= division->subBeatDuration(beatDuration)) {
		subBeatStart = now;
		player->play(soundLow, SoundLevel::low);
	}
}

IntegerParameter *LinearRhythm::makeMeasureLengthParameter() {
	IntegerParameter *parameter = new IntegerParameter(
			new String("METER"),
			storage,
			storedParameterMeter,
			minMeterValue,
			maxMeterValue,
			defaultMeterValue
		);

	return parameter;
}
