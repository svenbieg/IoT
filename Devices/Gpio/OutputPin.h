//=============
// OutputPin.h
//=============

#pragma once


//=======
// Using
//=======

#include "BoolClass.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//============
// Output-Pin
//============

class OutputPin: public Object
{
public:
	// Con-/Destructors
	OutputPin(Handle<String> Id, BYTE Pin, BOOL Value=false);

	// Common
	Event<OutputPin> Changed;
	Event<OutputPin> Down;
	inline BYTE GetPin() { return uPin; }
	Event<OutputPin> Up;
	Handle<Bool> Value;

private:
	// Common
	VOID OnValueChanged(Handle<Variable> Variable);
	BYTE uPin;
};

}}
