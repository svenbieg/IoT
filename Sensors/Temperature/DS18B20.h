//===========
// DS18B20.h
//===========

#pragma once


//=======
// Using
//=======

#include "UI/Timer.h"
#include "Devices/Gpio/OneWire.h"
#include "Thermometer.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//============
// Resolution
//============

enum class DS18B20Resolution: BYTE
{
Bits9,
Bits10,
Bits11,
Bits12
};


//============================
// DS18B20 Dallas Temperature
//============================

class DS18B20: public Thermometer
{
private:
	// Using
	using OneWire=Devices::Gpio::OneWire;
	using Timer=UI::Timer;

public:
	// Con-/Destructors
	DS18B20(Handle<String> Id, Handle<OneWire> Bus, UINT64 BusId, DS18B20Resolution Resolution=DS18B20Resolution::Bits12);

	// Common
	DS18B20Resolution GetResolution()const { return m_Resolution; }
	VOID SetResolution(DS18B20Resolution Resolution);

private:
	// Common
	VOID BeginConversion();
	VOID OnTimerTriggered();
	VOID ReadResolution();
	VOID ReadTemperature();
	VOID WriteResolution();
	UINT64 m_Id;
	Handle<OneWire> m_OneWire;
	DS18B20Resolution m_Resolution;
	Handle<Timer> m_Timer;
};

}}
