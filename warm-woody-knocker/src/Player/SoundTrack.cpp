#include "SoundTrack.h"

SoundTrack::SoundTrack(uint8_t channelPin):
	channelPin(channelPin),
	shouldStart(SoundLevel::no),
	shouldStop(0) {

	pinMode(channelPin, OUTPUT);
}

void SoundTrack::play(SoundLevel level) {
	shouldStart = level;
}

void SoundTrack::check(unsigned long now) {
	if (shouldStart == SoundLevel::low) {
		digitalWrite(channelPin, HIGH);
		shouldStart = SoundLevel::no;
		shouldStop = now + 2000;
	} else if (shouldStart == SoundLevel::high) {
		digitalWrite(channelPin, HIGH);
		shouldStart = SoundLevel::no;
		shouldStop = now + 1200;
	}

	if (now >= shouldStop) {
		shouldStop = -1;
		digitalWrite(channelPin, LOW);
	}
}
