//============
// PwmPin.cpp
//============

#include "pch.h"


//=======
// Using
//=======

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

PwmPin::PwmPin(Handle<String> id, BYTE pin, UINT period):
GpioPin(id, pin),
m_Period(period)
{
PwmInit(m_Pin, m_Period);
Value=new Float(id, 0.f);
Value->Changed.Add(this, &PwmPin::OnValueChanged);
}


//================
// Common Private
//================

VOID PwmPin::OnValueChanged()
{
PwmSetDuty(m_Pin, (UINT)(Value*m_Period));
}

}}
