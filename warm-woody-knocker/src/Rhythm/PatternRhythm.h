#ifndef PatternRhythm_h
#define PatternRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class TempoParameter;
class TapTempoFeature;
class EnumParameter;
class Player;
class Animation;
struct Pattern;
class Storage;


class PatternRhythm: public Rhythm {

public:
		
	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	PatternRhythm(Storage *storage, Player *player, TempoParameter *tempoParameter,
		TapTempoFeature *tapTempoFeature, Animation *animation);

	virtual ~PatternRhythm();

private:

	TempoParameter *tempo;
	TapTempoFeature *tapTempo;

	void setupPatterns();
	void setupParameters();
	EnumParameter *makePatternParameter();

	Storage *storage;
	EnumParameter *patternParameter;
	Animation *animation;

	unsigned long measureStart;
	unsigned long beatStart;
	unsigned long beatIndex;
	unsigned long animationBeatStart;

	int16_t patternsCount;
	Pattern *patterns;
};


#endif
