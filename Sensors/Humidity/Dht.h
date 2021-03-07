//=======
// Dht.h
//=======

#pragma once


//=======
// Using
//=======

#include "Core/Timer.h"
#include "Sensors/Temperature/Thermometer.h"
#include "IntegerClasses.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Humidity {


//=========
// Version
//=========

enum class DhtSensorVersion
{
DHT11,
DHT22
};


//========
// Status
//========

enum class DhtSensorStatus
{
Success=0,
Checksum=-1,
Timeout=-2
};


//============
// DHT-Sensor
//============

class Dht: public Sensors::Temperature::Thermometer
{
private:
	// Using
	using Timer=Core::Timer;

public:
	// Con-/Destructors
	Dht(Handle<String> Id, BYTE Pin, DhtSensorVersion Version=DhtSensorVersion::DHT22);

	// Common
	inline BYTE GetPin()const { return uPin; }
	Handle<Int32> Humidity;

private:
	// Common
	UINT ExpectPulse(BOOL Pulse);
	VOID OnTimerTriggered(Handle<Timer> Timer);
	DhtSensorStatus ReadSensor();
	Handle<Timer> hTimer;
	UINT uLastRead;
	BYTE uPin;
	DhtSensorVersion uVersion;
};

}}
