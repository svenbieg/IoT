//==============
// KTY-81-210.h
//==============
//
// Connection:
// Vss - Sensor - AI - 2.2k+0.1uF - 0V
//

#pragma once


//=======
// Using
//=======

#include "Data/Average.h"
#include "Thermometer.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//============
// KTY-81-210
//============

class Kty_81_210: public Thermometer
{
public:
	// Con-/Destructors
	Kty_81_210(Handle<String> Id, BYTE AnalogPin, FLOAT Resistor=2200.f);

private:
	// Common
	VOID OnLoop();
	Data::Average<FLOAT, 20, 4> fInput;
	FLOAT fResistor;
	Data::Average<FLOAT, 10> fTemperature;
	UINT uErrorTime;
	BYTE uPin;
};

}}
