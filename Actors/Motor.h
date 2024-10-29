//=========
// Motor.h
//=========

#pragma once


//=======
// Using
//=======

#include "FloatClass.h"


//===========
// Namespace
//===========

namespace Actors {


//=======
// Motor
//=======

class Motor: public Object
{
public:
	// Con-/Destructors
	Motor(Handle<String> Id, BYTE SpeedPin, BYTE ForwardPin, BYTE BackwardPin);

	// Common
	Handle<Float> Speed;

private:
	// Common
	VOID OnSpeedChanged();
	BYTE m_BackwardPin;
	BYTE m_ForwardPin;
	BYTE m_SpeedPin;
};

}
