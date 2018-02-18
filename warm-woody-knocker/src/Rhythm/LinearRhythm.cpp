#include "LinearRhythm.h"
#include "../Parameters/IntegerParameter.h"
#include "../Parameters/TempoParameter.h"
#include "../Parameters/DivisionParameter.h"


static int const minMeterValue = 0;
static int const maxMeterValue = 16;
static int const defaultMeterValue = 4;

static int const divisionsCount = 3;


LinearRhythm::LinearRhythm(TempoParameter *tempoParameter) {
	this->setupParameters(tempoParameter);
	this->resetState();
}


LinearRhythm::~LinearRhythm() {

}

void LinearRhythm::setupParameters(TempoParameter *tempoParameter) {
	this->tempo = tempoParameter;

	this->parametersCount = 3;
	this->parameters = new Parameter*[this->parametersCount];
	this->parameters[0] = makeMeasureLengthParameter();
	this->parameters[1] = new DivisionParameter(nullptr);
	this->parameters[2] = tempoParameter;
}


String LinearRhythm::title() {
	return String("Linear");
}


bool ledState = LOW;

void LinearRhythm::resetState() {
	this->measureStart = 0;

	digitalWrite(LED_BUILTIN, LOW);
}

void LinearRhythm::check(unsigned long now) {
	unsigned long timeSinceMeasureStart = now - this->measureStart;

	if (timeSinceMeasureStart >= this->tempo->beatDuration) {
		ledState = !ledState;
		digitalWrite(LED_BUILTIN, ledState);
		this->measureStart = now;
	}
	
}

IntegerParameter *LinearRhythm::makeMeasureLengthParameter() {
	IntegerParameter *parameter = new IntegerParameter(
			new String("METER"),
			nullptr,
			minMeterValue,
			maxMeterValue,
			defaultMeterValue
		);

	return parameter;
}
