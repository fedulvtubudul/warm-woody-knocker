#include "Feature.h"


Feature::Feature(String *title) :
	title(title) {
}

Feature::~Feature() {	
}

String *Feature::getTitle() {
	return title;
}
