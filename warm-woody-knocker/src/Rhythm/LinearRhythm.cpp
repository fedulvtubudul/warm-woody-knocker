#include "LinearRhythm.h"

#include "../Parameters/Feature.h"
#include "../Parameters/TapTempoFeature.h"
#include "../Parameters/IntegerParameter.h"
#include "../Parameters/TempoParameter.h"
#include "../Parameters/DivisionParameter.h"

#include "../Player/Player.h"
#include "../Animation/Animation.h"
#include "../Storage/StoredParameter.h"


static int const minMeterValue = 0;
static int const maxMeterValue = 16;
static int const defaultMeterValue = 4;


LinearRhythm::LinearRhythm(Storage *storage, Player *player, TempoParameter *tempoParameter,
	TapTempoFeature *tapTempoFeature, Animation *animation):

	Rhythm(player),
	tempo(tempoParameter),
	tapTempo(tapTempoFeature),
	storage(storage),
	animation(animation) {

	this->setupParameters();
	this->resetState();
}

LinearRhythm::~LinearRhythm() {

}

void LinearRhythm::setupParameters() {
	this->meter = makeMeasureLengthParameter();
	this->division = new DivisionParameter(storage, nullptr);

	featuresCount = 4;
	features = new Feature*[this->featuresCount];
	features[0] = meter;
	features[1] = division;
	features[2] = tempo;
	features[3] = tapTempo;
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
			maxMeterValue
		);

	return parameter;
}
