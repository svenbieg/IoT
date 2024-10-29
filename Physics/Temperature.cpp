//=================
// Temperature.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Temperature.h"


//===========
// Namespace
//===========

namespace Physics {


//==================
// Con-/Destructors
//==================

Temperature::Temperature(FLOAT deg_c):
Temperature(nullptr, deg_c)
{}

Temperature::Temperature(Handle<String> name, FLOAT deg_c):
TypedVariable(name, deg_c)
{}


//========
// Common
//========

Handle<String> Temperature::ToString()
{
SharedLock lock(m_Mutex);
if(m_Value==-300.f)
	return "-";
return new String("%i\260C", (INT)m_Value);
}

}