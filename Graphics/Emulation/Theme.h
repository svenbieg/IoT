//=========
// Theme.h
//=========

#pragma once


//=======
// Using
//=======

#include "Graphics/Theme.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//========
// Themes
//========

enum class Themes
{
m_Dark,
m_Light,
m_Monochrome
};


//=======
// Theme
//=======

class Theme: public Graphics::Theme
{
public:
	// Con-/Destructors
	Theme(Themes Theme=Themes::m_Light);

	// Common
	static Handle<Theme> Get(Themes Theme=Themes::m_Light);

private:
	// Common
	static Handle<Theme> m_Dark;
	static Handle<Theme> m_Light;
	static Handle<Theme> m_Monochrome;
};

}}
