/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/


//Includes & Defines
#include "StdAfx.h"
#include <process.h>
#include "Common.h"
#include "User.h"

//define for protocol change
//#ifdef GameServer90

#define DataSend ((void(*)(DWORD PlayerID,PBYTE Packet,DWORD Size)) 0x004B3370)
#define DataSendB ((void(*)(DWORD,LPSTR,DWORD)) 0x004B3370)
#define DataRecv ((void(*)(BYTE,PBYTE,DWORD,DWORD,...)) 0x004368E0)
#define DataSendC ((void(*)(int,unsigned char*,int)) 0x004B3370);

#define pMaxLen  (0x1777)
#define gObjCalCharacter ((void(*)(int)) 0x004031A7)
#define GCPkLevelSend ((void(*)(int,unsigned char)) 0x0043C2F0)
#define GetTopHitUser ((DWORD(*)(DWORD)) 0x00403DD2)
#define LogAddFunc ((void(*)(char* Text,int Type)) 0x004C0EB0)
#define NPCTalk ((void(*)(DWORD dwNpcID,char* Text,DWORD PlayerID)) 0x00407347)
#define CGLevelUpPointAdd ((int(*)(BYTE *Arg1,DWORD PlayerID)) 0x004073DD)

#define GameMonsterAllCloseAndReload ((void(*)()) 0x0040759F)
#define gObjViewportListProtocolCreate ((void(*)(gObjStruct*)) 0x0052F870)
#define pReadCommonServerInfo ((void(*)()) 0x00405C6D)
#define pShopDataLoad ((void(*)()) 0x00406B6D)
#define ChaosBoxInit ((void(*) (GOBJSTRUCT*)) 0x00404EDF)
#define GCUserChaosBoxSend ((void(*) (GOBJSTRUCT*, int)) 0x00406FFF)
//#define ChaosBoxInit ((void(*) (int)) 0x00404EDF) MOTHER FUCKER YOU FUCKER ME UP DUDE !!!!
#define gObjInventoryDeleteItem ((void(*)(int,int)) 0x51A3E0)
#define GCInventoryItemDeleteSend ((void(*)(int,int,unsigned char)) 0x00403AE9)
#define GCSendQuestPrize ((int(*)(int, int, int)) 0x00403472)
#define gObjGetItemCountInIventory ((int(*)(int,WORD))0x0040299B)
#define gObjDel ((short (*)(int)) 0x0050A020)
#define GameMonsterAllAdd ((WORD(*)(void)) 0x0056BB20)
#define ItemGetNumberMake ((int(*) (int,int)) 0x00405425)


#define LogAddFuncColor ((void(*) (int, char*)) 0x004C0FA0)
#define SendBarMsg ((void(*)(DWORD,LPSTR,DWORD)) 0x004B3370)
#define gObjTeleport ((void(*)(int, int, int, int))0x00403382)
#define FriendMemoListReq ((void(*)(int)) 0x00472140)
#define GCServerMsgStringSend ((void(*) (char* Text, DWORD PlayerID, int Type)) 0x004066B3)
#define ChatTargetSend ((DWORD(*)(DWORD *, char*, DWORD))0x00439260)
#define ChatTargetSendNogs ((void(*)(LPGOBJSTRUCT,char* Text,DWORD PlayerID)) 0x00438F00)
#define GCMoneySend ((void(*) (DWORD,int)) 0x004075EA)
#define ItemSerialCreateSend ((int(*)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)) 0x00407004)
#define gObjSetMonster ((void(*) (int,int)) 0x0040616D)
#define gObjAddMonster ((int(*) (int)) 0x004044F3) 
#define GCLevelUpMsgSend ((void(*)(int, unsigned char)) 0x0043BDC0)
//#define gObjMonterTopHitDamageUser ((DWORD(*)(DWORD * MonterAddress))0x004074FA)
#define gObjMonterTopHitDamageUser ((DWORD(*)(LPGOBJSTRUCT lpObj))0x004074FA)
#define gObjMoveGate ((void(*)(int, int))0x00405C9A) //Not Used
#define DropItemSend ((void(*)(DWORD *, LPGOBJSTRUCT)) 0x00420330)
#define gObjGameClose ((BOOL(*)(int)) 0x00509940)
//#define gObjItemByteConvert16_JMP ((int(*) (LPBYTE, int, int)) 0x005581B0)

#define MonsterCount 0x7D95B94
#define MonsterReads 0x7D800B6
#define gObjSetMonsters	((void(*)(int,int))0x0040616D)
#define gObjSetPosMonster ((void(*)(int,int))0x00506870)
#define gObjAddMonsters	((int(*)(unsigned char))0x004044F3)
//#define gObjDel ((void (*)(int)) 0x00403AE4)
#define ObjMemFree ((int(*)(int)) 0x0050A2C0)
#define CloseClient ((void(*)(DWORD))0x0040788D)


#define GsgEventMonsterItemDropFunc_Addr ((int(*) ( LPGOBJSTRUCT lpObj ,LPGOBJSTRUCT lpObjOfPlayer)) 0x420330)
#define MonsterItemDrop_Hook 0x402AD1
#define MonsterDie_Hook 0x4184C4  //CAll Funtion MonterDieGiveItem
//#define MonsterDie_Hook 0x4050DD
#define gObjMonsterDieGiveItem ((int(*) ( LPGOBJSTRUCT , LPGOBJSTRUCT )) 0x4050DD )
//#define gObjMonsterDieGiveItem ((int(*) ( LPGOBJSTRUCT , LPGOBJSTRUCT )) 0x41D9E0 )
#define RingDef 0x00406BB3
#define gObjMoveGate_Hook (0x00405C9A)
#define gObjMoveGate_JMP ((int(*)(int, int))0x00532530)
#define gObjNPCRecvTalk01_Hook (0x0044508F)
#define gObjNPCRecvTalk02_Hook (0x004450C0)
#define gObjItemByteConvert16_Hook (0x00401389)
#define ProtocolCore_Offset (0x004038BE)
#define ProtocolCoreSend_Offset (0x004055BF)
#define gObjGameClose_Hook (0x004034B8)
//#define retResistance_Offset (0x00405D26)


#define gObjOffset (*(char**)0x7A5502C)
#define gObjSize 0x2228
#define MIN_PLAYERID 8000
#define MAX_PLAYERID 9000
#define GS_ITEMSIZE 0xBC

//#endif

#define gObjPlayer 0x1F40
#define gObjMaxUsr 0x1CE7 
#define gObj_isonline 0x4
#define gObjMapID 0x131
#define gObjPosX 0x12C
#define gObjPosY 0x12E
#define gObjPk 0x125
#define gObjClass 0xA2
#define gObjLupp 0xAC
#define gObjStr 0xDC
#define gObjDex 0xDE
#define gObjVit 0xE0
#define gObjEne 0xE2
#define gObjLead 0x100
#define gObjLogin 0x6C
#define gObjNick 0x77
#define gObjDir 0x130
#define gObjExp 0xB0
#define gObjNextExp 0xB8
#define gObjZen 0xD8
#define gObjLvl 0xAA //0xA6
#define gObjCtl 0x1F4 // 34 = GM
#define gObjLife 0xE4
#define gObjMaxLife 0xE8
#define gObjAddLife 0x134
#define gObjShield 0x13C
#define gObjMaxShield 0x140
#define gObjAddShield 0x144
#define gObjInventory 0xE7C
#define gObjWarehouse 0xEB4




int gObjGetgObjId(char *CharacterName);
//#define gObjGetValue(aIndex, Offset)	( (*(char**)gObjOffset) + gObjSize*aIndex +Offset )




