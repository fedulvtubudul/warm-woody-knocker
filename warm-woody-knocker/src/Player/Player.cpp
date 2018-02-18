#include "Player.h"

#define LOW_CHANNEL_PIN 8
#define HIGH_CHANNEL_PIN 9


Player::Player() {
	tracks = new SoundTrack*[soundChannelsCount];

	tracks[soundLow] = new SoundTrack(LOW_CHANNEL_PIN);
	tracks[soundHigh] = new SoundTrack(HIGH_CHANNEL_PIN);
}

Player::~Player() {

}

void Player::check(unsigned long now) {
	for (int i = 0; i < soundChannelsCount; ++i) {
		tracks[i]->check(now);
	}
}

void Player::play(SoundChannel sound, SoundLevel level) {
	tracks[sound]->play(level);
}
