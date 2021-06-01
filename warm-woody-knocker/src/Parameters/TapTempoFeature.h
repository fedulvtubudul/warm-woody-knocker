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

private:
	TempoParameter *tempoParameter;
};

#endif
