#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SQLClass
{
public:
	void Init();
	char* ReturnString(char *szField,char *szQuery);
	int ReturnInt(char *szField,char *szQuery);
	short ReturnShort(char *szField,char *szQuery);
	int GetCountInt(char* Table, const char* Optional, ...);
	void DoQuery(char *szQuery);
	void SendMail(int aIndex,char *szQuestName,char *szQuestInfo);
	void QuestUpdate(int aIndex,int iKillMob,int iMobCount,char *szQuestName,char *szQuestInfo);
};
extern SQLClass SQL;