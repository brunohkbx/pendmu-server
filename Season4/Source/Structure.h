/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include <vector>
#include <windows.h>
#include "Common.h"

//#define GET_USER_INDEX(_AINDEX) ( 9000 - _AINDEX )

DWORD gObjByWarehouse ( int rinv );
DWORD gObjByInventory ( int rinv );
//PCPoints
struct PCPOINTS{
	unsigned short PCPoints;
	short	sPoints[9000 - 8000];
	short	isUseCmd[9000 - 8000];
	
};

struct Arena
{
	//PCPoints
	PCPOINTS PCPoints;
	int MaxLevel;

	//Add Command
	int IsAdd;
	int AddMaxPoints;
	int AddLevel;
	unsigned long AddCost;

	//Post Command
	int IsPost;
	int PostLevel;
	unsigned long PostCost;

	//Reload Command
	int IsReload;

	//Skin Cmd
	int IsSkin;
	int IsOnlyGMSkin;
	int SkinLevel;

	//Protocol
	int IsProtocol;

	//Golden Archer Event
	int IsGADrop;
	int GANeedRena;
	int GAItemscount;

	//Custom Quest
	int QuestCount;


};

void __cdecl MoveGate_Hook(DWORD PlayerID, UINT GateNum);
//int retResistance(LPGOBJSTRUCT lpObj, int Resistance_Type);
void InitProto(void);
extern Arena Config;