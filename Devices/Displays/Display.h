//===========
// Display.h
//===========

#pragma once


//=======
// Using
//=======

#include "Core/Controls/Control.h"
#include "Graphics/Emulation/Bitmap.h"
#include "Graphics/DeviceContext.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Displays {


//=========
// Display
//=========

class Display: public Object
{
protected:
	// Using
	using Bitmap=Graphics::Emulation::Bitmap;
	using BitmapFormat=Graphics::BitmapFormat;
	using COLOR=Graphics::COLOR;
	using CoreControl=Core::Controls::Control;
	using DeviceContext=Graphics::DeviceContext;

public:
	// Common
	COLOR BackgroundColor;
	Handle<CoreControl> Content;
	virtual VOID Flush()=0;
	Handle<DeviceContext> GetDeviceContext()const { return hDeviceContext; }
	UINT GetHeight()const { return uHeight; }
	UINT GetWidth()const { return uWidth; }

protected:
	// Con-/Destructors
	Display(UINT Width, UINT Height, BitmapFormat Format);
	~Display();

	// Common
	Handle<Bitmap> hBitmap;
	Handle<DeviceContext> hDeviceContext;
	UINT uHeight;
	UINT uWidth;

private:
	// Common
	VOID OnLoop();
};

}}