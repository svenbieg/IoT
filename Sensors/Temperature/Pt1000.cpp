//============
// Pt1000.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Math/DataRow.h"
#include "Pt1000.h"

using namespace Math;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//==========
// Settings
//==========

const FLOAT pPtOhm[]= { 842.7f, 882.2f, 921.6f, 960.9f, 1000.f, 1039.f, 1077.9f, 1097.4f, 1116.7f, 1155.4f, 1194.f, 1232.4f, 1270.f, 1308.9f, 1347.f, 1385.f, 1422.f, 1460.6f, 1498.2f, 1535.8f, 1573.1f, 1600.f, 1640.f, 1680.f };
const FLOAT pPtTemp[]={  -40.f,  -30.f,  -20.f,  -10.f,    0.f,   10.f,    20.f,    25.f,    30.f,    40.f,   50.f,    60.f,   70.f,    80.f,   90.f,  100.f,  110.f,   120.f,   130.f,   140.f,   150.f, 160.f, 170.f, 180.f };


//==================
// Con-/Destructors
//==================

Pt1000::Pt1000(Handle<String> id, Handle<AnalogPin> pin, FLOAT volt, FLOAT res):
Thermometer(id),
m_ErrorTime(0),
m_Pin(pin),
m_Resistor(res),
m_Voltage(volt)
{
m_Pin->Value->Changed.Add(this, &Pt1000::OnValueChanged);
}


//================
// Common Private
//================

VOID Pt1000::OnValueChanged()
{
FLOAT ur=m_Pin->Value;
FLOAT uges=m_Voltage;
FLOAT i=ur/m_Resistor;
FLOAT rges=uges/i;
FLOAT r=rges-m_Resistor;
if(r>=842.7f&&r<=1680.f)
	{
	FLOAT t=DataRow::Calculate(r, pPtOhm, pPtTemp, ArraySize(pPtOhm));
	Temperature->Set(t);
	m_ErrorTime=0;
	}
else
	{
	UINT time=GetTickCount();
	if(m_ErrorTime==0)
		m_ErrorTime=time;
	if(time<m_ErrorTime+5000)
		return;
	Temperature->Set(-300.f);
	}
}

}}
