/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "Structure.h"
#include "GameServer.h"
#include "Utils.h"
#include "DuelSystem.h"
#include "Log.h"
#include "Protocols.h"

Arena Config;


void __cdecl MoveGate_Hook(DWORD aIndex, UINT GateNum)
{
	int ID = aIndex-MIN_PLAYERID;
	char sBuf[255] = {0};
	LPGOBJSTRUCT pObj = (LPGOBJSTRUCT)(aIndex*gObjSize + gObjBaseAddr);
	if (pObjGS[ID].isInDuelEvent==0)
	{
		//Check if player in Duel Spectator State
		Duel.DeleteSpectator(aIndex,0);	//ROOM 1
		Duel.DeleteSpectator(aIndex,1);	//ROOM 2
		Duel.DeleteSpectator(aIndex,2);	//ROOM 3
		Duel.DeleteSpectator(aIndex,3);	//ROOM 4

		//If player move before auto-warp, clear his state
		pObjGS[ID].isDuelEnded=0;
		pObjGS[ID].DuelWarpSeconds=0;
	}
	else if ((pObj->TargetNumber!=-1)&&(pObj->pTransaction==1))
	{
		GCServerMsgStringSend("[Anti-Hack][Move] DUPE ATTEMPT: In Trade!",aIndex, 0x01);
		wsprintf(sBuf, "[Anti-Hack][%s][%d,%d,%d] Move Trade-Dupe Attempt, Trade: %s[%d], Action: %d",pObj->Name,pObj->MapNumber,pObj->X,pObj->Y,GetName(pObj->TargetNumber),pObj->TargetNumber,pObj->pTransaction);
		Log.outError(sBuf);
		return;

	}
	
	else if (pObj->m_IfState==389)
	{
		GCServerMsgStringSend("[Anti-Hack][Move] DUPE ATTEMPT: Open Warehouse!",aIndex, 0x01);
		wsprintf(sBuf, "[Anti-Hack][%s][%d,%d,%d] Move Warehouse-Dupe Attempt, State: %d",pObj->Name,pObj->MapNumber,pObj->X,pObj->Y,pObj->m_IfState);
		Log.outError(sBuf);
		return;
	}
	 else if ((pObj->m_IfState==769)||(pObj->m_IfState==829)) 
	 {
		GCServerMsgStringSend("[Anti-Hack][Move] DUPE ATTEMPT: Lehap Dialog!",aIndex, 0x01);
		wsprintf(sBuf, "[Anti-Hack][%s][%d,%d,%d] Move Lehap Dialog Attempt, State: %d",pObj->Name,pObj->MapNumber,pObj->X,pObj->Y,pObj->m_IfState);
		Log.outError(sBuf);
		return;
	}

	else if ((pObj->m_IfState&3)==1) 
	{
		GCServerMsgStringSend("[Anti-Hack][Move] DUPE ATTEMPT: Unknown!",aIndex, 0x01);
		wsprintf(sBuf, "[Anti-Hack][Move]: [%s] Unknown !!!",pObj->Name);
		Log.outError(sBuf);
		return;
	 }

	else if (pObjGS[ID].isInDuelEvent==1&&Duel.isInDuelRoom(aIndex)==TRUE)
	{
		GCServerMsgStringSend("Cant move while in DUEL!!!",aIndex, 0x01);
		return;
	}

	
	gObjMoveGate_JMP(aIndex,GateNum);
	
	
}



void InitProto(void)
{
	
	if (Config.IsProtocol!=1)
	{
#ifdef GameServer90
		SetByte(0x004B21C6,0x33);
		SetByte(0x004B21C7,0xD2);
		SetByte(0x004B21C8,0xE9);
		SetByte(0x004B21C9,0xC8);
		SetByte(0x004B21CA,0x09);
		SetByte(0x004B21CB,0x00);
		SetByte(0x004B21CC,0x00);
		SetByte(0x004B21CD,0x90);
		SetByte(0x004B21CE,0x90);

		SetByte(0x004B2B95,0x8A);
		SetByte(0x004B2B96,0x51);
		SetByte(0x004B2B97,0x02);
		SetByte(0x004B2B98,0x52);
		SetByte(0x004B2B99,0xFF);
		SetByte(0x004B2B9A,0x15);
		SetByte(0x004B2B9B,0x04);
		SetByte(0x004B2B9C,0x28);
		SetByte(0x004B2B9D,0x65);
		SetByte(0x004B2B9E,0x00);
		SetByte(0x004B2B9F,0x88);
		SetByte(0x004B2BA0,0x45);
		SetByte(0x004B2BA1,0xE4);
		SetByte(0x004B2BA2,0x8B);
		SetByte(0x004B2BA3,0x45);
		SetByte(0x004B2BA4,0xF0);
		SetByte(0x004B2BA5,0xE9);
		SetByte(0x004B2BA6,0x25);
		SetByte(0x004B2BA7,0xF6);
		SetByte(0x004B2BA8,0xFF);
		SetByte(0x004B2BA9,0xFF);

		SetByte(0x004C256B,0x33);
		SetByte(0x004C256C,0xC9);
		SetByte(0x004C256D,0x8A);
		SetByte(0x004C256E,0x4D);
		SetByte(0x004C256F,0x0C);
		SetByte(0x004C2570,0x51);
		SetByte(0x004C2571,0xFF);
		SetByte(0x004C2572,0x15);
		SetByte(0x004C2573,0x00);
		SetByte(0x004C2574,0x28);
		SetByte(0x004C2575,0x65);
		SetByte(0x004C2576,0x00);
		SetByte(0x004C2577,0x8B);
		SetByte(0x004C2578,0x75);
		SetByte(0x004C2579,0x08);
		SetByte(0x004C257A,0x88);
		SetByte(0x004C257B,0x46);
		SetByte(0x004C257C,0x02);
		SetByte(0x004C257D,0x5F);
		SetByte(0x004C257E,0x5E);
		SetByte(0x004C257F,0x5B);
		SetByte(0x004C2580,0x8B);
		SetByte(0x004C2581,0xE5);
		SetByte(0x004C2582,0x5D);
		SetByte(0x004C2583,0xC3);

		_asm
			{
				Mov Dword Ptr Ds:[00652800H],Offset ProtocolServer
				Mov Dword Ptr Ds:[00652804H],Offset ProtocolClient

			}
#endif
	}
}

