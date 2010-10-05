#include "stdafx.h"
#include "CSQL.h"
#include "SQL_Manager.h"
#include "GameServer.h"
#include "Log.h"


SQLClass SQL;
CBoundRecordSet rsSql;
CSQL PointsSql;
SQLCONNECTIONSTRING m_SqlConn;

void SQLClass::Init()
{

	bool bResult = false;
	char SQLConnect[]="..\\OptionsData\\Options.ini";

	if( GetPrivateProfileIntA("SQL", "SQLVersion", 2000, SQLConnect) == 2000 ) {
		strcpy_s(m_SqlConn.sDriver, "{SQL Server}");
	} 
	else {
		strcpy_s(m_SqlConn.sDriver, "{SQL Native Client}");
	}
	

	GetPrivateProfileStringA("SQL", "Host",	"",m_SqlConn.sServer,	sizeof(m_SqlConn.sServer),	SQLConnect);
	GetPrivateProfileStringA("SQL", "Database",		"",m_SqlConn.sDatabase,	sizeof(m_SqlConn.sDatabase),SQLConnect);
	GetPrivateProfileStringA("SQL", "User",	"",m_SqlConn.sUID,		sizeof(m_SqlConn.sUID),		SQLConnect);
	GetPrivateProfileStringA("SQL", "Password",	"",m_SqlConn.sPwd,		sizeof(m_SqlConn.sPwd),		SQLConnect);

	if( PointsSql.Connect(&m_SqlConn) == false ) 
	{
		MessageBoxA(NULL, "g_SQL::Init() Connect to SQL Server false \n chek your setting !", "SQL Error!", MB_OK|MB_ICONERROR);
		ExitProcess(0);
	} 
	else 
	{
		bResult = true;
	}

	if( bResult == true )
	{
		//Log.outInfo("SQL Manager Initialized");
	}
}


char* SQLClass::ReturnString(char *szField,char *szQuery)
{
	static char szRetString[1024];
	PointsSql.Execute(szQuery, &rsSql, true);
	rsSql.Fetch();
	strcpy_s(szRetString,rsSql.Values(szField).ToString());
	rsSql.Close();
	return szRetString;

}
int SQLClass::ReturnInt(char *szField,char *szQuery)
{
	PointsSql.Execute(szQuery, &rsSql, true);
	rsSql.Fetch();
	int value = rsSql.Values(szField).ToIntegerS();
	rsSql.Close();
	return value;
}

short SQLClass::ReturnShort(char *szField,char *szQuery)
{
	PointsSql.Execute(szQuery, &rsSql, true);
	rsSql.Fetch();
	short value = rsSql.Values(szField).ToIntegerS();
	rsSql.Close();
	return value;
}


int SQLClass::GetCountInt(char* Table, const char* Optional, ...)
{
	char Buffer[1024];
	char szQueryBuff[1024];
	va_list pArguments;
    va_start(pArguments, Optional);
    vsprintf(Buffer, Optional, pArguments);
    va_end(pArguments);
    if (Optional)
		wsprintfA(szQueryBuff, "SELECT * FROM %s %s;", Table, Buffer);
    else
		wsprintfA(szQueryBuff, "SELECT * FROM %s;", Table);
	int cc = rsSql.RowCount;
	rsSql.Close();
	ZeroMemory(szQueryBuff,sizeof(szQueryBuff));
	return cc;
}



void SQLClass::DoQuery(char *szQuery)
{
	//PointsSql.Execute(szQuery);
	PointsSql.Execute(szQuery, &rsSql, true);
	rsSql.Close();
}

