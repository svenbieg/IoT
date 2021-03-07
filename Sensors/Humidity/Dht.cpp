//=========
// Dht.cpp
//=========

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "Devices/InterruptLock.h"
#include "Dht.h"

using namespace Devices;
using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Humidity {


//==================
// Con-/Destructors
//==================

Dht::Dht(Handle<String> hid, BYTE upin, DhtSensorVersion uver):
Thermometer(hid+"_Temperature"),
uLastRead(0),
uPin(upin),
uVersion(uver)
{
SetPinMode(uPin, PinMode::Output);
DigitalWrite(uPin, 0);
Humidity=new Int32(hid+"_Humidity");
hTimer=new Timer();
hTimer->Triggered.Add(this, &Dht::OnTimerTriggered);
hTimer->StartPeriodic(2000);
}


//================
// Common Private
//================

UINT Dht::ExpectPulse(BOOL b)
{
UINT utime=GetTickCountUs();
UINT ucycles=0;
while(GetTickCountUs()<utime+1000)
	{
	BOOL bpin=DigitalRead(uPin)>0;
	if(bpin!=b)
		return ucycles;
	ucycles++;
	}
return -1;
}

VOID Dht::OnTimerTriggered(Handle<Timer> htimer)
{
ReadSensor();
}

DhtSensorStatus Dht::ReadSensor()
{
FLOAT fhum=0.f;
FLOAT ftemp=0.f;
SetPinMode(uPin, PinMode::Output);
DigitalWrite(uPin, 0);
switch(uVersion)
	{
	case DhtSensorVersion::DHT22:
		{
		SleepMicroseconds(1100);
		break;
		}
	default:
		{
		Sleep(20);
		break;
		}
	}
UINT pcycles[82];
ZeroMemory(pcycles, 82*sizeof(UINT));
	{
	InterruptLock lock;
	SetPinMode(uPin, PinMode::Input);
	SleepMicroseconds(55);
	for(UINT u=0; u<82; u+=2)
		{
		pcycles[u]=ExpectPulse(false);
		pcycles[u+1]=ExpectPulse(true);
		}
	}
/*for(UINT u=0; u<82; u+=2)
	DebugPrint("\tLOW %u - HIGH %u\n", pcycles[u], pcycles[u+1]);*/
BYTE pdata[5];
for(UINT u=0; u<40; u++)
	{
	pdata[u/8]<<=1;
	if(pcycles[2+u*2]<pcycles[2+u*2+1])
		pdata[u/8]|=1;
	}
if(pdata[4]!=(BYTE)(pdata[0]+pdata[1]+pdata[2]+pdata[3]))
	{
	return DhtSensorStatus::Checksum;
	}
switch(uVersion)
	{
	case DhtSensorVersion::DHT11:
		{
		fhum=pdata[0]+pdata[1]*0.1f;
		ftemp=pdata[2];
		if(pdata[3]&0x80)
			ftemp=-1-ftemp;
		ftemp+=(pdata[3]&0xF)*0.1f;
		break;
		}
	case DhtSensorVersion::DHT22:
		{
		fhum=((WORD)pdata[0])<<8|pdata[1];
		fhum*=0.1f;
		ftemp=((WORD)(pdata[2]&0x7F))<<8|pdata[3];
		ftemp*=0.1f;
		if(pdata[2]&0x80)
			ftemp*=-1;
		break;
		}
	}
Humidity=fhum;
Temperature=ftemp;
return DhtSensorStatus::Success;
}

}}
