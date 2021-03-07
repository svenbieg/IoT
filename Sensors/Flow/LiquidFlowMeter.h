//===================
// LiquidFlowMeter.h
//===================

#pragma once


//========
// Wiring
//========

// S0+ (green) -> 5V
// S0- (brown) -> GPIO -> 4K7 -> 0V


//=======
// Using
//=======

#include "Devices/Gpio/ImpulsePin.h"
#include "Physics/Flow.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Flow {


//===================
// Liquid-Flow-Meter
//===================

class LiquidFlowMeter: public Object
{
private:
	// Using
	using ImpulsePin=Devices::Gpio::ImpulsePin;

public:
	// Con-/Destructors
	LiquidFlowMeter(Handle<String> Id, BYTE Pin, BYTE PcntUnit, UINT MillisPerTick);

	// Common
	Handle<Physics::Flow> Flow;

private:
	// Common
	VOID OnLoop();
	Handle<ImpulsePin> hPin;
	UINT uMillisPerTick;
};

}}
