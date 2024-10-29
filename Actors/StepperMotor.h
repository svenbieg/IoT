//================
// StepperMotor.h
//================

#pragma once


//=======
// Using
//=======

#include "Devices/Timer.h"


//===========
// Namespace
//===========

namespace Actors {


//===============
// Stepper-Motor
//===============

class StepperMotor: public Object
{
private:
	// Using
	using Timer=Devices::Timer;

public:
	// Con-/Destructors
	StepperMotor(BYTE Pin1, BYTE Pin2, BYTE Pin3, BYTE Pin4);
	~StepperMotor();

	// Common
	VOID Backward(UINT Steps=-1);
	VOID Forward(UINT Steps=-1);
	FLOAT Speed;
	VOID Stop();

private:
	// Common
	VOID OnTimerTriggered();
	BYTE m_Phase;
	BYTE m_Pin1;
	BYTE m_Pin2;
	BYTE m_Pin3;
	BYTE m_Pin4;
	UINT m_Steps;
	Handle<Timer> m_Timer;
};

}