#ifndef Pattern_h
#define Pattern_h

#include "Arduino.h"
#include "../Player/SoundTrack.h"

struct Pattern {
	String title;
	int16_t meter;
	int16_t length;
	SoundLevel *lowChannelValues;
	SoundLevel *highChannelValues;
};

Pattern makeClavePattern();
Pattern makeBembePattern();
Pattern makeSongoPattern();
Pattern makeSaiidiPattern();
Pattern makeSwing3Pattern();
Pattern makeSwing4Pattern();

#endif
