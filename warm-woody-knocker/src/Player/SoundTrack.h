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

	SoundTrack(uint8_t channelPin, float refClickDuration, RelativeParameter *volumeParameter);

	void play(SoundLevel level);

private:

	uint8_t channelPin;
	float refClickDuration;
	RelativeParameter *volume;
};

#endif
