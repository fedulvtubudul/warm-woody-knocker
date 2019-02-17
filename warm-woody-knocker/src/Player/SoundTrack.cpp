#include "SoundTrack.h"
#include "../Parameters/RelativeParameter.h"


SoundTrack::SoundTrack(uint8_t channelPin, unsigned long refClickDuration, RelativeParameter *volumeParameter):
	channelPin(channelPin),
	refClickDuration(refClickDuration),
	volume(volumeParameter),
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
		shouldStop = now + refClickDuration * volume->relativeValue;
	} else if (shouldStart == SoundLevel::high) {
		digitalWrite(channelPin, HIGH);
		shouldStart = SoundLevel::no;
		shouldStop = now + refClickDuration * 0.75f * volume->relativeValue;
	}

	if (now >= shouldStop) {
		shouldStop = -1;
		digitalWrite(channelPin, LOW);
	}
}
