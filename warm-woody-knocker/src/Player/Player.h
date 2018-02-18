#ifndef Player_h
#define Player_h

#include "Arduino.h"


enum class Sound {
	low,
	high
};


enum class SoundLevel {
	low,
	high
};


class Player {

public:

	Player();
	virtual ~Player();

	virtual void check(unsigned long now);
	virtual void play(Sound sound, SoundLevel level);

};

#endif
