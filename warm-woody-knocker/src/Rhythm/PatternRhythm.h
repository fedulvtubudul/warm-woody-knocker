#ifndef PatternRhythm_h
#define PatternRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class TempoParameter;
class Player;


class PatternRhythm: public Rhythm {

public:
		
	uint16_t patternLength;
	uint8_t *patternValues;

	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	PatternRhythm(Player *player, TempoParameter *tempoParameter);
	virtual ~PatternRhythm();

private:

	TempoParameter *tempo;

	void setupParameters(TempoParameter *tempoParameter);

};


#endif
