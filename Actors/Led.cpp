//=========
// Led.cpp
//=========

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Devices/Gpio/GpioHelper.h"
#include "Led.h"

using namespace Devices::Gpio;
using namespace Core;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

Led::Led(BYTE upin, BOOL bon):
bOn(bon),
uInterval(0),
uLastTime(0),
uPin(upin)
{
SetPinMode(uPin, PinMode::Output);
DigitalWrite(uPin, bOn);
}

Led::~Led()
{
Set(false);
}


//========
// Common
//========

VOID Led::Blink(UINT uinterval)
{
uInterval=uinterval;
Application::Current->Loop.Add(this, &Led::OnLoop);
}

VOID Led::Off()
{
Set(false);
}

VOID Led::On()
{
Set(true);
}

VOID Led::Set(BOOL bon)
{
Application::Current->Loop.Remove(this);
bOn=bon;
DigitalWrite(uPin, bOn);
}


//================
// Common Private
//================

VOID Led::OnLoop()
{
UINT utime=GetTickCount();
if(utime<uLastTime+uInterval)
	return;
uLastTime=utime;
bOn=!bOn;
DigitalWrite(uPin, bOn);
}

}
