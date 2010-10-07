/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include <windows.h>
#include "SQL_Manager.h"
#include <vector>
#include "User.h"



typedef struct PCShopItemConfig
{	
	int ItemIndex;
	int ItemID;	
	int X;
	int Y;
	int Skill;
	int Level;
	int Luck;
	int Opt;
	int Dur;
	int Exc;

	int NewOpt1;
	int NewOpt2;
	int NewOpt3;
	int NewOpt4;
	int NewOpt5;

	int SlotX;
	int Cost;
}PCShopItemStruct;

typedef struct PCShopMobPoints
{	
	int MobID;
	int Points;	
}PCShopMobPointsStruct;

class PCPointShop
{
public:
	UINT ReadFile();
	int CalcItemXY(int X,int Y);
	int MakePacket();
	void Init();
	void OpenShop(DWORD PlayerID);
	void BuyItem(DWORD PlayerID,int Position);
	void GetInfo(DWORD PlayerID);
	void SQLSetStatus(DWORD PlayerID);
	void IncreasePoints(DWORD PlayerID,int Points);
	void DecreasePoints(DWORD PlayerID,int Points);
	void LevelUp(DWORD PlayerID, int MobID);

	//Vars
	BOOL IsPCPointSystem;
	BYTE PCPointPacket[4680];
	BYTE PC_Shop[0x78];
	PCShopItemStruct Items[120];
	PCShopMobPointsStruct pPCMobPoint[512];
	int OnlyForGM;
	int AddWhenKillMobs;
	int SQLGetPoints(DWORD PlayerID);
private:
	unsigned int MaxPlayerPoints;
	int HowManyItems;
	int MobPointRecords;
	int PacketSizes;
	int SearchIndex(int Position);
	int GetRewardPoints(int MobID);
};

extern PCPointShop PCPoint;