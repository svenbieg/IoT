//=====================
// LiquidFlowMeter.cpp
//=====================

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"
#include "LiquidFlowMeter.h"

using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Flow {


//==================
// Con-/Destructors
//==================

LiquidFlowMeter::LiquidFlowMeter(Handle<String> hid, BYTE upin, BYTE upcnt, UINT uml):
uMillisPerTick(uml)
{
Flow=new Physics::Flow(hid, -1);
hPin=new ImpulsePin(upin, upcnt);
}


//================
// Common Private
//================

VOID LiquidFlowMeter::OnLoop()
{
UINT ucount=hPin->GetImpulseCount();
UINT umlpersec=ucount*uMillisPerTick;
Flow->Set(umlpersec);
}

}}
