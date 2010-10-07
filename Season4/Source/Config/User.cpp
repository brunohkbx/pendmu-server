/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "StdAfx.h"
#include "User.h"
#include "Log.h"
#include "Utils.h"

#include <stdio.h>
#include "GameServer.h"
#include "DuelSystem.h"
#include "Structure.h"
#include "SQL_Manager.h"
#include "NPC.h"
#include "PCPoints.h"
#include "CQuestSystem.h"

GOBJSTRUCT *ObjTab = (GOBJSTRUCT*)OBJECT_BASE;


void FireWorksSend(UINT MapNumber, BYTE X, BYTE Y,int Cant)
{
	BYTE Explode[] = {0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00};
	Explode[5] = (BYTE)X;
	Explode[6] = (BYTE)Y;
	if (Cant>100) return;
	for(int i=0;i<Cant;i++)
	{ 
		DataSendNear(MapNumber,X,Y,Explode,Explode[1],6);
	}
}

void FireWorksSendAll(int Cant)
{
	if (Cant>100) return;
	for(int aIndex=MIN_PLAYERID;aIndex<MAX_PLAYERID;aIndex++)
	{
		if (gObjIsConnected(aIndex)==true)
		{
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
			FireWorksSend(gObj->MapNumber,gObj->X,gObj->Y,Cant);
		}
	}
}


BOOL __cdecl gObjGameClose_Func(int aIndex)
{
	if (aIndex >=MIN_PLAYERID && aIndex <=MAX_PLAYERID)
	{
		int ID;	
		//Getting Player Structure
		LPGOBJSTRUCT gObj = (LPGOBJSTRUCT)(aIndex*gObjSize + gObjBaseAddr);
		ID=aIndex-MIN_PLAYERID;
	
	
		//If not transfer server, save all
	
		PCPoint.SQLSetStatus(aIndex);
		GoldenArcherSaveData(aIndex);
		Log.outNormal("[%s][%s][%d] Save New Data Complete.",gObj->AccountID,gObj->Name,aIndex);
	
		conLog.ConsoleOutputDT("[%s][%s][%d] Disconnect.",gObj->AccountID,gObj->Name,aIndex);
		if(Duel.isInDuelRoom(aIndex)==TRUE&&pObjGS[ID].isInDuelEvent==1)
			Duel.ClearRoombyPlayerID(aIndex);
		g_Quest.QuestUpdateSQL(aIndex);
	}
	
	//Going to this func (fix)
	
	BOOL rValue = gObjGameClose(aIndex);
	return rValue;
	
}
