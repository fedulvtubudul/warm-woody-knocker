#include "IntegerParameter.h"
#include "../Storage/Storage.h"


IntegerParameter::~IntegerParameter() {
	
}

IntegerParameter::IntegerParameter(String *title, Storage *storage, StoredParameter parameter, int minValue, int maxValue, void (*onChange)(IntegerParameter *sender) = nullptr) :
	Parameter(title, storage, parameter, onChange),
	minValue(minValue),
	maxValue(maxValue) {

	int storedValue = 0;
	storage->getValue<int>(parameter, storedValue);
	storedValue = min(storedValue, maxValue);
	storedValue = max(storedValue, minValue);
	value = storedValue;
}

void IntegerParameter::stepBy(int stepValue) {
	value += stepValue;
	value = value > minValue ? value : minValue;
	value = value < maxValue ? value : maxValue;

	storage->setValue(storedParameter, value);

	notify();
}

int IntegerParameter::getValue() {
	return value;
}

String IntegerParameter::printableValue() {
	return String(value);
}
