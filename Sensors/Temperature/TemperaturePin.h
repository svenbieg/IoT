//==================
// TemperaturePin.h
//==================

#pragma once


//=======
// Using
//=======

#include "Data/Average.h"
#include "Devices/OneWire.h"
#include "Thermometer.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//======
// Mode
//======

enum class TemperaturePinMode
{
Kty81_210,
Pt1000
};


//=================
// Temperature Pin
//=================

class TemperaturePin: public Thermometer
{
private:
	// Using
	using OneWire=Devices::OneWire;
	typedef VOID (TemperaturePin::*TempProc)();

public:
	// Con-/Destructors
	TemperaturePin(Handle<String> Id, BYTE AnalogPin, BYTE DigitalPin, TemperaturePinMode Mode);

private:
	// Common
	VOID DetectThermometer();
	VOID OnLoop();
	VOID ReadAnalog();
	VOID ReadDigital();
	FLOAT VoltageToTemperature(FLOAT Voltage);
	Data::Average<FLOAT, 20, 4> fInput;
	Data::Average<FLOAT, 10> fTemperature;
	Handle<OneWire> hOneWire;
	TempProc pProcedure;
	BYTE uAnalogPin;
	BYTE uDigitalPin;
	UINT64 uId;
	TemperaturePinMode uMode;
	UINT64 uNextRead;
	UINT64 uTimeout;
};

}}