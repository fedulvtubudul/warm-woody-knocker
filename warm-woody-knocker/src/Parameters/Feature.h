#ifndef Feature_h
#define Feature_h

#include "Arduino.h"


class Feature {
public:
	virtual ~Feature();
	Feature(String *title);

	virtual String *getTitle();
	virtual String printableValue() = 0;
	virtual bool canFocus() = 0;
	virtual void tap() = 0;
	virtual void scroll(int stepValue) = 0;

private:
	String *title;
	Feature();
};

#endif
