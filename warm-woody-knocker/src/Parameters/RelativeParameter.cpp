#include "RelativeParameter.h"


RelativeParameter::RelativeParameter(String *title, Storage *storage, StoredParameter parameter, int steps, void (*onChange)(RelativeParameter *sender)) : 
	IntegerParameter(title, storage, parameter, 0, steps, onChange) {

	relativeValue = (float)(value - minValue) / (float)(maxValue - minValue);
}

void RelativeParameter::notify() {
	relativeValue = (float)(value - minValue) / (float)(maxValue - minValue);

	IntegerParameter::notify();
}

RelativeParameter::~RelativeParameter() {
	
}
