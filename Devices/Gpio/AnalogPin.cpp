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
#include "Devices/Clock.h"
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

AnalogPin::AnalogPin(Handle<String> id, BYTE pin):
GpioPin(id, pin)
{
SetPinMode(m_Pin, PinMode::Input);
Value=new Float(id, 0.0f);
auto clock=Clock::Get();
clock->Tick.Add(this, &AnalogPin::OnClockTick);
}

AnalogPin::~AnalogPin()
{
auto clock=Clock::Get();
clock->Tick.Remove(this);
}


//========
// Common
//========

FLOAT AnalogPin::Read()
{
return AnalogRead(m_Pin);
}


//================
// Common Private
//================

VOID AnalogPin::OnClockTick()
{
m_Input=AnalogRead(m_Pin);
if(m_Input.GetCount()<20)
	return;
m_Value=m_Input;
Value=m_Value;
}

}}
