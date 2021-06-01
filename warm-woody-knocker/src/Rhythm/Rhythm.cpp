#include "Rhythm.h"
#include "../Parameters/Feature.h"
#include "../Parameters/Parameter.h"


Rhythm::Rhythm(Player *player):
	player(player) {

}

Rhythm::~Rhythm() {

}

int Rhythm::getFeaturesCount(void) {
	return featuresCount;
}

Feature * Rhythm::getFeature(int index) {
	return features[index];
}
