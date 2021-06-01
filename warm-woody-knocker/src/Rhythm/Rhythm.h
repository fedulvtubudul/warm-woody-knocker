#ifndef Rhythm_h
#define Rhythm_h

#include "Arduino.h"


class Parameter;
class Player;
class Feature;


class Rhythm {
	
public:

	virtual String title() = 0;
	virtual void resetState() = 0;
	virtual void check(unsigned long now);
	
	int getFeaturesCount();
	Feature *getFeature(int index);

	Rhythm(Player *player);
	virtual ~Rhythm();

protected:
	int featuresCount;
	Feature **features;
	Player *player;
};


#endif
