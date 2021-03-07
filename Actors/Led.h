//=======
// Led.h
//=======

#pragma once


//===========
// Namespace
//===========

namespace Actors {


//=====
// Led
//=====

class Led: public Object
{
public:
	// Con-/Destructors
	Led(BYTE Pin, BOOL On=false);
	~Led();

	// Common
	VOID Blink(UINT Interval=1000);
	VOID Off();
	VOID On();
	virtual VOID Set(BOOL On);

protected:
	// Common
	VOID OnLoop();
	BOOL bOn;
	UINT uInterval;
	UINT uLastTime;
	BYTE uPin;
};

}
