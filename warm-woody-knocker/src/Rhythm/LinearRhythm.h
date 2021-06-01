#ifndef LinearRhythm_h
#define LinearRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class TempoParameter;
class TapTempoFeature;
class DivisionParameter;
class IntegerParameter;
class EnumParameter;
class Player;
class Animation;
class Storage;


class LinearRhythm: public Rhythm {

public:

	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	LinearRhythm(Storage *storage, Player *player, TempoParameter *tempoParameter,
		TapTempoFeature *tapTempoFeature, Animation *animation);

	virtual ~LinearRhythm();

private:

	void setupParameters();
	IntegerParameter *makeMeasureLengthParameter();

	Storage *storage;
	TempoParameter *tempo;
	TapTempoFeature *tapTempo;
	IntegerParameter *meter;
	DivisionParameter *division;
	Animation *animation;

	unsigned long measureStart;
	unsigned long beatStart;
	unsigned long subBeatStart;

};

#endif
