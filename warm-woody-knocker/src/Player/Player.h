#ifndef Player_h
#define Player_h

#include "Arduino.h"
#include "SoundTrack.h"


class RelativeParameter;


enum SoundChannel {
	soundLow = 0,
	soundHigh = 1,

	soundChannelsCount
};


class Player {

public:

	Player(RelativeParameter *volumeParameter);
	virtual ~Player();

	void play(SoundChannel sound, SoundLevel level);

private:

	SoundTrack **tracks;

};

#endif
