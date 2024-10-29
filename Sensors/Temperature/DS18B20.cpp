//=============
// DS18B20.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "DS18B20.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//==================
// Con-/Destructors
//==================

DS18B20::DS18B20(Handle<String> hid, Handle<OneWire> hbus, UINT64 uid, DS18B20Resolution res):
Thermometer(hid),
m_Id(uid),
m_OneWire(hbus),
m_Resolution(res)
{
WriteResolution();
BeginConversion();
m_Timer=new Timer();
m_Timer->Triggered.Add(this, &DS18B20::OnTimerTriggered);
m_Timer->StartPeriodic(1000);
}


//========
// Common
//========

VOID DS18B20::SetResolution(DS18B20Resolution res)
{
m_Resolution=res;
WriteResolution();
}


//================
// Common Private
//================

VOID DS18B20::BeginConversion()
{
if(!m_OneWire->Select(m_Id))
	{
	Temperature=-300.f;
	return;
	}
m_OneWire->Write(0x44);
}

VOID DS18B20::ReadResolution()
{
if(!m_OneWire->Select(m_Id))
	{
	Temperature=-300.f;
	return;
	}
m_OneWire->Write(0xBE);
BYTE pbuf[5];
m_OneWire->Read(pbuf, 5);
m_Resolution=(DS18B20Resolution)((pbuf[4]>>5)&0x03);
}

VOID DS18B20::ReadTemperature()
{
if(!m_OneWire->Select(m_Id))
	{
	Temperature=-300.f;
	return;
	}
m_OneWire->Write(0xBE);
BYTE pbuf[2];
m_OneWire->Read(pbuf, 2);
BYTE pmask[4]={ 0xFF, 0xFE, 0xFC, 0xF8 };
pbuf[0]&=pmask[(BYTE)m_Resolution];
WORD utemp=((WORD)pbuf[1]<<8)|pbuf[0];
Temperature=(FLOAT)utemp/16.f;
}

VOID DS18B20::WriteResolution()
{
if(!m_OneWire->Select(m_Id))
	return;
m_OneWire->Write(0x4E);
BYTE pbuf[3]={ 0, 0, 0 };
pbuf[2]=((BYTE)m_Resolution<<5)|0x1F;
m_OneWire->Write(pbuf, 3);
}

VOID DS18B20::OnTimerTriggered()
{
ReadTemperature();
BeginConversion();
}

}}
