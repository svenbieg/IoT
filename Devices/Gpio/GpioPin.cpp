//=============
// GpioPin.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "GpioPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

Handle<GpioPin::PinMap> GpioPin::Pins;


//============================
// Con-/Destructors Protected
//============================

GpioPin::GpioPin(Handle<String> id, BYTE pin):
m_Id(id),
m_Pin(pin)
{
if(!Pins)
	Pins=new PinMap();
Pins->Add(m_Id, this);
}

GpioPin::~GpioPin()
{
Pins->Remove(m_Id);
if(Pins->GetCount()==0)
	Pins=nullptr;
}

}}