#ifndef PatternRhythm_h
#define PatternRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class TempoParameter;
class EnumParameter;
class Player;
struct Pattern;


class PatternRhythm: public Rhythm {

public:
		
	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	PatternRhythm(Player *player, TempoParameter *tempoParameter);
	virtual ~PatternRhythm();

private:

	TempoParameter *tempo;

	void setupPatterns();
	void setupParameters(TempoParameter *tempoParameter);
	EnumParameter *makePatternParameter();

	unsigned long measureStart;

	int16_t patternsCount;
	Pattern *patterns;

};


#endif
