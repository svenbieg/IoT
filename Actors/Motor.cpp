//===========
// Motor.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "Devices/Gpio/PwmHelper.h"
#include "Motor.h"

using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

Motor::Motor(Handle<String> id, BYTE pin_speed, BYTE pin_fwd, BYTE pin_back):
m_BackwardPin(pin_back),
m_ForwardPin(pin_fwd),
m_SpeedPin(pin_speed)
{
SetPinMode(m_BackwardPin, PinMode::Output);
SetPinMode(m_ForwardPin, PinMode::Output);
PwmInit(m_SpeedPin, 5000);
Speed=new Float(id, 0.f);
Speed->Changed.Add(this, &Motor::OnSpeedChanged);
}


//================
// Common Private
//================

VOID Motor::OnSpeedChanged()
{
FLOAT speed=Speed;
speed=Max(speed, -1.f);
speed=Min(speed, 1.f);
DigitalWrite(m_ForwardPin, speed>0.f);
DigitalWrite(m_BackwardPin, speed<0.f);
if(speed<0.f)
	speed*=-1.f;
UINT duty=(UINT)(speed*5000);
PwmSetDuty(m_SpeedPin, duty);
}

}
