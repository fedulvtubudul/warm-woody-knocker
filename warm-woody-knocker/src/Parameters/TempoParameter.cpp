#include "TempoParameter.h"


TempoParameter::TempoParameter(void (*onChange)(TempoParameter *sender)) : 
	IntegerParameter(new String("TEMPO"), onChange, 15, 300, 60) {

}


TempoParameter::~TempoParameter() {
	
}
