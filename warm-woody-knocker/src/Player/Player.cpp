#include "Player.h"

#define LOW_CHANNEL_PIN 8
#define HIGH_CHANNEL_PIN 9


Player::Player(RelativeParameter *volumeParameter) {
	tracks = new SoundTrack*[soundChannelsCount];

	tracks[soundLow] = new SoundTrack(LOW_CHANNEL_PIN, 4500, volumeParameter);
	tracks[soundHigh] = new SoundTrack(HIGH_CHANNEL_PIN, 6000, volumeParameter);
}

Player::~Player() {

}

void Player::play(SoundChannel sound, SoundLevel level) {
	tracks[sound]->play(level);
}
