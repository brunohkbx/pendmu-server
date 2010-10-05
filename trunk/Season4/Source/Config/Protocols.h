/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "StdAfx.h"
#include <stdio.h>

__declspec(dllexport)BYTE ProtocolServer(BYTE Type);
__declspec(dllexport)BYTE ProtocolClient(BYTE Type);

//bool DLLProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial);
bool ProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial); 

void ProtocolCoreSend(DWORD PlayerID,PBYTE tpProtocol,DWORD ProtocolLen);


