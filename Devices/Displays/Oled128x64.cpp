//================
// Oled128x64.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/I2C/I2CBus.h"
#include "Oled128x64.h"

using namespace Devices::I2C;


//===========
// Namespace
//===========

namespace Devices {
	namespace Displays {


//=========
// I2C-Bus
//=========

enum Command: BYTE
{
CmdChargePump=0x8D,
CmdColumnAddr=0x21,
CmdComScanDec=0xC8,
CmdDeactivateScroll=0x2E,
CmdDisplayAllOnResume=0xA4,
CmdDisplayOff=0xAE,
CmdDisplayOn=0xAF,
CmdMemoryMode=0x20,
CmdNormalDisplay=0xA6,
CmdPageAddr=0x22,
CmdSegRemap=0xA0,
CmdSetCompIns=0xDA,
CmdSetContrast=0x81,
CmdSetDisplayClockDiv=0xD5,
CmdSetDisplayOffset=0xD3,
CmdSetMultiplex=0xA8,
CmdSetPrecharge=0xD9,
CmdSetStartLine=0x40,
CmdSetVComDetect=0xDB,
};


//==================
// Con-/Destructors
//==================

Oled128x64::Oled128x64(BYTE uaddr):
Display(128, 64, BitmapFormat::Monochrome),
uAddress(uaddr)
{
if(!I2CBus::Current)
	I2CBus::Current=new I2CBus();
auto hbus=I2CBus::Current;
BYTE pinit1[]={ CmdDisplayOff, CmdSetDisplayClockDiv, 0x80, CmdSetMultiplex };
SendCommands(pinit1, ARRAYSIZE(pinit1));
SendCommand((BYTE)(uHeight-1));
BYTE pinit2[]={ CmdSetDisplayOffset, 0, CmdSetStartLine, CmdChargePump };
SendCommands(pinit2, ARRAYSIZE(pinit2));
SendCommand(0x14);
BYTE pinit3[]={ CmdMemoryMode, 0, CmdSegRemap|1, CmdComScanDec };
SendCommands(pinit3, ARRAYSIZE(pinit3));
BYTE pinit4[]={ CmdSetCompIns, 0x12, CmdSetContrast };
SendCommands(pinit4, ARRAYSIZE(pinit4));
SendCommand(0xCF);
SendCommand(CmdSetPrecharge);
SendCommand(0xF1);
BYTE pinit5[]={ CmdSetVComDetect, 0x40, CmdDisplayAllOnResume, CmdNormalDisplay, CmdDeactivateScroll, CmdDisplayOn };
hbus->BeginWrite(uAddress);
hbus->Write(pinit5, ARRAYSIZE(pinit5));
hbus->EndTransmission();
}


//========
// Common
//========

VOID Oled128x64::Flush()
{
if(!uAddress)
	return;
BYTE pcmd[]={ CmdPageAddr, 0x00, 0xFF, CmdColumnAddr, 0 };
SendCommands(pcmd, ARRAYSIZE(pcmd));
SendCommand((BYTE)uWidth-1);
UINT usize=uWidth*uHeight/8;
BYTE* pbmp=hBitmap->Begin();
for(UINT upos=0; upos<usize; )
	{
	UINT ucopy=MIN(usize-upos, 31);
	auto hbus=I2CBus::Current;
	hbus->BeginWrite(uAddress);
	hbus->Write(0x40);
	hbus->Write(&pbmp[upos], ucopy);
	hbus->EndTransmission();
	upos+=ucopy;
	}
}


//================
// Common Private
//================

VOID Oled128x64::SendCommand(BYTE ucmd)
{
auto hbus=I2CBus::Current;
hbus->BeginWrite(uAddress);
hbus->Write(0);
hbus->Write(ucmd);
hbus->EndTransmission();
}

VOID Oled128x64::SendCommands(BYTE const* pcmd, UINT ucount)
{
auto hbus=I2CBus::Current;
hbus->BeginWrite(uAddress);
hbus->Write(0);
hbus->Write(pcmd, ucount);
hbus->EndTransmission();
}

}}