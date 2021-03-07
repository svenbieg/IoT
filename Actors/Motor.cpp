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

Motor::Motor(Handle<String> hid, BYTE upinspeed, BYTE upinfwd, BYTE upinback):
uPinBackward(upinback),
uPinForward(upinfwd),
uPinSpeed(upinspeed)
{
SetPinMode(uPinBackward, PinMode::Output);
SetPinMode(uPinForward, PinMode::Output);
PwmInit(uPinSpeed, 5000);
Speed=new Float(hid, 0.f);
Speed->Changed.Add(this, &Motor::OnSpeedChanged);
}


//================
// Common Private
//================

VOID Motor::OnSpeedChanged(Handle<Variable> hvar)
{
FLOAT fspeed=Speed;
fspeed=MAX(fspeed, -1);
fspeed=MIN(fspeed, 1.);
DigitalWrite(uPinForward, fspeed>0.f);
DigitalWrite(uPinBackward, fspeed<0.f);
if(fspeed<0.f)
	fspeed*=-1.f;
UINT uduty=(UINT)(fspeed*5000);
PwmSetDuty(uPinSpeed, uduty);
}

}
