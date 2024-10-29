//==============
// InputPin.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "Devices/Clock.h"
#include "Core/Application.h"
#include "InputPin.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

InputPin::InputPin(Handle<String> id, BYTE pin):
GpioPin(id, pin)
{
SetPinMode(m_Pin, PinMode::Input);
BOOL value=DigitalRead(m_Pin);
Value=new Bool(id, value);
AttachInterrupt(m_Pin);
auto clock=Clock::Get();
clock->Tick.Add(this, &InputPin::OnClockTick);
}

InputPin::~InputPin()
{
DetachInterrupt(m_Pin);
auto clock=Clock::Get();
clock->Tick.Remove(this);
}


//================
// Common Private
//================

VOID InputPin::DoChange()
{
BOOL old_value=Value;
BOOL new_value=DigitalRead(m_Pin);
if(old_value==new_value)
	{
	Value=!new_value;
	old_value? Down(this): Up(this);
	Value=new_value;
	new_value? Up(this): Down(this);
	}
else
	{
	Value=new_value;
	if(old_value)Down(this);
	if(new_value)Up(this);
	}
}

VOID InputPin::OnClockTick()
{
BOOL changed=DetectInterrupt(m_Pin);
if(changed)
	Application::Current->Dispatch(this, &InputPin::DoChange);
}

}}
