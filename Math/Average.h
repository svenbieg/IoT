//===========
// Average.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace Math {


//=========
// Average
//=========

template <class _value_t, UINT _count=8, UINT _ignore=0>
class Average
{
public:
	// Con-/Destructors
	Average(): m_Count(0), m_Value(0) {}

	// Access
	operator _value_t()const { return m_Value; }
	UINT GetCount()const { return m_Count; }
	_value_t const* GetValues()const { return m_Values; }

	// Modification
	Average& operator=(_value_t Value)
		{
		if(m_Count<_count)
			{
			m_Values[m_Count++]=Value;
			}
		else
			{
			MoveMemory(m_Values, &m_Values[1], (m_Count-1)*sizeof(_value_t));
			m_Values[m_Count-1]=Value;
			}
		_value_t psorted[_count];
		for(UINT u=0; u<m_Count; u++)
			{
			BOOL bdone=false;
			for(UINT s=0; s<u; s++)
				{
				if(m_Values[u]<psorted[s])
					{
					MoveMemory(&psorted[s+1], &psorted[s], (u-s-1)*sizeof(_value_t));
					psorted[s]=m_Values[u];
					bdone=true;
					break;
					}
				}
			if(bdone)
				continue;
			psorted[u]=m_Values[u];
			}
		_value_t t=0;
		if(m_Count>_ignore*2)
			{
			for(UINT u=_ignore; u<m_Count-_ignore; u++)
				t+=m_Values[u];
			m_Value=t/(m_Count-_ignore*2);
			}
		else
			{
			for(UINT u=0; u<m_Count; u++)
				t+=m_Values[u];
			m_Value=t/m_Count;
			}
		return *this;
		}
	VOID Reset() { m_Value=0; m_Count=0; }

private:
	// Common
	UINT m_Count;
	_value_t m_Value;
	_value_t m_Values[_count];
};

}