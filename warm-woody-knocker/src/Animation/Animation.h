#ifndef Animation_h
#define Animation_h
#include <Arduino.h>


class LiquidCrystal;


class Animation {
	public:
		Animation(LiquidCrystal *lcd, int left, int top, int width, int height);
		void step();
		
	private:
		LiquidCrystal *lcd;
		int currentState;

		int left;
		int top;
		int width;
		int height;

		void printState(int state);
};

#endif
