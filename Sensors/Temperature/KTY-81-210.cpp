//================
// KTY-81-210.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Data/Row.h"
#include "Devices/Gpio/AnalogHelper.h"
#include "Devices/Gpio/GpioHelper.h"
#include "Runtime/Application.h"
#include "System.h"
#include "KTY-81-210.h"

using namespace Data;
using namespace Devices::Gpio;
using namespace Runtime;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//==========
// Settings
//==========

const FLOAT pKtyOhm[]=		{ 1135.f, 1247.f, 1396.f, 1495.f, 1630.f, 1772.f, 1922.f, 2000.f, 2080.f, 2245.f, 2417.f, 2597.f, 2785.f, 2980.f, 3118.f, 3392.f, 3817.f, 4008.f, 4166.f, 4280.f };
const FLOAT pKtyTemp[]=		{  -40.f,  -30.f,  -20.f,  -10.f,    0.f,   10.f,   20.f,   25.f,   30.f,   40.f,   50.f,   60.f,   70.f,   80.f,   90.f,  100.f,  110.f,  120.f,  130.f,  140.f };


//==================
// Con-/Destructors
//==================

Kty_81_210::Kty_81_210(Handle<String> hid, BYTE upin, FLOAT fres):
Thermometer(hid),
fResistor(fres),
uErrorTime(0),
uPin(upin)
{
SetPinMode(uPin, PinMode::Input);
Application::Current->Loop.Add(this, &Kty_81_210::OnLoop);
}


//================
// Common Private
//================

VOID Kty_81_210::OnLoop()
{
FLOAT fvoltage=AnalogRead(uPin);
if(fvoltage<0.f)
	return;
FLOAT u=System::Voltage;
FLOAT i=fvoltage/fResistor;
FLOAT rges=u/i;
FLOAT r=rges-fResistor;
if(r>=1135.f&&r<=4280.f)
	{
	FLOAT t=Row::Calculate(r, pKtyOhm, pKtyTemp, ARRAYSIZE(pKtyOhm));
	fInput=t;
	if(fInput.GetCount()==20)
		{
		fTemperature=fInput;
		fInput.Reset();
		Temperature->Set(fTemperature);
		}
	uErrorTime=0;
	}
else
	{
	UINT utime=GetTickCount();
	if(uErrorTime==0)
		uErrorTime=utime;
	if(utime<uErrorTime+5000)
		return;
	fInput.Reset();
	fTemperature.Reset();
	Temperature->Set(-300.f);
	}
}

}}
