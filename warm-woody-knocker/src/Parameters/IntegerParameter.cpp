#include "IntegerParameter.h"


IntegerParameter::~IntegerParameter() {
	
}

IntegerParameter::IntegerParameter(String *title, void (*onChange)(void), int minValue, int maxValue, int initialValue) :
	Parameter(title, onChange),
	minValue(minValue),
	maxValue(maxValue),
	value(initialValue) {
		
}


void IntegerParameter::stepBy(int stepValue) {
	value += stepValue;
	value = value > minValue ? value : minValue;
	value = value < maxValue ? value : maxValue;

	notify();
}


String IntegerParameter::printableValue() {
	return String(value);
}
