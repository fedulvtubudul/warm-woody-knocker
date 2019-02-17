#include "RelativeParameter.h"


RelativeParameter::RelativeParameter(String *title, int steps, int initialStep, void (*onChange)(RelativeParameter *sender)) : 
	IntegerParameter(title, 0, steps, initialStep, onChange) {

	relativeValue = (float)(value - minValue) / (float)(maxValue - minValue);
}

void RelativeParameter::notify() {
	relativeValue = (float)(value - minValue) / (float)(maxValue - minValue);

	IntegerParameter::notify();
}

RelativeParameter::~RelativeParameter() {
	
}
