//========
// Font.h
//========

#pragma once


//=======
// Using
//=======

#include "Graphics/Font.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//======
// Font
//======

class Font: public Graphics::Font
{
public:
	// Char-Info
	typedef struct
		{
		const BYTE* Data;
		WORD Size;
		}CHARINFO;

	// Common
	CHARINFO const* GetCharInfo(BYTE Char) { return &m_Characters[Char]; }
	UINT GetSize()const override { return m_Size; }

protected:
	// Con-/Destructors
	Font(UINT Size);

	// Common
	CHARINFO m_Characters[256];
	UINT m_Size;
};

}}