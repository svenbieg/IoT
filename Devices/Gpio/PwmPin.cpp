//============
// PwmPin.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "Devices/Gpio/PwmHelper.h"
#include "PwmPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

PwmPin::PwmPin(Handle<String> hid, BYTE upin, UINT uperiod):
uPeriod(uperiod),
uPin(upin)
{
PwmInit(uPin, uPeriod);
Value=new Float(hid, 0.f);
Value->Changed.Add(this, &PwmPin::OnValueChanged);
}


//================
// Common Private
//================

VOID PwmPin::OnValueChanged(Handle<Variable> hvar)
{
FLOAT f=Value;
PwmSetDuty(uPin, (UINT)(f*uPeriod));
}

}}
