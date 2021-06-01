#ifndef Parameter_h
#define Parameter_h

#include "Arduino.h"
#include "Feature.h"
#include "../Storage/StoredParameter.h"


class Storage;


class Parameter: public Feature {

public:

	virtual ~Parameter();
	Parameter(String *title, Storage *storage, StoredParameter parameter, void (*onChange)(Parameter *sender) = nullptr);

protected:

	Storage *storage;
	StoredParameter storedParameter;
	
	virtual bool canFocus();
	virtual void tap();
	virtual void notify();

private :

	void (*onChange)(Parameter *sender);
	Parameter();

};

#endif
