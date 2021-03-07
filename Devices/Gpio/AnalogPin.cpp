//===============
// AnalogPin.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Devices/Gpio/AnalogHelper.h"
#include "Devices/Gpio/GpioHelper.h"
#include "AnalogPin.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {
	

//==================
// Con-/Destructors
//==================

AnalogPin::AnalogPin(Handle<String> hid, BYTE upin):
Multiplicator(1.f),
uPin(upin)
{
SetPinMode(uPin, PinMode::Input);
Value=new Float(hid, 0.0f);
Application::Current->Loop.Add(this, &AnalogPin::OnLoop);
}


//========
// Common
//========

FLOAT AnalogPin::Read()
{
while(fInput.GetCount()<20)
	fInput=AnalogRead(uPin);
fValue=fInput*Multiplicator;
Value->Set(fValue);
return fValue;
}


//================
// Common Private
//================

VOID AnalogPin::OnLoop()
{
fInput=AnalogRead(uPin);
if(fInput.GetCount()<20)
	return;
fValue=fInput*Multiplicator;
Value->Set(fValue);
}

}}
