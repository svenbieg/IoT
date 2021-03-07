//====================
// TemperaturePin.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Data/Row.h"
#include "Devices/Gpio/AnalogHelper.h"
#include "Devices/Gpio/GpioHelper.h"
#include "System.h"
#include "TemperaturePin.h"

using namespace Core;
using namespace Data;
using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//==========
// Settings
//==========

const FLOAT pKtyOhm[]=		{ 1630.f, 1772.f, 1922.f, 2000.f, 2080.f, 2245.f, 2417.f, 2597.f, 2785.f, 2980.f, 3118.f, 3392.f, 3817.f, 4008.f, 4166.f, 4280.f };
const FLOAT pKtyTemp[]=		{    0.f,   10.f,   20.f,   25.f,   30.f,   40.f,   50.f,   60.f,   70.f,   80.f,   90.f,  100.f,  110.f,  120.f,  130.f,  140.f };
const FLOAT pPtOhm[]=		{ 842.7f, 882.2f, 921.6f, 960.9f, 1000.f, 1039.f, 1077.9f, 1097.4f, 1116.7f, 1155.4f, 1194.f, 1232.4f, 1270.f, 1308.9f, 1347.f, 1385.f, 1422.f, 1460.6f, 1498.2f, 1535.8f, 1573.1f };
const FLOAT pPtTemp[]=		{  -40.f,  -30.f,  -20.f,  -10.f,    0.f,   10.f,    20.f,    25.f,    30.f,    40.f,   50.f,    60.f,   70.f,    80.f,   90.f,  100.f,  110.f,   120.f,   130.f,   140.f,   150.f };


//==================
// Con-/Destructors
//==================

TemperaturePin::TemperaturePin(Handle<String> hid, BYTE uanalog, BYTE udigital, TemperaturePinMode mode):
Thermometer(hid),
pProcedure(&TemperaturePin::DetectThermometer),
uAnalogPin(uanalog),
uDigitalPin(udigital),
uMode(mode),
uNextRead(0)
{
SetPinMode(uAnalogPin, PinMode::Input);
hOneWire=new OneWire(uDigitalPin);
Application::Current->Loop.Add(this, &TemperaturePin::OnLoop);
}


//================
// Common Private
//================

VOID TemperaturePin::DetectThermometer()
{
UINT64 uid=0;
if(hOneWire->Scan(&uid, 1))
	{
	if(!hOneWire->Select(uid))
		return;
	DebugPrint("Digital thermometer found at pin %u\n", uDigitalPin);
	hOneWire->Write(0x4E);
	BYTE pbuf[3]={ 0, 0, 0 };
	pbuf[2]=((BYTE)3<<5)|0x1F;
	hOneWire->Write(pbuf, 3);
	uId=uid;
	uNextRead=0;
	pProcedure=&TemperaturePin::ReadDigital;
	return;
	}
FLOAT fvoltage=AnalogRead(uAnalogPin);
if(fvoltage<0.f)
	return;
FLOAT ftemp=VoltageToTemperature(fvoltage);
if(ftemp!=-300.f)
	{
	DebugPrint("Analog thermometer found at pin %u\n", uAnalogPin);
	fInput.Reset();
	fTemperature.Reset();
	uNextRead=0;
	uTimeout=0;
	pProcedure=&TemperaturePin::ReadAnalog;
	return;
	}
}

VOID TemperaturePin::OnLoop()
{
(this->*pProcedure)();
}

VOID TemperaturePin::ReadAnalog()
{
FLOAT fvoltage=AnalogRead(uAnalogPin);
if(fvoltage>0.f)
	{
	FLOAT ftemp=VoltageToTemperature(fvoltage);
	if(ftemp!=-300.f)
		{
		uTimeout=0;
		fInput=ftemp;
		if(fInput.GetCount()==20)
			{
			fTemperature=fInput;
			fInput.Reset();
			Temperature->Set(fTemperature);
			}
		return;
		}
	}
if(uTimeout==0)
	{
	uTimeout=GetTickCount64()+5000;
	return;
	}
if(GetTickCount64()>uTimeout)
	{
	DebugPrint("Analog thermometer lost at pin %u\n", uAnalogPin);
	Temperature=-300.f;
	pProcedure=&TemperaturePin::DetectThermometer;
	}
}

VOID TemperaturePin::ReadDigital()
{
if(!hOneWire->Select(uId))
	{
	DebugPrint("Digital thermometer lost at pin %u\n", uDigitalPin);
	Temperature=-300.f;
	pProcedure=&TemperaturePin::DetectThermometer;
	return;
	}
if(uNextRead==0)
	{
	hOneWire->Write(0x44);
	uNextRead=GetTickCount64()+1000;
	return;
	}
UINT64 utime=GetTickCount64();
if(utime>=uNextRead)
	{
	hOneWire->Write(0xBE);
	BYTE pbuf[2];
	hOneWire->Read(pbuf, 2);
	pbuf[0]&=0xF8;
	WORD utemp=((WORD)pbuf[1]<<8)|pbuf[0];
	FLOAT ftemp=(FLOAT)utemp/16.f;
	Temperature->Set(ftemp);
	uNextRead=0;
	}
}

FLOAT TemperaturePin::VoltageToTemperature(FLOAT fvoltage)
{
FLOAT u=System::Voltage;
FLOAT ur=u-fvoltage;
FLOAT i=ur/4700.f;
FLOAT rges=u/i;
FLOAT r=rges-4700;
FLOAT ftemp=-300.f;
switch(uMode)
	{
	case TemperaturePinMode::Kty81_210:
		{
		ftemp=Row::Calculate(r, pKtyOhm, pKtyTemp, ARRAYSIZE(pKtyOhm), -300.f);
		break;
		}
	case TemperaturePinMode::Pt1000:
		{
		ftemp=Row::Calculate(r, pPtOhm, pPtTemp, ARRAYSIZE(pPtOhm), -300.f);
		break;
		}
	}
return ftemp;
}

}}