#include "Rhythm.h"
#include "../Parameters/Parameter.h"


Rhythm::~Rhythm() {

}

int Rhythm::getParametersCount(void) {
	return this->parametersCount;
}

Parameter * Rhythm::getParameter(int parameterIndex) {
	return parameters[parameterIndex];
}
