#ifndef Button_hpp
#define Button_hpp
#include <Arduino.h>


typedef enum {
	buttonStateNotPressed,
	buttonStateStartPressing,
	buttonStatePressed,
	buttonStateHeld
} ButtonState;


class Button {

public:

	Button(uint8_t pin, uint32_t clickThreshold, void (*clickHandler)(void),
		uint32_t holdThreshold, void (*holdHandler)(void));
	
	void check();
	
private:

	uint8_t pin;
	
	uint32_t clickThreshold;
	void (*clickHandler)(void);
	
	uint32_t holdThreshold;
	void (*holdHandler)(void);
	
	ButtonState state;
	uint32_t pressStarted;

	void checkPressed();
	void checkReleased();
	void clicked();
	void held();

};

#endif
