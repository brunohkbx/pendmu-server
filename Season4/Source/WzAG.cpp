/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
//#include <windows.h>
#include "offsets.h"
#include "Protocols.h"
#include "Global.h"
#include "GameServer.h" 
#include "Utils.h"
#include "Fixs.h"
#include "ChatCore.h"
#include "Log.h"
#include "ItemDropRate.h"
//#include "DropItem.h"
//#include "EventItemBags.h"
#include "WzAG.h"
#include "Maps.h"
#include "DuelSystem.h"
#include "SQL_Manager.h"
#include "Global.h"
#include "PCPoints.h"
#include "NPC.h"
#include "EventItemBag13.h"
#include "Structure.h"
#include "Monster.h"
#include "Security.h"
#include "CQuestSystem.h"


DROPRATES					DropRateConfig[1000]; 
BOOL						bDropRateConfig;
PlayerOBJ					pObjGS[MAX_PLAYERID-MIN_PLAYERID];
PCPointShop					PCPoint;


void MakeDir()
{
	_mkdir("POST_LOG");
	_mkdir("LOG");
		
}
void GS()
{
	//SQL Connection
	SQL.Init();
	
	
		InitProto();
#ifdef GameServer90
		//GetQueComplStatusFix
		BYTE QueCompletionStat[] = { 0xFF, 0x25, 0x00, 0xB5, 0x71, 0x00, 0x90, 0x90, 0x90 };
		memcpy((int*)0x004B1D9E,QueCompletionStat,sizeof(QueCompletionStat));
		*(unsigned int*)0x0071B500  = (unsigned int)GetQueComplStatusFix;
#endif
        
		_asm
		{
			//Item Reward From ItemDropRate.txt
			pushad	

			mov eax,MonsterItemDrop_Hook+1
			mov ecx,offset gEventMonsterItemDrop
			sub ecx,MonsterItemDrop_Hook+5
			mov [eax],ecx

			//Monster Die

			mov eax,MonsterDie_Hook+1
			mov ecx, offset MonsterDie
			sub ecx,MonsterDie_Hook+5
			mov [eax], ecx

			// NPC Hook
			mov eax, gObjNPCRecvTalk01_Hook+1
			mov ecx, offset NpcRecvTalk
			sub ecx, gObjNPCRecvTalk01_Hook+5
			mov [eax], ecx

			mov eax, gObjNPCRecvTalk02_Hook+1
			mov ecx, offset NpcRecvTalk
			sub ecx, gObjNPCRecvTalk02_Hook+5
			mov [eax], ecx

			//Out Game Or save Data Item Hook
			mov eax, gObjGameClose_Hook+1 //gObjItemByteConvert16
			mov ecx, offset gObjGameClose_Func
			sub ecx, gObjGameClose_Hook+5
			mov [eax], ecx

			//Hook EventItemBag13 (Ring Warior 40 Fixs)
			mov eax,RingDef+1
			mov ecx,offset RingEventItemBoxOpen
			sub ecx,RingDef+5
			mov [eax],ecx
			
			//New Move Gate
			mov eax, gObjMoveGate_Hook+1
			mov ecx, offset MoveGate_Hook
			sub ecx, gObjMoveGate_Hook+5
			mov [eax], ecx

			popad
		}
		
		//LoadBags();
//		ItemDropRate(0,0,"ItemDropRate.txt");
		HookThis((DWORD)&ProtocolCore,ProtocolCore_Offset);
		HookThis((DWORD)&ProtocolCoreSend,ProtocolCoreSend_Offset);
		//HookThis((DWORD)&retResistance,retResistance_Offset);
		//HookThis((DWORD)&MyGEventMonsterItemDropCR,MonsterItemDrop_Hook);
		//HookThis((DWORD)&ItemByteConvert16,gObjItemByteConvert16_Hook);
		//Functions Hook
		//HookThis(GET_ADDR(OnCharacterLeaveGame), 0x00404264);
		
}



//Funtion Load DLL 
extern "C" _declspec(dllexport) void Load()
{
	DWORD OldProtect;
	if(VirtualProtect(LPVOID(GS_BASE),3604479,PAGE_EXECUTE_READWRITE,&OldProtect))//3543191 
	{
		CheckMAC();
		//SetUp console
		LoadIni(); //Load Ini config
		IniciaIni(); //Load Ini config
		MakeDir(); //Make Important Folder
		conLog.InitCore(); //Setup Console
		PartyZenBugFix (); // PartyZen Fixs
		GS(); //Start GS Hook
		Fixs(); //Start Fixs
		//MapInit(); //Setup Map add
		ItemDropRate(0,0,"..\\OptionsData\\ItemDropRate.txt"); //Load ItemDropRate System & Start
		PCPoint.Init(); //Setup PCPoints
		GoldenArcherInit(0,0,"..\\OptionsData\\GoldenArcher.txt"); //Read Golden Archer Config
		Duel.Init(); //Setup Duel
		Read13thItemBag(); //Fixs Ring 40
		g_Quest.LoadFile("..\\OptionsData\\QuestSystem.txt");
		
	}
	else
	{
		MessageBoxA(0, "Error with server file. Can't Init Custom Modification", "--::Syrius DLL::--", MB_OK | MB_ICONSTOP);
	}
}



				
