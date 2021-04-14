//=============
// Display.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Runtime/Application.h"
#include "Display.h"

using namespace Core;
using namespace Graphics;


//===========
// Namespace
//===========

namespace Devices {
	namespace Displays {


//============================
// Con-/Destructors Protected
//============================

Display::Display(UINT uwidth, UINT uheight, BitmapFormat uformat):
BackgroundColor(Colors::Black),
uHeight(uheight),
uWidth(uwidth)
{
hBitmap=new Bitmap(uwidth, uheight, uformat);
hDeviceContext=new DeviceContext();
Application::Current->Loop.Add(this, &Display::OnLoop);
}

Display::~Display()
{
Application::Current->Loop.Remove(this);
}


//================
// Common Private
//================

VOID Display::OnLoop()
{
hDeviceContext->SetTarget(hBitmap);
hDeviceContext->Clear(BackgroundColor);
BOOL brendered=Content->Render(hDeviceContext);
hDeviceContext->Flush();
if(brendered)
	this->Flush();
}

}}