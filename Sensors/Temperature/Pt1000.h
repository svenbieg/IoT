//==========
// Pt1000.h
//==========
//
// Connection:
// Vss - Sensor - AI - 2.2k - 0V
//

#pragma once


//=======
// Using
//=======

#include "Devices/Gpio/AnalogPin.h"
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
private:
	// Using
	using AnalogPin=Devices::Gpio::AnalogPin;

public:
	// Con-/Destructors
	Pt1000(Handle<String> Id, Handle<AnalogPin> AnalogPin, FLOAT Voltage=3.3f, FLOAT Resistor=2200.f);

private:
	// Common
	VOID OnValueChanged();
	UINT m_ErrorTime;
	Handle<AnalogPin> m_Pin;
	FLOAT m_Resistor;
	FLOAT m_Voltage;
};

}}
