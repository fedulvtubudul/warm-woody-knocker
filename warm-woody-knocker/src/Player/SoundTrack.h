#ifndef Sound_h
#define Sound_h

#include "Arduino.h"


enum class SoundLevel {
	no,
	low,
	high
};


class SoundTrack {

public:

	SoundTrack(uint8_t channelPin);

	void check(unsigned long now);
	void play(SoundLevel level);

private:

	uint8_t channelPin;
	SoundLevel shouldStart;
	unsigned long shouldStop;

};

#endif
