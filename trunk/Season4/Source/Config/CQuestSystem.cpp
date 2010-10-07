#include "StdAfx.h"
#include "Common.h"
#include "CQuestSystem.h"
#include "Log.h"
#include "Utils.h"
#include "GameServer.h"
#include "Structure.h"
#include "SQL_Manager.h"
#include "CSQL.h"
#include "WzMemScript.h"


CQuestSystem g_Quest;

void CQuestSystem::Init()
{
	for(int i=0;i<MAX_QUESTS;i++)
	{
		this->m_QuestData[i].iQuestIndex =0;
		this->m_QuestData[i].IsRewardItem = 0;
		this->m_QuestData[i].iRewardZen = 0;
		this->m_QuestData[i].wRewardLevel = 0;
		this->m_QuestData[i].iRewardExp =0;
		this->m_QuestData[i].iRewardPoints = 0;
		this->m_QuestData[i].iMonsterId = 0;
		this->m_QuestData[i].iMonsterLevel = 0;
		this->m_QuestData[i].iMapNumber = 0;
		this->m_QuestData[i].wLevelReq = 0;
		this->m_QuestData[i].iMonsterCount = 0;

		//Item Reward

		this->m_QuestItem[i].iQuestIndex = 0;
		this->m_QuestItem[i].bType = 0;
		this->m_QuestItem[i].bIndex = 0;
		this->m_QuestItem[i].bLuck = 0;
		this->m_QuestItem[i].bOptions = 0;
		this->m_QuestItem[i].bSkill = 0;
		this->m_QuestItem[i].bExcelent = 0;
	
	}

}

