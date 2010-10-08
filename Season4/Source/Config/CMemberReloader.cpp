#include "StdAfx.h"
#include "Log.h"
#include "CMemberReloader.h"

int bIsVipServer = GetPrivateProfileInt("GameServerCustom","bIsVipServer",0,".//ConnectMember.ini");

void ConnectMemberLoad(char * File)
{
	_asm
	{
		PUSH File
		MOV ECX, gDirPath
		MOV EDI,CConMember__Load_Offset
		CALL EDI
	}
	Log.outInfo("ConnectMember.txt Reloaded");
}
void ConnectMemberReloader(void * lpParams)
{
	int Mins	= GetPrivateProfileInt("GameServerCustom", "CMemberReloadMins", 20, ".\\RPG.ini");
	int Secs	= (Mins * 60) * 1000;
	if(bIsVipServer == 1)
	{
		while(true)
		{
			Sleep(Secs);
			ConnectMemberLoad("..\\Data\\ConnectMember.txt");
		}
	}
	_endthread();

}
bool Structs(char* ini)
{
	bIsVipServer = GetPrivateProfileInt("GameServerCustom","CMemberReloadActive",0,ini);

	return true;
}