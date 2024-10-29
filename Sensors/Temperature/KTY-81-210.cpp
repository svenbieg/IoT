//================
// KTY-81-210.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Math/DataRow.h"
#include "KTY-81-210.h"

using namespace Math;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//==========
// Settings
//==========

const FLOAT pKtyOhm[]= { 1135.f, 1247.f, 1396.f, 1495.f, 1630.f, 1772.f, 1922.f, 2000.f, 2080.f, 2245.f, 2417.f, 2597.f, 2785.f, 2980.f, 3118.f, 3392.f, 3817.f, 4008.f, 4166.f, 4280.f };
const FLOAT pKtyTemp[]={  -40.f,  -30.f,  -20.f,  -10.f,    0.f,   10.f,   20.f,   25.f,   30.f,   40.f,   50.f,   60.f,   70.f,   80.f,   90.f,  100.f,  110.f,  120.f,  130.f,  140.f };


//==================
// Con-/Destructors
//==================

Kty_81_210::Kty_81_210(Handle<String> id, Handle<AnalogPin> pin, FLOAT volt, FLOAT res):
Thermometer(id),
m_ErrorTime(0),
m_Pin(pin),
m_Resistor(res),
m_Voltage(volt)
{
m_Pin->Value->Changed.Add(this, &Kty_81_210::OnValueChanged);
}


//================
// Common Private
//================

VOID Kty_81_210::OnValueChanged()
{
FLOAT ur=m_Pin->Value;
FLOAT uges=m_Voltage;
FLOAT i=ur/m_Resistor;
FLOAT rges=uges/i;
FLOAT r=rges-m_Resistor;
if(r>=1135.f&&r<=4280.f)
	{
	FLOAT t=DataRow::Calculate(r, pKtyOhm, pKtyTemp, ArraySize(pKtyOhm));
	Temperature->Set(t);
	m_ErrorTime=0;
	}
else
	{
	UINT utime=GetTickCount();
	if(m_ErrorTime==0)
		m_ErrorTime=utime;
	if(utime<m_ErrorTime+5000)
		return;
	Temperature->Set(-300.f);
	}
}

}}
