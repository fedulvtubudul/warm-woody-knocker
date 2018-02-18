#include "Player.h"


#define ONBEAT_OUTPUT 8
#define OFFBEAT_OUTPUT 9


Player::Player() {

}

Player::~Player() {

}

bool shouldStart = false;
unsigned long started = 0;


void Player::check(unsigned long now) {

	if (shouldStart) {
		started = now;
		shouldStart = false;
		digitalWrite(ONBEAT_OUTPUT, HIGH);
	}

	if (now - started > 1000) {
		digitalWrite(ONBEAT_OUTPUT, LOW);
	}
}

void Player::play(Sound sound, SoundLevel level) {
	shouldStart = true;
}
