#include "Parameter.h"


Parameter::Parameter(String *title) {
	this->title = title;
}

String *Parameter::getTitle() {
	return title;
}
