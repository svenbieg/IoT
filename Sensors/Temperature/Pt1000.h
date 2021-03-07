//==========
// Pt1000.h
//==========
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


//========
// Pt1000
//========

class Pt1000: public Thermometer
{
public:
	// Con-/Destructors
	Pt1000(Handle<String> Id, BYTE AnalogPin, FLOAT Resistor=2200.f);

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
