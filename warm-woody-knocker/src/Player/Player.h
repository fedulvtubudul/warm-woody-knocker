#ifndef Player_h
#define Player_h

#include "Arduino.h"
#include "SoundTrack.h"


enum SoundChannel {
	soundLow = 0,
	soundHigh = 1,

	soundChannelsCount
};


class Player {

public:

	Player();
	virtual ~Player();

	void check(unsigned long now);
	void play(SoundChannel sound, SoundLevel level);

private:

	SoundTrack **tracks;

};

#endif
