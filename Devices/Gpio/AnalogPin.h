//=============
// AnalogPin.h
//=============

#pragma once


//=======
// Using
//=======

#include "Data/Average.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//============
// Analog Pin
//============

class AnalogPin: public Object
{
public:
	// Con-/Destructors
	AnalogPin(Handle<String> Id, BYTE Pin);

	// Common
	BYTE GetPin()const { return uPin; }
	FLOAT Read();
	FLOAT Multiplicator;
	Handle<Float> Value;

private:
	// Common
	VOID OnLoop();
	Data::Average<FLOAT, 20, 4> fInput;
	Data::Average<FLOAT, 10> fValue;
	BYTE uPin;
};

}}
