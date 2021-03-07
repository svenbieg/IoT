//============
// Pt1000.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Data/Row.h"
#include "Devices/Gpio/AnalogHelper.h"
#include "Devices/Gpio/GpioHelper.h"
#include "Runtime/Application.h"
#include "Pt1000.h"
#include "System.h"

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

const FLOAT pPtOhm[]=		{ 842.7f, 882.2f, 921.6f, 960.9f, 1000.f, 1039.f, 1077.9f, 1097.4f, 1116.7f, 1155.4f, 1194.f, 1232.4f, 1270.f, 1308.9f, 1347.f, 1385.f, 1422.f, 1460.6f, 1498.2f, 1535.8f, 1573.1f, 1600.f, 1640.f, 1680.f };
const FLOAT pPtTemp[]=		{  -40.f,  -30.f,  -20.f,  -10.f,    0.f,   10.f,    20.f,    25.f,    30.f,    40.f,   50.f,    60.f,   70.f,    80.f,   90.f,  100.f,  110.f,   120.f,   130.f,   140.f,   150.f, 160.f, 170.f, 180.f };


//==================
// Con-/Destructors
//==================

Pt1000::Pt1000(Handle<String> hid, BYTE upin, FLOAT fres):
Thermometer(hid),
fResistor(fres),
uErrorTime(0),
uPin(upin)
{
SetPinMode(uPin, PinMode::Input);
Application::Current->Loop.Add(this, &Pt1000::OnLoop);
}


//================
// Common Private
//================

VOID Pt1000::OnLoop()
{
FLOAT fvoltage=AnalogRead(uPin);
if(fvoltage<0.f)
	return;
FLOAT u=System::Voltage;
FLOAT i=fvoltage/fResistor;
FLOAT rges=u/i;
FLOAT r=rges-fResistor;
if(r>=842.7f&&r<=1573.1f)
	{
	FLOAT t=Row::Calculate(r, pPtOhm, pPtTemp, ARRAYSIZE(pPtOhm));
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
