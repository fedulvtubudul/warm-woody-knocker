#ifndef Parameter_h
#define Parameter_h

#include "Arduino.h"
#include "../Storage/StoredParameter.h"


class Storage;


class Parameter {

public:

	virtual ~Parameter();
	Parameter(String *title, Storage *storage, StoredParameter parameter, void (*onChange)(Parameter *sender) = nullptr);

	String *getTitle();
	virtual void stepBy(int stepValue) = 0;
	virtual String printableValue() = 0;

protected:

	virtual void notify();

private :
	
	Storage *storage;
	StoredParameter storedParameter;
	String *title;
	void (*onChange)(Parameter *sender);

	Parameter();

};

#endif
