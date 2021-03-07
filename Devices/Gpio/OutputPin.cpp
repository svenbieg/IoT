//===============
// OutputPin.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "OutputPin.h"

using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

OutputPin::OutputPin(Handle<String> hid, BYTE upin, BOOL bvalue):
uPin(upin)
{
SetPinMode(uPin, PinMode::Output);
DigitalWrite(uPin, bvalue);
Value=new Bool(hid, bvalue);
Value->Changed.Add(this, &OutputPin::OnValueChanged);
}


//================
// Common Private
//================

VOID OutputPin::OnValueChanged(Handle<Variable> hvar)
{
BOOL b=Value->Get();
DigitalWrite(uPin, b);
b? Up(this): Down(this);
Changed(this);
}

}}
