//===============
// Temperature.h
//===============

#pragma once


//=======
// Using
//=======

#include "HandleHelper.h"
#include "Variable.h"


//===========
// Namespace
//===========

namespace Physics {


//=============
// Temperature
//=============

class Temperature: public TypedVariable<FLOAT>
{
public:
	// Con-/Destructors
	Temperature(FLOAT DegreesCelsius=0.f);
	Temperature(Handle<String> Name, FLOAT DegreesCelsius=0.f);

	// Common
	Handle<String> ToString()override;
	static constexpr LPCSTR Unit="\260C";
};

}


//====================
// Temperature-Handle
//====================

template<>
class Handle<Physics::Temperature>
{
private:
	// Using
	using _temp_t=Physics::Temperature;

public:
	// Friends
	template <class _friend_t> friend class Handle;

	// Con-/Destructors
	Handle(): m_Object(nullptr) {}
	Handle(_temp_t* Object) { HandleCreate(&m_Object, Object); }
	Handle(Handle<_temp_t>&& Handle)noexcept: m_Object(Handle.m_Object) { Handle.m_Object=nullptr; }
	~Handle() { HandleClear(&m_Object); }

	// Access
	operator FLOAT() { return VariableGet(m_Object, -300.f); }
	_temp_t* operator->()const { return m_Object; }

	// Comparison
	BOOL operator==(FLOAT Value)const { return VariableEqual(m_Object, Value, -300.f); }

	// Assignment
	Handle& operator=(FLOAT Value) { VariableAssign(&m_Object, Value); return *this; }
	Handle& operator=(_temp_t* Object) { HandleAssign(&m_Object, Object); return *this; }
	Handle& operator=(Handle<_temp_t> const& Handle) { HandleAssign(&m_Object, Handle.m_Object); return *this; }

private:
	// Common
	_temp_t* m_Object;
};
