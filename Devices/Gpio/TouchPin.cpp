//==============
// TouchPin.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Devices/Gpio/TouchHelper.h"
#include "Devices/Clock.h"
#include "TouchPin.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

TouchPin::TouchPin(Handle<String> id, BYTE pin):
GpioPin(id, pin),
m_Average(0),
m_AverageCount(0)
{
Value=new Bool(id);
if(!TouchInit(m_Pin))
	return;
auto clock=Clock::Get();
clock->Tick.Add(this, &TouchPin::OnClockTick);
}

TouchPin::~TouchPin()
{
TouchClose(m_Pin);
auto clock=Clock::Get();
clock->Tick.Remove(this);
}


//================
// Common Private
//================

VOID TouchPin::DoSet(BOOL value)
{
Value->Set(value);
value? Touched(this): Released(this);
}

WORD TouchPin::GetTreshold()
{
if(m_AverageCount>=32)
	return m_Average;
WORD value=TouchRead(m_Pin);
m_Average+=value;
m_AverageCount++;
if(m_AverageCount<32)
	return 0;
m_Average=m_Average/32-100;
if(m_Average<200)
	{
	DebugPrint("Touch-Pin %u average too low\n", m_Pin);
	TouchClose(m_Pin);
	auto clock=Clock::Get();
	clock->Tick.Remove(this);
	return 0;
	}
TouchTreshold(m_Pin, m_Average);
return m_Average;
}

VOID TouchPin::OnClockTick()
{
WORD threshold=GetTreshold();
if(!threshold)
	return;
WORD value=TouchRead(m_Pin);
BOOL b_new=value<threshold;
BOOL b_old=Value;
if(b_old==b_new)
	return;
Application::Current->Dispatch(this, [this, b_new]() { DoSet(b_new); });
}

}}