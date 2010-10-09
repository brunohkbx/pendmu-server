/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "GameServer.h"
#include "ItemDropRate.h"
#include <stdio.h>
#include "Creature.h"
#include "User.h"
#include "Utils.h"
#include "Log.h"
#include "PCPoints.h"
#include "CQuestSystem.h"
#include "ImperialEvent.h"

void __cdecl MonsterDie(LPGOBJSTRUCT lpObjOfMonster, LPGOBJSTRUCT lpObjOfPlayer)
{
	int MonsterNumber=lpObjOfMonster->m_Index;
	int MonsterType=GetKind(lpObjOfMonster->m_Index);
	int MonsterLevel=gObj_GetLevel(MonsterNumber);
	
	//Check if Mob is PCPointsMob
	PCPoint.LevelUp(lpObjOfPlayer->m_Index,MonsterType);

	g_Quest.QuestManage(lpObjOfPlayer->m_Index,MonsterType);
	//Going to the Drop function (bug Fix)
	gObjMonsterDieGiveItem(lpObjOfMonster, lpObjOfPlayer);
	
	//Imperial.MonsterManager(lpObjOfPlayer->m_Index,(aSend[4] + aSend[3] * 256));
	
	//=====================//
	//Imperial Event Drops //
	//=====================//
	if((lpObjOfMonster->Class == 20 && lpObjOfMonster->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
	{	
		ImperialMobCfg.nMonsterOfEvent--;

		//Messages.outNormal(aIndex,"[Imperial Fort] Killed Mob. [%d]",ImperialMobCfg.nMonsterOfEvent);
		if(ImperialMobCfg.nMonsterOfEvent > 0)
		{
			//return ;
		}
	}
	
	if((lpObjOfMonster->Class == 525 && lpObjOfMonster->MapNumber == Imperial.EventMap) || (lpObjOfMonster->Class == 524 && lpObjOfMonster->MapNumber == Imperial.EventMap))
	{
		return; //GCStateInfoSend((DWORD)pObj, 0, 0);
	}


	if((lpObjOfMonster->Class == 528 && lpObjOfMonster->MapNumber == Imperial.EventMap))
	{
		return; //GCStateInfoSend((DWORD)pObj, 0, 0);
	}

	//Log.outError("[Imperial Fort] MonsterItemDrop");

	
}


int itemsDroppedRequests=0;

//int __cdecl MyGEventMonsterItemDropCR ( DWORD * b_MonsterDataAddr ,LPGOBJSTRUCT lpObjOfPlayer)
BOOL gEventMonsterItemDrop ( LPGOBJSTRUCT lpObj ,LPGOBJSTRUCT lpObjOfPlayer)  
{
	//Monster Variables
	//int MonsterType=GetKind((DWORD)b_MonsterDataAddr[0]);
	int MonsterType = lpObj->Class;
	//int MonsterLevel=gObj_GetLevel((DWORD)b_MonsterDataAddr[0]);
	int MonsterLevel = lpObj->Level;
	//int MonsterId=(int)b_MonsterDataAddr[0];
	int MonsterId = lpObj->m_Index;
	
	//Player Variables
	int PlayerId=lpObjOfPlayer->m_Index;

	//Location Variables
	int Map=gObj_GetMap(MonsterId);
	int X=gObj_GetPosX(MonsterId);
	int Y=gObj_GetPosY(MonsterId);

	
	

	//========================================================================================================================================
	//New Random Rate Calculation
	//========================================================================================================================================
	itemsDroppedRequests = itemsDroppedRequests + 1;
	srand(static_cast<int>(time(NULL))+(MonsterId*MonsterLevel)+itemsDroppedRequests);
	int dwRand = (int)(rand()/(((double)RAND_MAX + 1)/10000));

	//Reset DropRequest Counter
	if (itemsDroppedRequests>65000)
	{
		itemsDroppedRequests=1;
	}
	


	
	//========================================================================================================================================
	//Log Portion [TRACE ONLY]
	//========================================================================================================================================
	//char sBuf[255] = {0};
	//wsprintf(sBuf, "[Drop System] ID: %d, Level: %d, Random: %d, Req: %d",MonsterId, MonsterLevel, dwRand, itemsDroppedRequests);
	//LogLine("%s\n", sBuf);

	//========================================================================================================================================
	//Drop Generator
	//========================================================================================================================================
	int ItemPosition=-1;
	UINT RewardItemNumber=0;

	if(bDropRateConfig==TRUE)
	{
		if (dwRand>0)
		{
			//Calling Drop System Function from Drops.cpp
			ItemPosition=GetDropConfigurationItem(dwRand, Map, MonsterLevel, MonsterId);
			RewardItemNumber=ItemGetNumberMake(DropRateConfig[ItemPosition].Type,DropRateConfig[ItemPosition].Index);
			//RewardItemNumber=DropRateConfig[ItemPosition].Type*512+DropRateConfig[ItemPosition].Index;
		}
	}

	//If drop position has been returned, drop item from the list
	if(ItemPosition > -1)
	{
		// Monster DMG
		DWORD dwTopHitDamageUser = gObjMonterTopHitDamageUser(lpObj);
		char sBuf[255] = {0};
		ItemSerialCreateSend(MonsterId,Map,X,Y,RewardItemNumber,DropRateConfig[ItemPosition].Level,DropRateConfig[ItemPosition].Duration,DropRateConfig[ItemPosition].Skill,DropRateConfig[ItemPosition].Luck,DropRateConfig[ItemPosition].Opt ,dwTopHitDamageUser,0,0 ) ;
		wsprintf(sBuf, "[Drop System][DROP] Map: %d, X: %d, Y: %d, ITEM: %d [%d,%d]", Map,X,Y,RewardItemNumber,DropRateConfig[ItemPosition].Type,DropRateConfig[ItemPosition].Index);
		Log.outNormal("%s\n", sBuf);
		return TRUE;
	}
	//If no drop returned from the list
	else
	{
		
		BOOL bValue = GsgEventMonsterItemDropFunc_Addr (lpObj, lpObjOfPlayer);
		return bValue;
	}
}