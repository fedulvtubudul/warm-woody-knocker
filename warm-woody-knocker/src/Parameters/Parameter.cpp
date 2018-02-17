#include "Parameter.h"


Parameter::Parameter(String *title, void (*onChange)(Parameter *sender)) {
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
		this->onChange(this);
	}
}