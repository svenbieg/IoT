//============
// Beeper.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Beeper.h"


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

Beeper::Beeper(Handle<String> hid, BYTE upin)
{
hTransistor=new Transistor(hid, upin);
Value=hTransistor->Value;
}

}
