//==========
// PwmPin.h
//==========

#pragma once


//=======
// Using
//=======

#include "FloatClasses.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// PWM-Pin
//=========

class PwmPin: public Object
{
public:
	// Con-/Destructors
	PwmPin(Handle<String> Id, BYTE Pin, UINT Period);

	// Common
	BYTE GetPin()const { return uPin; }
	Handle<Float> Value;

private:
	// Common
	VOID OnValueChanged(Handle<Variable> Variable);
	UINT uPeriod;
	BYTE uPin;
};

}}
