#ifndef Feature_h
#define Feature_h

#include "Arduino.h"


class Feature {
public:
	virtual ~Feature();
	Feature(String *title);

	virtual String *getTitle();
	virtual String printableValue() = 0;

private:
	String *title;
	Feature();
};

#endif
