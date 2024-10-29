//==================
// RenderTarget.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "RenderTarget.h"
#include "Font.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//==================
// Con-/Destructors
//==================

RenderTarget::RenderTarget(Handle<Bitmap> bitmap):
m_Bitmap(bitmap),
m_Clip(0, 0, 0, 0),
m_Offset(0, 0)
{}


//========
// Common
//========

VOID RenderTarget::Clip(POINT const& offset, RECT const& clip)
{
m_Offset=offset;
m_Clip=clip;
}

VOID RenderTarget::DrawBitmap(RECT const& dst, Handle<Graphics::Bitmap> bmp, RECT const& src)
{
}

VOID RenderTarget::DrawLine(POINT const& from, POINT const& to, Handle<Graphics::Brush> brush, UINT width)
{
}

VOID RenderTarget::DrawPolygon(POINT const* points, UINT count, Handle<Graphics::Brush> brush, UINT width)
{
for(UINT u=0; u+1<count; u++)
	DrawLine(points[u], points[u+1], brush, width);
DrawLine(points[count-1], points[0], brush, width);
}

VOID RenderTarget::DrawRect(RECT const& rc, Handle<Graphics::Brush> brush, UINT width)
{
POINT from(rc.Left, rc.Top);
POINT to(rc.Right, rc.Top);
DrawLine(from, to, brush, width);
from.Set(rc.Left, rc.Top);
to.Set(rc.Left, rc.Bottom);
DrawLine(from, to, brush, width);
from.Set(rc.Right, rc.Top);
to.Set(rc.Right, rc.Bottom);
DrawLine(from, to, brush, width);
from.Set(rc.Left, rc.Bottom);
to.Set(rc.Right, rc.Bottom);
DrawLine(from, to, brush, width);
}

VOID RenderTarget::DrawText(RECT const& rc, FLOAT scale, LPCTSTR text, UINT len)
{
COLOR color=TextColor->GetColor();
if(color.GetAlpha()==0)
	return;
auto font=Convert<Emulation::Font>(Font);
if(!font)
	return;
RECT rc_text(rc);
rc_text+=m_Offset;
RECT rc_clip(rc_text);
rc_clip.SetBounds(m_Clip);
if(!rc_clip)
	return;
if(len==0)
	len=StringLength(text);
if(len==0)
	return;
UINT font_size=font->GetSize();
for(UINT u=0; u<len; u++)
	{
	if(rc_text.Left>=rc_clip.Right)
		break;
	BYTE uchar=(BYTE)text[u];
	auto char_info=font->GetCharInfo(uchar);
	auto pchar=char_info->Data;
	UINT char_width=char_info->Size/font_size;
	INT char_left=(INT)rc_text.Left;
	INT char_right=char_left+char_width;
	rc_text.Left=(FLOAT)char_right;
	if(char_right<rc_clip.Left)
		continue;
	for(UINT cy=0; cy<font_size; cy++)
		{
		INT y=(INT)rc_text.Top+cy;
		if(y<rc_clip.Top)
			continue;
		if(y>=rc_clip.Bottom)
			break;
		for(UINT cx=0; cx<char_width; cx++)
			{
			INT x=char_left+cx;
			if(x<rc_clip.Left)
				continue;
			if(x>=rc_clip.Right)
				break;
			if(pchar[cy*char_width+cx])
				m_Bitmap->SetPixel(x, y, color);
			}
		}
	}
}

VOID RenderTarget::FillPolygon(POINT const* points, UINT count, Handle<Graphics::Brush> brush)
{
DrawPolygon(points, count, brush);
}

VOID RenderTarget::FillRect(RECT const& rc, Handle<Graphics::Brush> brush)
{
COLOR c=brush->GetColor();
if(!c.GetAlpha())
	return;
RECT rc_fill(rc);
rc_fill+=m_Offset;
rc_fill.SetBounds(m_Clip);
if(!rc_fill)
	return;
for(INT y=rc_fill.Top; y<rc_fill.Bottom; y++)
	{
	for(INT x=rc_fill.Left; x<rc_fill.Right; x++)
		m_Bitmap->SetPixel(x, y, c);
	}
}

POINT RenderTarget::GetOffset()
{
POINT pt_clip(m_Clip.Left, m_Clip.Top);
return pt_clip-m_Offset;
}

SIZE RenderTarget::MeasureText(Handle<Graphics::Font> font, FLOAT scale, LPCTSTR text, UINT len)
{
SIZE size(0, 0);
auto emu_font=Convert<Emulation::Font>(font);
if(!emu_font)
	return size;
UINT font_size=emu_font->GetSize();
size.Height=font_size*scale;
if(!text)
	return size;
if(len==0)
	len=StringLength(text);
if(len==0)
	return size;
for(UINT u=0; u<len; u++)
	{
	auto char_info=emu_font->GetCharInfo((BYTE)CharToChar<CHAR, TCHAR>(text[u]));
	UINT char_width=char_info->Size/font_size;
	size.Width+=char_width;
	}
size.Width*=scale;
return size;
}

VOID RenderTarget::SetPixel(INT left, INT top, COLOR c)
{
left+=m_Offset.Left;
if(left<m_Clip.Left||left>=m_Clip.Right)
	return;
top+=m_Offset.Top;
if(top<m_Clip.Top||top>=m_Clip.Bottom)
	return;
m_Bitmap->SetPixel((INT)left, (INT)top, c);
}

VOID RenderTarget::Unclip()
{
m_Clip.Clear();
m_Offset.Clear();
}

}}