#ifndef LinearRhythm_h
#define LinearRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class TempoParameter;
class IntegerParameter;
class EnumParameter;
class Player;


class LinearRhythm: public Rhythm {

public:

	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	LinearRhythm(Player *player, TempoParameter *tempoParameter);
	virtual ~LinearRhythm();

private:

	void setupParameters(TempoParameter *tempoParameter);
	IntegerParameter *makeMeasureLengthParameter();
	EnumParameter *LinearRhythm::makeDivisionParameter();

	TempoParameter *tempo;
	unsigned long measureStart;

};

#endif
