//===========
// Theme.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Fonts/SmallFont.h"
#include "Graphics/Emulation/Cursor.h"
#include "Graphics/Emulation/Font.h"
#include "Theme.h"

using namespace Graphics::Emulation::Fonts;

using EmuCursor=Graphics::Emulation::Cursor;
using EmuFont=Graphics::Emulation::Font;


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//==================
// Con-/Destructors
//==================

Theme::Theme(Themes theme)
{
DefaultCursor=new EmuCursor();
DefaultFont=new SmallFont();
switch(theme)
	{
	case Themes::m_Dark:
		{
		BorderBrush=new Brush(Colors::LightGray);
		ControlBrush=new Brush(Colors::Black);
		FocusBorderBrush=new Brush(Colors::FocusBorder);
		FocusBrush=new Brush(Colors::Focus);
		GrayTextBrush=new Brush(Colors::Gray);
		HighlightBrush=new Brush(Colors::Highlight);
		HighlightBorderBrush=new Brush(Colors::HighlightBorder);
		InactiveHighlightBrush=new Brush(Colors::Silver);
		LightBorderBrush=new Brush(Colors::Gray);
		LightControlBrush=new Brush(Colors::BlackGray);
		LightTextBrush=new Brush(Colors::Gray);
		TextBrush=new Brush(Colors::White);
		WindowBrush=new Brush(Colors::Black);
		break;
		}
	case Themes::m_Light:
		{
		BorderBrush=new Brush(Colors::Gray);
		ControlBrush=new Brush(Colors::White);
		FocusBorderBrush=new Brush(Colors::FocusBorder);
		FocusBrush=new Brush(Colors::Focus);
		GrayTextBrush=new Brush(Colors::Gray);
		HighlightBrush=new Brush(Colors::Highlight);
		HighlightBorderBrush=new Brush(Colors::HighlightBorder);
		InactiveHighlightBrush=new Brush(Colors::Silver);
		LightBorderBrush=new Brush(Colors::LightGray);
		LightControlBrush=new Brush(Colors::WhiteGray);
		LightTextBrush=new Brush(Colors::Gray);
		TextBrush=new Brush(Colors::Black);
		WindowBrush=new Brush(Colors::White);
		break;
		}
	case Themes::m_Monochrome:
		{
		BorderBrush=new Brush(Colors::White);
		ControlBrush=new Brush(Colors::Black);
		FocusBorderBrush=new Brush(Colors::White);
		FocusBrush=new Brush(Colors::Transparent);
		GrayTextBrush=new Brush(Colors::White);
		HighlightBrush=new Brush(Colors::Black);
		HighlightBorderBrush=new Brush(Colors::White);
		InactiveHighlightBrush=new Brush(Colors::Black);
		LightBorderBrush=new Brush(Colors::White);
		LightControlBrush=new Brush(Colors::Black);
		LightTextBrush=new Brush(Colors::White);
		TextBrush=new Brush(Colors::White);
		WindowBrush=new Brush(Colors::Black);
		break;
		}
	}
}


//========
// Common
//========

Handle<Theme> Theme::Get(Themes theme)
{
switch(theme)
	{
	case Themes::m_Dark:
		{
		if(!m_Dark)
			m_Dark=new Theme(theme);
		return m_Dark;
		}
	case Themes::m_Light:
		{
		if(!m_Light)
			m_Light=new Theme(theme);
		return m_Light;
		}
	case Themes::m_Monochrome:
		{
		if(!m_Monochrome)
			m_Monochrome=new Theme(theme);
		return m_Monochrome;
		}
	}
return nullptr;
}

Handle<Theme> Theme::m_Dark;
Handle<Theme> Theme::m_Light;
Handle<Theme> Theme::m_Monochrome;

}}