void CQuestSystem::LoadFile(char *filename)
{
	this->Init();
	
	if((SMDFile = fopen(filename, "r")) == NULL)
	{
		MessageBoxA(0,"CQuestManager::LoadFile() error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}
	
		
	SMDToken Token;
	//[Index]			=[1]- This is Number of Quest
	//[QuestName]		=[2]- This is name of Quest
	//[RewardZen]		=[3]- This is Count of Reward ZEN 
	//[RewardLvl]		=[4]- This is Count of Reward LVL 
	//[RewardExp]		=[5]- This is Count of Reward Exp
	//[RewardLevelUpPoint]	=[6]-This is Count of Reward LvlUpPoints
	//[MonsterId]		=[7]-This is monster id from Monster.txt
	//[MonsterLevel]	=[8]-This is monster Lvl from Monster id
	//[MapNumber]		=[9]-This is MapNumber Where should pass a quest
	//[Minlevel]		=[10]-This is Minimum lvl Which the character for quest start should have
	//[Monster Kill]		=[11]-Number Of Monster Must Kill
	//[IsMaster Reward]		=[12]-Options For Master receive Exp, point, Level
	//[QuestInfo]		=[13]- This is Info of Quest
	//[RewardItem]		=[14]- This is option - Enable/disabse reward item

	int iIndex;
	int iQuestIndex =0;
	char szQuestName[100] = {0};
	char szQuestInfo[100] = {0};
	BYTE IsRewardItem = 0;
	unsigned int iRewardZen = 0;
	WORD wRewardLevel = 0;
	unsigned int iRewardExp =0;
	int iRewardPoints = 0;
	int iMonsterId = 0;
	int iMonsterLevel = 0;
	int iMapNumber = 0;
	WORD wLevelReq = 0;
	int iMonsterCount = 0;
	BYTE IsForMaster = 0;

	//Item Reward
	
	BYTE bIndex = 0;
	BYTE bType = 0;
	BYTE bLevel = 0;
	BYTE bLuck = 0;
	BYTE bOptions = 0;
	BYTE bSkill = 0;
	BYTE bExcelent = 0;

	while(true)
	{
		Token = GetToken();
		
		if(Token == END)
			break;
	
		if(Token == NUMBER)
		{
			iIndex = TokenNumber;
			if (iIndex ==0)
			{
			
				while(true)
				{
					Token = GetToken();
				
					if(strcmp("end",TokenString) == 0)
						break;
		
					iQuestIndex = TokenNumber;
	
					Token = GetToken();
					IsRewardItem = TokenNumber;

					Token = GetToken();
					iRewardZen = TokenNumber;

					Token = GetToken();
					wRewardLevel = TokenNumber;

					Token = GetToken();
					iRewardExp = TokenNumber;

					Token = GetToken();
					iRewardPoints = TokenNumber;

					Token = GetToken();
					iMonsterId = TokenNumber;

					Token = GetToken();
					iMonsterLevel = TokenNumber;
				
					Token = GetToken();
					iMapNumber = TokenNumber;
				
					Token = GetToken();
					wLevelReq = TokenNumber;

					Token = GetToken();
					iMonsterCount = TokenNumber;

					Token = GetToken();
					IsForMaster = TokenNumber;

					Token = GetToken();
					memcpy(szQuestName,TokenString,sizeof(szQuestName));
	
					Token = GetToken();
					memcpy(szQuestInfo,TokenString,sizeof(szQuestInfo));
			


					this->Insert(iQuestIndex,IsRewardItem,iRewardZen,wRewardLevel,iRewardExp,iRewardPoints,iMonsterId,iMonsterLevel,iMapNumber,wLevelReq,iMonsterCount,IsForMaster,szQuestName,szQuestInfo);
				}
			}
			if (iIndex == 1)
			{
				while(true)
				{
					Token = GetToken();
				
					if(strcmp("end",TokenString) == 0)
						break;

					iQuestIndex = TokenNumber;


					Token = GetToken();
					bType = TokenNumber;

					Token = GetToken();
					bIndex = TokenNumber;

					Token = GetToken();
					bLevel = TokenNumber;

					Token = GetToken();
					bLuck = TokenNumber;

					Token = GetToken();
					bOptions = TokenNumber;

					Token = GetToken();
					bSkill = TokenNumber;

					Token = GetToken();
					bExcelent = TokenNumber;

					this->InsertItem(iQuestIndex,bType,bIndex,bLevel,bLuck,bOptions,bSkill,bExcelent);
				}
			}
		}
	}
	fclose(SMDFile);
	//Log.outNormal("File [%s] is Loaded",filename);
	conLog.ConsoleOutput("[Quest]File has been loaded",filename);
	return;
}

void CQuestSystem::Insert(int iQIndex,BYTE IsRewardItem,unsigned int iRewardZen,WORD wRewardLevel,unsigned int iRewardExp,int iRewardPoints,int iMonsterId,int iMonsterLevel,int iMapNumber,WORD wLevelReq,int iMonsterCount,BYTE IsForMaster, char *szQuestName,char *szQuestInfo)
{
	this->m_QuestData[iQIndex].iQuestIndex = iQIndex;
	strcpy(this->m_QuestData[iQIndex].szQuestName,szQuestName);
	strcpy(this->m_QuestData[iQIndex].szQuestInfo,szQuestInfo);
	this->m_QuestData[iQIndex].IsRewardItem = IsRewardItem;
	this->m_QuestData[iQIndex].iRewardZen = iRewardZen;
	this->m_QuestData[iQIndex].wRewardLevel = wRewardLevel;
	this->m_QuestData[iQIndex].iRewardExp = iRewardExp;
	this->m_QuestData[iQIndex].iRewardPoints = iRewardPoints;
	this->m_QuestData[iQIndex].iMonsterId = iMonsterId;
	this->m_QuestData[iQIndex].iMonsterLevel = iMonsterLevel;
	this->m_QuestData[iQIndex].iMapNumber = iMapNumber;
	this->m_QuestData[iQIndex].wLevelReq = wLevelReq;
	this->m_QuestData[iQIndex].iMonsterCount = iMonsterCount;
	this->m_QuestData[iQIndex].IsForMaster = IsForMaster;
	
}

void CQuestSystem::InsertItem(int iQuestIndex,BYTE bType,BYTE bIndex,BYTE bLevel,BYTE bLuck,BYTE bOptions,BYTE bSkill,BYTE bExcelent)
{
	this->m_QuestItem[iQuestIndex].iQuestIndex = iQuestIndex;
	this->m_QuestItem[iQuestIndex].bType = bType;
	this->m_QuestItem[iQuestIndex].bIndex = bIndex;
	this->m_QuestItem[iQuestIndex].bLevel = bLevel;
	this->m_QuestItem[iQuestIndex].bLuck = bLuck;
	this->m_QuestItem[iQuestIndex].bOptions = bOptions;
	this->m_QuestItem[iQuestIndex].bSkill = bSkill;
	this->m_QuestItem[iQuestIndex].bExcelent = bExcelent;
}


void CQuestSystem::LoadQuest(int aIndex)
{
	GOBJSTRUCT *lpObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int ID = aIndex - MIN_PLAYERID;
	char szQueryBuff[200] = {0};
	char szQueryBuff1[200] = {0};
	char szQueryBuff2[200] = {0};

	wsprintfA(szQueryBuff, "SELECT C_QuestIndex FROM Character WHERE Name = '%s'",lpObj->Name);
	pObjGS[ID].iQuestIndex = SQL.ReturnInt("C_QuestIndex",szQueryBuff);
	wsprintfA(szQueryBuff1, "SELECT C_MonsterCount FROM Character WHERE Name = '%s'",lpObj->Name);
	pObjGS[ID].iMonsterCount = SQL.ReturnInt("C_MonsterCount",szQueryBuff1);
	wsprintfA(szQueryBuff2, "SELECT C_QuestState FROM Character WHERE Name = '%s'",lpObj->Name);
	pObjGS[ID].bQuestState = SQL.ReturnShort("C_QuestState",szQueryBuff2);

}

void CQuestSystem::NPCTalk1(GOBJSTRUCT *lpNpc,int aIndex)
{
	GOBJSTRUCT *lpObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int ID = aIndex - MIN_PLAYERID;
	
	if(this->m_QuestData[pObjGS[ID].iQuestIndex].wLevelReq > lpObj->Level)
	{	
		char msg[200];
		wsprintfA(msg,"You need %d level for quest.",this->m_QuestData[pObjGS[ID].iQuestIndex].wLevelReq);
		ChatTargetSendNogs(lpNpc,msg,aIndex);
		return;
	}

	if(pObjGS[ID].iQuestIndex >= Config.QuestCount&&pObjGS[ID].bQuestState==255)
	{
		QuestSay(aIndex,MSG31,lpObj->Name);
		return;
	}
	
	if(pObjGS[ID].bQuestState == 1)
	{
		this->QuestFinish(aIndex,pObjGS[ID].iQuestIndex,lpNpc);
		return;
	}

	if(pObjGS[ID].bQuestState == 255)
	{
		this->QuestStart(aIndex,pObjGS[ID].iQuestIndex+1,lpNpc);
		return;
	}
	ChatTargetSendNogs(lpNpc,MSG36,aIndex);
}

void CQuestSystem::QuestStart(int aIndex, int QuestId, GOBJSTRUCT *lpNpc)
{
	GOBJSTRUCT *lpObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int ID = aIndex - MIN_PLAYERID;

	SendMail(aIndex,this->m_QuestData[QuestId].szQuestName,this->m_QuestData[QuestId].szQuestInfo);

	pObjGS[ID].iQuestIndex = QuestId;
	pObjGS[ID].bQuestState = 0;
	pObjGS[ID].iMonsterCount = 0;

	Log.outNormal("[%s][%s] [CQuest System] Start Quest [%s]",lpObj->AccountID,lpObj->Name,this->m_QuestData[QuestId].szQuestName);

}

void CQuestSystem::QuestManage(int aIndex,int Monster)
{
	GOBJSTRUCT *lpObj = (GOBJSTRUCT*) OBJECT_POINTER (aIndex);
	int ID = aIndex - MIN_PLAYERID; 
	
	if(Monster>=MIN_PLAYERID&&Monster<=MAX_PLAYERID)
	{
		return;
	}

	if (pObjGS[ID].bQuestState == 0 && pObjGS[ID].iQuestIndex == m_QuestData[pObjGS[ID].iQuestIndex].iQuestIndex && Monster == m_QuestData[pObjGS[ID].iQuestIndex].iMonsterId&&m_QuestData[pObjGS[ID].iQuestIndex].iMapNumber == lpObj->MapNumber )
	{
		if(pObjGS[ID].iMonsterCount<m_QuestData[pObjGS[ID].iQuestIndex].iMonsterCount)
		{
			pObjGS[ID].iMonsterCount++;
		}
		Messages.outNormal(aIndex,"Quest Monster Kill %d/%d",pObjGS[ID].iMonsterCount,this->m_QuestData[pObjGS[ID].iQuestIndex].iMonsterCount);
		if(pObjGS[ID].iMonsterCount == m_QuestData[pObjGS[ID].iQuestIndex].iMonsterCount)
		{
			pObjGS[ID].bQuestState = 1;
			Messages.outOlive(aIndex,MSG26); //~[Quest] : Quest finished now go to Luke in Lorencia!
		}
		//Log.outNormal("[%s][%s] [Quest Sys][%s] Quest Monster Kill %d/%d",lpObj->AccountID,lpObj->Name,this->m_QuestData[lpObj->m_Quest[10]].szQuestName,lpObj->m_Quest[8],this->m_QuestData[lpObj->m_Quest[10]].iMobCount);
		return;

	}

}

void CQuestSystem::QuestUpdateSQL(int aIndex)
{
	char SQLBuff[300] = {0};
	int ID = aIndex - MIN_PLAYERID;
	wsprintfA(SQLBuff,"UPDATE Character SET C_QuestIndex = %d, C_MonsterCount = %d, C_QuestState = %d WHERE Name = '%s'",pObjGS[ID].iQuestIndex,pObjGS[ID].iMonsterCount,pObjGS[ID].bQuestState,GetName(aIndex));
	SQL.DoQuery(SQLBuff);

}

void CQuestSystem::QuestFinish(int aIndex, int QuestId, GOBJSTRUCT *lpNpc)
{
	GOBJSTRUCT *lpObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	//GOBJSTRUCT *lpObjNpc = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int ID = aIndex - MIN_PLAYERID;

	if (pObjGS[ID].iMonsterCount == m_QuestData[pObjGS[ID].iQuestIndex].iMonsterCount && pObjGS[ID].bQuestState == 1)
	{
		ChatTargetSendNogs(lpNpc,MSG37,aIndex);
		if (m_QuestData[pObjGS[ID].iQuestIndex].IsRewardItem == 1)
		{
			unsigned int Item = m_QuestItem[pObjGS[ID].iQuestIndex].bType * 512 + m_QuestItem[pObjGS[ID].iQuestIndex].bIndex;
			BYTE Level = m_QuestItem[pObjGS[ID].iQuestIndex].bLevel;
			BYTE Luck = m_QuestItem[pObjGS[ID].iQuestIndex].bLuck;
			BYTE Options = m_QuestItem[pObjGS[ID].iQuestIndex].bOptions;
			BYTE Skill = m_QuestItem[pObjGS[ID].iQuestIndex].bSkill;
			BYTE Excelent = m_QuestItem[pObjGS[ID].iQuestIndex].bExcelent;
			ItemSerialCreateSend (aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,Item,Level,0,Skill,Luck,Options,aIndex,Excelent,0);

		}
		if (lpObj->Level <Config.MaxLevel)
		{
			lpObj->Experience += m_QuestData[pObjGS[ID].iQuestIndex].iRewardExp;
			lpObj->Level += m_QuestData[pObjGS[ID].iQuestIndex].wRewardLevel;
		}
		if (lpObj->Level == Config.MaxLevel&&m_QuestData[pObjGS[ID].iQuestIndex].IsForMaster==1)
		{
			if (lpObj->MLevel>=1&&lpObj->MLevel<200)
			{
				lpObj->MLExp += m_QuestData[pObjGS[ID].iQuestIndex].iRewardExp;
				lpObj->MLevel += m_QuestData[pObjGS[ID].iQuestIndex].wRewardLevel;
				lpObj->MLPoint += m_QuestData[pObjGS[ID].iQuestIndex].wRewardLevel;
			}
		}
		lpObj->Money += m_QuestData[pObjGS[ID].iQuestIndex].iRewardZen;
		lpObj->LevelUpPoint += m_QuestData[pObjGS[ID].iQuestIndex].iRewardPoints;
		GCLevelUpMsgSend(aIndex,0);
		pObjGS[ID].bQuestState = 255;
		Log.outNormal("[%s][%s] [CQuest System] Finished Quest [%s]",lpObj->AccountID,lpObj->Name,this->m_QuestData[QuestId].szQuestName);
		return;
	}
	else
	{
	
		ChatTargetSendNogs(lpNpc,MSG36,aIndex);
		return;
	}
}

void CQuestSystem::SendMail(int aIndex,char *szQuestName,char *szQuestInfo)
{
	int ID = aIndex - MIN_PLAYERID;

	Messages.outOlive(aIndex,MSG27,this->m_QuestData[pObjGS[ID].iQuestIndex].iQuestIndex+1,szQuestName);
	Messages.outOlive(aIndex,MSG29,GetName(aIndex));
	Messages.outOlive(aIndex,MSG30);
	SQL.SendMail(aIndex,szQuestName,szQuestInfo);
}

