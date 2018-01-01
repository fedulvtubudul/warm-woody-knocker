#ifndef PatternRhythm_h
#define PatternRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class PatternRhythm: public Rhythm {

public:
	
	virtual String title();

	uint16_t patternLength;
	uint8_t *patternValues;

	virtual ~PatternRhythm();

};


#endif
