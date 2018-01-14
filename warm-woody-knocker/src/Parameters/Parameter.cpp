#include "Parameter.h"


Parameter::Parameter(String *title, void (*onChange)(void)) {
	this->title = title;
	this->onChange = onChange;
}


Parameter::~Parameter() {
	
}


String *Parameter::getTitle() {
	return title;
}


void Parameter::notify() {
	if (this->onChange) {
		this->onChange();
	}
}