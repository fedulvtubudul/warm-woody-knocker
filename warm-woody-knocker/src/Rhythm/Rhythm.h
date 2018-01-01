#ifndef Rhythm_h
#define Rhythm_h

#include "Arduino.h"


class RhythmParameter;


class Rhythm {
	
public:

	virtual String title() = 0;
	// virtual RhythmParameter *parameters() = 0;
	virtual ~Rhythm();
	
};


#endif
