#ifndef Sound_h
#define Sound_h

#include "Arduino.h"


class RelativeParameter;


enum class SoundLevel {
	no,
	low,
	high
};


class SoundTrack {

public:

	SoundTrack(uint8_t channelPin, unsigned long refClickDuration, RelativeParameter *volumeParameter);

	void check(unsigned long now);
	void play(SoundLevel level);

private:

	uint8_t channelPin;
	SoundLevel shouldStart;
	unsigned long shouldStop;
	unsigned long refClickDuration;
	RelativeParameter *volume;
};

#endif
