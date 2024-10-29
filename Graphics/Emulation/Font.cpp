//==========
// Font.cpp
//==========

#include "pch.h"


//=======
// Using
//=======

#include "Font.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//============================
// Con-/Destructors Protected
//============================

Font::Font(UINT size):
m_Size(size)
{
ZeroMemory(m_Characters, sizeof(m_Characters));
}

}}