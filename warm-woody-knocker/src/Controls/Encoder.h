#ifndef Encoder_h
#define Encoder_h
#include <Arduino.h>


typedef enum {
	encoderState_0 = 0b00,
	encoderState_1 = 0b01,
	encoderState_2 = 0b10,
	encoderState_3 = 0b11
} EncoderState;


typedef enum {
	spinDirectionCW,
	spinDirectionCCW
} SpinDirection;


class Encoder {

public:

	Encoder(uint8_t pinA, uint8_t pinB, uint32_t debounceThreshold, void (*spinHandler)(SpinDirection direction));
	void check();
	
private:

	uint8_t pinA;
	uint8_t pinB;
	
	uint32_t debounceThreshold;
	void (*spinHandler)(SpinDirection direction);
	
	EncoderState knownState;
	uint32_t knownStateStarted;
	boolean debounced;
	
	EncoderState readState();
	void switchToState(EncoderState state);
	void handleSwitchingToState(EncoderState state);
	void spinned(SpinDirection direction);

};


#endif
