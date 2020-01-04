#ifndef LinearRhythm_h
#define LinearRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class TempoParameter;
class DivisionParameter;
class IntegerParameter;
class EnumParameter;
class Player;
class Animation;


class LinearRhythm: public Rhythm {

public:

	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	LinearRhythm(Player *player, TempoParameter *tempoParameter, Animation *animation);
	virtual ~LinearRhythm();

private:

	void setupParameters(TempoParameter *tempoParameter);
	IntegerParameter *makeMeasureLengthParameter();

	TempoParameter *tempo;
	IntegerParameter *meter;
	DivisionParameter *division;
	Animation *animation;

	unsigned long measureStart;
	unsigned long beatStart;
	unsigned long subBeatStart;

};

#endif
