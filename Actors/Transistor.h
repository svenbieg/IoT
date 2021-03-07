//==============
// Transistor.h
//==============

#pragma once


//=======
// Using
//=======

#include "FloatClasses.h"


//===========
// Namespace
//===========

namespace Actors {


//===================
// Transistor BC547C
//===================

class Transistor: public Object
{
public:
	// Con-/Destructors
	Transistor(Handle<String> Id, BYTE PwmPin);

	// Common
	BYTE GetPin()const { return uPin; }
	Handle<Float> Value;

private:
	// Common
	VOID OnValueChanged(Handle<Variable> Variable);
	BYTE uPin;
};

}
