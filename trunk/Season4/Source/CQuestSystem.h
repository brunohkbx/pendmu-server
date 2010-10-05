#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "User.h"

#define MAX_QUESTS 201 //Array Start From 0, and Quest Number Start From 1, 201 mean 200 Quests

struct QUESTINFODATA
{
int iQuestIndex;
char szQuestName[100];
char szQuestInfo[100];
BYTE IsRewardItem;
unsigned int iRewardZen;
WORD wRewardLevel;
unsigned int iRewardExp;
int iRewardPoints;
int iMonsterId;
int iMonsterLevel;
int iMapNumber;
WORD wLevelReq;
int iMonsterCount;
BYTE IsForMaster;
};

struct QUESTITEMDATA
{
	int iQuestIndex;
	BYTE bType;
	BYTE bIndex;
	BYTE bLevel;
	BYTE bLuck;
	BYTE bOptions;
	BYTE bSkill;
	BYTE bExcelent;
};
class CQuestSystem
{
public:
	void Init();
	void LoadFile(char *filename);
	void Insert(int iQIndex,BYTE IsRewardItem,unsigned int iRewardZen,WORD wRewardLevel,unsigned int iRewardExp,int iRewardPoints,int iMonsterId,int iMonsterLevel,int iMapNumber,WORD wLevelReq,int iMonsterCount,BYTE IsForMaster, char *szQuestName,char *szQuestInfo);
	void InsertItem(int iQuestIndex,BYTE bType,BYTE bIndex,BYTE bLevel,BYTE bLuck,BYTE bOptions,BYTE bSkill,BYTE bExcelent);
	void LoadQuest (int aIndex);
	void NPCTalk1(GOBJSTRUCT *lpNpc,int aIndex);
	void QuestStart(int aIndex,int QuestId,GOBJSTRUCT *lpNpc);
	void QuestManage(int aIndex,int Monster);
	void QuestFinish(int aIndex,int QuestId,GOBJSTRUCT *lpNpc);
	void QuestUpdateSQL(int aIndex);
	void SendMail(int aIndex,char *szQuestName,char *szQuestInfo);
	QUESTINFODATA m_QuestData[MAX_QUESTS];
	QUESTITEMDATA m_QuestItem[MAX_QUESTS];

}; 
extern CQuestSystem g_Quest;

void SendMail(int aIndex,char *szQuestName,char *szQuestInfo);

