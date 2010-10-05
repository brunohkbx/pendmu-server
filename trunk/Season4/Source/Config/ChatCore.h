/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "GameServer.h"
#include "StdAfx.h"
#include "Utils.h"




//void ChatDataSend(DWORD gObjId,LPBYTE Protocol);
class cChat
{
private:
	void ChatGlobal(DWORD aIndex,char* msg);
	void ChatAddStats(DWORD aIndex, LPCSTR IpBuffer, BYTE CMD_STATS_TYPE);
	void ChatInfo(DWORD gObjId);
	void ChatReload(DWORD PlayerID,char* msg);
	void ChatSkin(DWORD aIndex,char* msg);
	void OnlineAll(DWORD aIndex);
	void GetTime(DWORD aIndex);
	void FireWork (DWORD aIndex,char * msg);
	void FireworkAll (DWORD aIndex,char * msg);
	void QuestInfo(DWORD aIndex);
	void TestMail(DWORD aIndex);
public:
	void ChatDataSend(DWORD gObjId,LPBYTE Protocol);
};

extern cChat ChatSystem;



//#define gObjGetName(aIndex,gObjNick) ((char *)gObjGetValue(aIndex,gObjNick))



