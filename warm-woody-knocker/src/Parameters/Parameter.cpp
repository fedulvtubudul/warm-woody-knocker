#include "Parameter.h"


Parameter::Parameter(String *title, Storage *storage, StoredParameter parameter, void (*onChange)(Parameter *sender)) {
	this->title = title;
	this->storage = storage;
	this->storedParameter = parameter;
	this->onChange = onChange;
}


Parameter::~Parameter() {
	
}


String *Parameter::getTitle() {
	return title;
}


void Parameter::notify() {
	if (this->onChange) {
		this->onChange(this);
	}
}