//==================
// StepperMotor.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "StepperMotor.h"

using namespace Devices;
using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

StepperMotor::StepperMotor(BYTE pin1, BYTE pin2, BYTE pin3, BYTE pin4):
Speed(1.f),
m_Phase(0),
m_Pin1(pin1),
m_Pin2(pin2),
m_Pin3(pin3),
m_Pin4(pin4),
m_Steps(0)
{
SetPinMode(m_Pin1, PinMode::Output);
SetPinMode(m_Pin2, PinMode::Output);
SetPinMode(m_Pin3, PinMode::Output);
SetPinMode(m_Pin4, PinMode::Output);
Stop();
}

StepperMotor::~StepperMotor()
{
Stop();
}


//========
// Common
//========

VOID StepperMotor::Backward(UINT usteps)
{
Stop();
if(Speed==0.f)
	return;
UINT udt=(UINT)(10000.f-Speed*9000.f);
m_Phase=16;
m_Steps=usteps;
m_Timer=new Timer();
m_Timer->Triggered.Add(this, &StepperMotor::OnTimerTriggered);
m_Timer->StartPeriodic(udt);
}

VOID StepperMotor::Forward(UINT usteps)
{
Stop();
if(Speed==0.f)
	return;
UINT udt=(UINT)(10000.f-Speed*9000.f);
m_Phase=0;
m_Steps=usteps;
m_Timer=new Timer();
m_Timer->Triggered.Add(this, &StepperMotor::OnTimerTriggered);
m_Timer->StartPeriodic(udt);
}

VOID StepperMotor::Stop()
{
if(m_Timer)
	{
	m_Timer->Stop();
	m_Timer=nullptr;
	}
DigitalWrite(m_Pin1, false);
DigitalWrite(m_Pin2, false);
DigitalWrite(m_Pin3, false);
DigitalWrite(m_Pin4, false);
}


//================
// Common Private
//================

VOID StepperMotor::OnTimerTriggered()
{
switch(m_Phase)
	{
	case 0:
	case 16:
		{
		DigitalWrite(m_Pin1, true);
		DigitalWrite(m_Pin2, false);
		DigitalWrite(m_Pin3, false);
		DigitalWrite(m_Pin4, false);
		break;
		}
	case 1:
	case 23:
		{
		DigitalWrite(m_Pin1, true);
		DigitalWrite(m_Pin2, true);
		DigitalWrite(m_Pin3, false);
		DigitalWrite(m_Pin4, false);
		break;
		}
	case 2:
	case 22:
		{
		DigitalWrite(m_Pin1, false);
		DigitalWrite(m_Pin2, true);
		DigitalWrite(m_Pin3, false);
		DigitalWrite(m_Pin4, false);
		break;
		}
	case 3:
	case 21:
		{
		DigitalWrite(m_Pin1, false);
		DigitalWrite(m_Pin2, true);
		DigitalWrite(m_Pin3, true);
		DigitalWrite(m_Pin4, false);
		break;
		}
	case 4:
	case 20:
		{
		DigitalWrite(m_Pin1, false);
		DigitalWrite(m_Pin2, false);
		DigitalWrite(m_Pin3, true);
		DigitalWrite(m_Pin4, false);
		break;
		}
	case 5:
	case 19:
		{
		DigitalWrite(m_Pin1, false);
		DigitalWrite(m_Pin2, false);
		DigitalWrite(m_Pin3, true);
		DigitalWrite(m_Pin4, true);
		break;
		}
	case 6:
	case 18:
		{
		DigitalWrite(m_Pin1, false);
		DigitalWrite(m_Pin2, false);
		DigitalWrite(m_Pin3, false);
		DigitalWrite(m_Pin4, true);
		break;
		}
	case 7:
	case 17:
		{
		DigitalWrite(m_Pin1, true);
		DigitalWrite(m_Pin2, false);
		DigitalWrite(m_Pin3, false);
		DigitalWrite(m_Pin4, true);
		break;
		}
	}
m_Phase++;
if(m_Phase==8)
	{
	m_Phase=0;
	m_Steps--;
	}
if(m_Phase==24)
	{
	m_Phase=16;
	m_Steps--;
	}
if(m_Steps==0)
	Stop();
}

}