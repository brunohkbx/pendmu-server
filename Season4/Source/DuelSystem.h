/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include <windows.h>



class DuelSystemClass
{
public:
	void Init();
	void DeleteSpectator(DWORD PlayerID, BYTE Room);
	BYTE GetSpectatorPosition(DWORD PlayerID, BYTE Room);
	void SetDuelInfo(DWORD PlayerID, BYTE Room);
	void NPCTalk_GateKeeper(DWORD PlayerID);
	int DuelOK_EnterRoom(DWORD PlayerID1, DWORD PlayerID2);
	void ClearRoom(BYTE Room);
	void ClearRoombyPlayerID(DWORD PlayerID);
	void GladiatorsGloryBuff(DWORD PlayerID);
	void WarpRoom(DWORD PlayerID, BYTE Room);
	BOOL isInDuelRoom(DWORD PlayerID);
	void SendDuelInfo(DWORD PlayerID, BYTE Room);
	BYTE SetSpectator(DWORD PlayerID, BYTE Room);
	void SendEndDuelNotification(DWORD lpObj, char* Winner, char* Looser);

	BOOL DuelRoom[4];
	BOOL DuelRoomTotalScore[4];

	DWORD Player[2][4];
	DWORD Spectator[10][4];
	BOOL isNewSystem;
	int MinLevel;
};



extern DuelSystemClass Duel;
