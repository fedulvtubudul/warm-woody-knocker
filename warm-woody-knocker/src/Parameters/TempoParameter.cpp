#include "TempoParameter.h"


TempoParameter::TempoParameter(void (*onChange)(void)) : 
	IntegerParameter(new String("TEMPO"), onChange, 15, 300, 60) {
	
}


TempoParameter::~TempoParameter() {
	
}
