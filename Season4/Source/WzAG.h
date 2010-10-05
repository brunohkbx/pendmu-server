/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "StdAfx.h"
#include "Items.h"
#include "Common.h"
#include <direct.h>

#define GS_BASE (0x401000)

void GS();
void MakeDir();
void __declspec(naked) GetQueComplStatusFix()
{
	_asm
	{
		//004B1D9E Hook, JMP back 004B1DA7
		CMP DWORD PTR SS:[EBP-0x30],0x3E3 //Original
		JE AllowSomeShit;

		CMP DWORD PTR SS:[EBP-0x30],0x79 //121 Error
		JE AllowSomeShit;

		mov edi, 0x004B1DA7;
		jmp edi;

	AllowSomeShit:
		mov edi, 0x004B1DD9;
		jmp edi;
	}
}
