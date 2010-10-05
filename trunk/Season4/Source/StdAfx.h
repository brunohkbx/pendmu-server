/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#if !defined(AFX_STDAFX_H__EC514948_DA54_48A7_950A_93DDC986B831__INCLUDED_)
#define AFX_STDAFX_H__EC514948_DA54_48A7_950A_93DDC986B831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Type Of DLL
#define GameServer90
//define GameServerCS90
//Includes & Defines

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <commctrl.h>
#include <process.h>
using namespace std;
//#include <winsock2.h>
#include "Global.h"
#pragma comment(lib,"ws2_32.lib")

static HMENU MyMenu;
static DWORD OldProtect;
static UINT_PTR MyMenuTimerID;
static UINT_PTR cPluginsTimer;

static HWND cWND;
static HINSTANCE hInst;

#pragma warning(disable: 4010)
#pragma warning(disable: 4018)
#pragma warning(disable: 4101)
#pragma warning(disable: 4244)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#pragma warning(disable: 4482)
#pragma warning(disable: 4996)
#pragma warning(disable: 4700)
#pragma warning(disable: 4996)
//typedef BYTE OBJECTSTRUCT;
#pragma warning(disable: 4305)
#pragma warning(disable: 4309)


typedef enum{
	Preto = 1,
	Vermelho = 2,
	Verde = 3,
	Azul = 4,
	Vermelho2 = 5,
	Azul2 = 6,
	Rosa = 7
}LogColors;

#endif // !defined(AFX_STDAFX_H__EC514948_DA54_48A7_950A_93DDC986B831__INCLUDED_)