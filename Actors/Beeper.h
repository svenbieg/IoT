//==========
// Beeper.h
//==========

#pragma once


//=======
// Using
//=======

#include "Transistor.h"


//===========
// Namespace
//===========

namespace Actors {


//========
// Beeper
//========

class Beeper: public Object
{
public:
	// Con-/Destructors
	Beeper(Handle<String> Id, BYTE Pin);

	// Common
	Handle<Float> Value;
	BYTE GetPin()const { return hTransistor->GetPin(); }

private:
	// Common
	Handle<Transistor> hTransistor;
};

}
