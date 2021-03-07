//================
// Transistor.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/PwmHelper.h"
#include "System.h"
#include "Transistor.h"

using namespace Devices::Gpio;


//==========
// Settings
//==========

const FLOAT fTransistorDelta=0.22f;
const FLOAT fTransistorMin=0.58f;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

Transistor::Transistor(Handle<String> hid, BYTE upin):
uPin(upin)
{
PwmInit(uPin, 1000);
Value=new Float(hid, 0.f);
Value->Changed.Add(this, &Transistor::OnValueChanged);
}


//================
// Common Private
//================

VOID Transistor::OnValueChanged(Handle<Variable> hvar)
{
FLOAT f=Value;
if(f==0.f)
	{
	PwmSetDuty(uPin, 0);
	return;
	}
f=fTransistorMin+f*fTransistorDelta;
f/=System::Voltage;
PwmSetDuty(uPin, (UINT)(f*1000));
}

}
