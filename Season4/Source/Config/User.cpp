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
#include "Items.h"
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

void __stdcall JGPGetCharInfoEx(int Loop, unsigned char *DSPacket, unsigned char *toClientPacket) {
	unsigned char ItemType = DSPacket[76 + (66 * Loop)]; //72 - Wings, 76 - Guardian
	register int nCol = (Loop * 34) + 38;
	register int CharSet5 = (Loop * 34) + 27; //CharSet[5]
	register int CharSet9 = (Loop * 34) + 31; //CharSet[9]
	register int CharSet10 = (Loop * 34) + 32; //CharSet[10]
	register int CharSet15 = (Loop * 34) + 37; //CharSet[15]
	register int CharSet17 = (Loop * 34) + 39; //CharSet[17]

	unsigned char Boots = DSPacket[68 + (66 * Loop)]; //Boots on Char
	unsigned char BootsLvl = DSPacket[69 + (66 * Loop)]; //Boots Level

	switch(ItemType)
	{
	case 0x50:
		toClientPacket[nCol] = 224;
		break;
	case 0x7B:
		toClientPacket[CharSet5]  -= 3;
		toClientPacket[nCol] = 96;

		break;
	}

	if(Boots == 255)
	{
		toClientPacket[CharSet5] |= CS_SET_BOOTS3(-1);
	}
}

/*void __stdcall gObjViewportPatchExecute(GOBJSTRUCT *lpObj) {

	if(lpObj->pInventory[GUARDIAN].m_Type != SLOT_EMPTY)
		gObjCharacterWingsSetPreview(lpObj->pInventory[GUARDIAN].m_Type, lpObj->CharSet, GUARDIAN,lpObj);
}
*/
void gObjCharacterWingsSetPreview(short ItemType, unsigned char *CharSet,int Type,GOBJSTRUCT *lpObj) 
{	
	if(Type == GUARDIAN)
	{
		register unsigned char PreviewPet = 0;

		switch(ItemType)
		{
		case 0x1A50: //Panda
			PreviewPet = 224;
			break;

		case 0x1A43:
			PreviewPet = 0x80;
			break;

		case 0x1A41:
			PreviewPet = 0x40;
			break;

		case 0x1A40:
			PreviewPet = 0x20;
			break;

		case 0x1A7B: //Skeleton
			CharSet[5] -= 3;
			PreviewPet = 96; //112
			break;

		default:
			PreviewPet = 0;
			break;
		}
		
		CharSet[16] = PreviewPet;
	}
}
