#include "SoundTrack.h"
#include "../Parameters/RelativeParameter.h"


SoundTrack::SoundTrack(uint8_t channelPin, float refClickDuration, RelativeParameter *volumeParameter):
	channelPin(channelPin),
	refClickDuration(refClickDuration),
	volume(volumeParameter) {

	pinMode(channelPin, OUTPUT);
}

void SoundTrack::play(SoundLevel level) {
	if (level == SoundLevel::no) {
		return;
	}

	digitalWrite(channelPin, HIGH);

	if (level == SoundLevel::low) {
		delayMicroseconds(refClickDuration * 0.75f * volume->relativeValue);
	}
		
	if (level == SoundLevel::high) {
		delayMicroseconds(refClickDuration * volume->relativeValue);
	}

	digitalWrite(channelPin, LOW);
}