void SQLClass::SendMail(int aIndex,char *szQuestName,char *szQuestInfo)
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);


	char szQueryBuff[1024];
	char szQueryBuff2[1024];
	char szQueryBuff3[1024];
	unsigned int MailMemoCount;
	unsigned int MailMemoTotal;
	unsigned int MemoGUID;


	wsprintfA(szQueryBuff, "SELECT MAX(MemoCount) AS MemoCount FROM T_FriendMain;");
	PointsSql.Execute(szQueryBuff, &rsSql, true);
	rsSql.Fetch();
	MailMemoCount = rsSql.Values("MemoCount").ToIntegerU();
	rsSql.Close();

	MailMemoCount += 1;


	wsprintfA(szQueryBuff2, "SELECT MemoTotal FROM T_FriendMain WHERE Name = '%s';", gObj->Name);
	PointsSql.Execute(szQueryBuff2, &rsSql, true);
	rsSql.Fetch();
	MailMemoTotal = rsSql.Values("MemoTotal").ToIntegerU();
	rsSql.Close();

	MailMemoTotal += 1;
	

	wsprintfA(szQueryBuff3, "SELECT GUID FROM T_FriendMain WHERE Name = '%s';", gObj->Name);
	PointsSql.Execute(szQueryBuff3, &rsSql, true);
	rsSql.Fetch();
	MemoGUID = rsSql.Values("GUID").ToIntegerU();
	rsSql.Close();
	


	char sSQL[2048] = {0};
	wsprintf(sSQL,"INSERT INTO %s.dbo.T_FriendMail (MemoIndex,GUID,FriendName,wDate,Subject,bRead,Memo,Photo,Dir,Act) VALUES (%d,%d,'Manager',GetDate(),'%s',0,convert(varbinary(1000),'%s'),0x3006FF22222F1FFFC703FC0040F111110000,143,2)",m_SqlConn.sDatabase,MailMemoCount,MemoGUID,szQuestName,szQuestInfo);
	PointsSql.Execute(sSQL, &rsSql, true);
	rsSql.Close();

	char sSQL2[1024] = {0};
	wsprintf(sSQL2,"UPDATE %s.dbo.T_FriendMain SET MemoCount='%d',MemoTotal='%d' WHERE Name='%s'", m_SqlConn.sDatabase,MailMemoCount,MailMemoTotal,gObj->Name);
	PointsSql.Execute(sSQL2, &rsSql, true);
	rsSql.Close();
	//Update Mail
	FriendMemoListReq(aIndex);
	Messages.outOlive(aIndex,"You have new Mail from system");

}

void SQLClass::QuestUpdate(int aIndex,int iKillMob,int iMobCount,char *szQuestName,char *szQuestInfo)
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	
	char szQueryBuff[1024];
	char szQueryBuff2[1024];
	char szQueryBuff3[1024];
	char szQueryBuff4[1024];
	char szQueryBuff5[1024];
	unsigned int MailMemoCount;
	unsigned int MailMemoTotal;
	unsigned int MemoGUID;

	wsprintfA(szQueryBuff, "SELECT MAX(MemoCount) AS MemoCount FROM T_FriendMain");
	PointsSql.Execute(szQueryBuff, &rsSql, true);
	rsSql.Fetch();
	MailMemoCount = rsSql.Values("MemoCount").ToIntegerU();
	rsSql.Close();

	MailMemoCount += 1;
	//Messages.outNormal(aIndex,"MailCount %d",MailMemoCount);

	wsprintfA(szQueryBuff2, "SELECT MemoTotal FROM T_FriendMain WHERE Name = '%s';", gObj->Name);
	PointsSql.Execute(szQueryBuff2, &rsSql, true);
	rsSql.Fetch();
	MailMemoTotal = rsSql.Values("MemoTotal").ToIntegerU();
	rsSql.Close();

	MailMemoTotal += 1;
	//Messages.outNormal(aIndex,"MemoTotal %d",MailMemoTotal);

	wsprintfA(szQueryBuff3, "SELECT GUID FROM T_FriendMain WHERE Name = '%s';", gObj->Name);
	PointsSql.Execute(szQueryBuff3, &rsSql, true);
	rsSql.Fetch();
	MemoGUID = rsSql.Values("GUID").ToIntegerU();
	rsSql.Close();
	//Messages.outNormal(aIndex,"GUID %d",MemoGUID);



	//Send Mail with Quest Info
	char QuestInfo[300];
	wsprintfA(QuestInfo,"Quest completed, go to Quest Manager for reward!");
	wsprintfA(szQueryBuff4, "INSERT INTO %s.dbo.T_FriendMail (MemoIndex,GUID,FriendName,wDate,Subject,bRead,Memo,Photo,Dir,Act) VALUES (%d,%d,'Manager',GetDate(),'%s',0,convert(varbinary(1000),'%s'),0x3006FF22222F1FFFC703FC0040F111110000,143,2)",m_SqlConn.sDatabase,MailMemoCount,MemoGUID,szQuestName,QuestInfo);
	PointsSql.Execute(szQueryBuff4, &rsSql, true);
	rsSql.Close();

	//Update Mail Count
	wsprintfA(szQueryBuff5, "UPDATE %s.dbo.T_FriendMain SET MemoCount='%d',MemoTotal='%d' WHERE Name='%s'",m_SqlConn.sDatabase,MailMemoCount,MailMemoTotal,gObj->Name);
	PointsSql.Execute(szQueryBuff5, &rsSql, true);
	rsSql.Close();
	
	//Update Mail
	FriendMemoListReq(aIndex);

}
