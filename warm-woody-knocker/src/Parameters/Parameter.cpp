#include "Parameter.h"


Parameter::Parameter(String *title, Storage *storage, StoredParameter parameter,
	void (*onChange)(Parameter *sender)):
	
	Feature(title) {

	this->storage = storage;
	this->storedParameter = parameter;
	this->onChange = onChange;
}

Parameter::~Parameter() {	
}

bool Parameter::canFocus() {
	return true;
}

void Parameter::tap() {
}

void Parameter::notify() {
	if (this->onChange) {
		this->onChange(this);
	}
}