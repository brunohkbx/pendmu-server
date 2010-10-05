/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/


//Includes & Defines
#include "StdAfx.h"
#include "GameServer.h"
#include "User.h"



#define GET_ADDR(_func) ((DWORD)&_func)

void LogLine(char*formatstring, ...);
void ToHex(unsigned char* out,unsigned char* data,int c_len);

void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset);
void SetNop(DWORD dwOffset,int Size);
void SetRetn(DWORD dwOffset);
void SetByte(DWORD dwOffset,BYTE btValue);


//Defines
bool VerifyGM(DWORD gObjId);
DWORD gObjByNick(char* nick);
void *GetPlayerAddress(unsigned int PlayerID);
void gObj_GetNick (DWORD gObjId,char*nick);
void gObj_GetLogin(WORD gObjId,char* login);
DWORD gObj_GetMoney(WORD gObjId);
WORD gObj_GetLevel(DWORD PlayerID);
DWORD gObj_GetLevelUpPoints(WORD gObjId);
char gObj_GetMap(WORD gObjId);
char gObj_GetPosX(WORD gObjId);
char gObj_GetPosY(WORD gObjId);
int GetPlayerClass(DWORD PlayerID);
void gObj_Write(int PlayerID,int gObjParam,long int Value);
long int gObj_GetInt(int PlayerID,int gObjParam);

char* gObj_GetChar(int PlayerID,int gObjParam);
bool gObjIsConnected(DWORD wId);
bool gObjIsNConnected(DWORD wId);
//void DataSendAll(unsigned char* Packet,int Lenght);
#define DataSendAll ((void(*)(PBYTE lpMsg, int iMsgSize)) 0x0040729D)
void ServerMsgSend(DWORD wId,int Type,char Sender[20],const char* Message,...);
void GCServerMsgSend(const char* Message,DWORD wId,int Type);
void AllServerMsgSend(char *message, ...);
void NPCSay(DWORD PlayerID,DWORD iNpcID,char* Text);
unsigned char Role (unsigned char range);
void SendBarMessage(DWORD PlayerID, int Color, LPCTSTR szText);
void HookProc(DWORD OriginalOffset, DWORD DestOffset);
void WriteMemoryInt(DWORD Offset, DWORD bValue, DWORD bValueMax, DWORD OffsetLen);




WORD gObj_GetStr(DWORD PlayerID);
WORD gObj_GetAgi(DWORD PlayerID);
WORD gObj_GetVit(DWORD PlayerID);
WORD gObj_GetEne(DWORD PlayerID);
WORD gObj_GetLead(DWORD PlayerID);
WORD gObj_GetPoints(DWORD PlayerID);

void *gObj_GetNickDuel (DWORD gObjId);


void CallSkillEffect(DWORD PlayerID,BYTE Skill, BYTE Status,DWORD MobID,int isSkill);
void CallSkillEffectToMap(DWORD PlayerID,BYTE Skill, BYTE Status,DWORD MobID,int isSkill);

extern void DataSendToMap ( int PlayerID , PBYTE Protocol , DWORD ProtocolLen);
extern void DataSendAllNear ( int PlayerID , PBYTE Protocol , DWORD ProtocolLen, int dist);

int MonsterAddAndSpawn(WORD Monster,BYTE Map,BYTE X, BYTE Y);

int DelPlayerItemLevel ( DWORD PlayerID, DWORD itemId, WORD ItemLevel );
int DelPlayerCantItemsSpecific ( DWORD PlayerID, DWORD itemId, int CANT );
int GetItemInLocation ( DWORD PlayerID, BYTE Location);
void MyGEventMonsterItemDrop ( DWORD * b_MonsterDataAddr,LPGOBJSTRUCT lpObjOfPlayer);
void __cdecl MonsterDie(LPGOBJSTRUCT lpObjOfMonster, LPGOBJSTRUCT lpObjOfPlayer);
void NpcRecvTalk(DWORD * pObjAddressOfNPC, char* pstrTalkOfNPC, DWORD PlayerID);
void StringSendToMap(char*Text,int Map,int type);
UINT GetKind(DWORD MobID);
LPSTR GetName(DWORD PlayerID);

int OnCharacterLeaveGame(int aIndex);
bool IsOnGame(int iIndex);
void SendNoticeToAll(char * Notice);
void Set_ExtraItemDropRate(DWORD PlayerID,int ExtraItemDrop);
void Set_ExtraExpRate(DWORD PlayerID,int ExtraExp);
int Random(int min,int max) ;

//void __cdecl ItemByteConvert16(LPBYTE buf, int pOBJ_INV, int maxitem);

void DataSendNear (int Map,int X,int Y, PBYTE Protocol , DWORD ProtocolLen, int dist);
void QuestSay(int aIndex,const char *Format,...);