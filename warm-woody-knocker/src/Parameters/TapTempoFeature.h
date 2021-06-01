#ifndef TapTempoParameter_h
#define TapTempoParameter_h

#include "Arduino.h"
#include "Feature.h"


class TempoParameter;


class TapTempoFeature : public Feature {
public:
	TapTempoFeature(TempoParameter *tempoParameter);
	virtual ~TapTempoFeature();

	virtual String printableValue();
	virtual bool canFocus();
	virtual void tap();
	virtual void scroll(int stepValue);

private:
	TempoParameter *tempoParameter;
};

#endif
