/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "Utils.h"
#include "Log.h"
#include "configs.h"
#include "User.h"
#include "DuelSystem.h"
#include "Structure.h"
#include "SQL_Manager.h"
#include "NPC.h"
#include "PCPoints.h"


void LogLine(char *formatstring,...)
{
	va_list args;
	va_start(args,formatstring);
	char msg[0x1770];
	memset(msg,0,sizeof(msg));
	FILE *logfile = fopen(".\\LOG\\Phoenix.log","a+");
	_vsnprintf(msg,sizeof(msg),formatstring,args);
	fputs(msg,logfile);
	fclose(logfile);
}

#ifdef Season5
int IsExistWingItem(int aIndex)
{
 DWORD pInvOffset = *LPDWORD((*(char**)0x7A5502C)+0x2228*aIndex+0xE7C);
 return *LPDWORD(pInvOffset + 0x52A);
}

int IsExistPetItem(int aIndex)
{
 DWORD pInvOffset = *LPDWORD((*(char**)0x7A5502C)+0x2228*aIndex+0xE7C);
 return *LPDWORD(pInvOffset + 0x5E6);
}
unsigned char Role(unsigned char range)
{

	srand(static_cast<int>(time(NULL)));
	return (rand() % range);

}

//CM +15 and other mixes:)
int gObjGetItemCountInChaosbox(int aIndex, short type) {
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	int count = 0;

	for(unsigned i = 0; i < 32; i++)
	{
		if(gObj->pChaosBox[i].m_Type == type)
			count++;
	}

	return count;
}



#endif

void ToHex(unsigned char* out,unsigned char* data,int c_len)
{
	string s,t;
	char cBuff[5001];
	c_len = c_len & 0xFF;
	memset(cBuff,0,5000);
	for(int i=0;i<c_len;i++)
	{
		wsprintf(cBuff+(i*3),"%02X,",data[i]);
	}
	strcat(cBuff,"\r\n");
	memcpy(out,cBuff,(c_len*3)+2);
}

void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset-(dwJmpOffset+5);
}

void SetNop(DWORD dwOffset,int Size)
{
	for(int n=0;n<Size;n++)
	{
		*(BYTE*)(dwOffset+n) = 0x90;
	}
}

void SetRetn(DWORD dwOffset)
{
	*(BYTE*)(dwOffset) = 0xC3;
}

void SetByte(DWORD dwOffset,BYTE btValue)
{
	*(BYTE*)(dwOffset) = btValue;
}

//Verify GM
bool VerifyGM(DWORD gObjId)
{
	
	if(*(short int*)(gObjId*gObjSize+gObjOffset+gObjCtl)==34)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Return index of char
DWORD gObjByNick(char* nick)
{
	for(DWORD i=gObjPlayer;i<gObjMaxUsr;i++)
	{
		char* Name=(char*)(gObjOffset+(gObjSize*i)+gObjNick);
		if(memcmp(nick,Name,10)==0)
		{
			return i;
		}
	}
	return 0xFFFF;
}

//Deinfe of char
void *GetPlayerAddress(unsigned int PlayerID)
{
	return(void*)(gObjOffset+(PlayerID*gObjSize));
}

//Get Login
void gObj_GetLogin(WORD gObjId,char* login)
{
	memcpy(login,(char*)(gObjOffset+(gObjSize*gObjId)+gObjLogin),10);
}

//Get Money
DWORD gObj_GetMoney(WORD gObjId)
{
	return *(DWORD*)(gObjOffset+(gObjSize*gObjId)+gObjZen);
}

//Get level of char
WORD gObj_GetLevel(DWORD PlayerID)
{
	BYTE *Player = (BYTE*)GetPlayerAddress(PlayerID);
	WORD level=0;
	memcpy(&level,Player+gObjLvl,sizeof(WORD));
	return level;
}

//Level up points
DWORD gObj_GetLevelUpPoints(WORD gObjId)
{
	return *(DWORD*)(gObjOffset+(gObjSize*gObjId)+gObjLupp);
}

//Get Map
char gObj_GetMap(WORD gObjId)
{
	char* map=(char*)(gObjOffset+(gObjSize*gObjId)+gObjMapID);
	return *map;
}

//Get Pos X
char gObj_GetPosX(WORD gObjId)
{
	char* PosX=(char*)(gObjOffset+(gObjSize*gObjId)+gObjPosX);
	return *PosX;
}

//Get Pos Y
char gObj_GetPosY(WORD gObjId)
{
	char* PosY=(char*)(gObjOffset+(gObjSize*gObjId)+gObjPosY);
	return *PosY;
}

//Get Player Class
int GetPlayerClass(DWORD PlayerID)
{
	BYTE *Player=(BYTE*)GetPlayerAddress(PlayerID);
	BYTE Class=0;
	memcpy(&Class,Player+gObjClass,sizeof(BYTE));
	return Class;
}

//Write
void gObj_Write(int PlayerID,int gObjParam,long int Value)
{
*(long int*)(PlayerID*gObjSize+gObjOffset);
}

//Get Int
long int gObj_GetInt(int PlayerID,int gObjParam)
{
	return *(long int*)(PlayerID*gObjSize+gObjOffset+gObjParam);
}

//Get name character
void gObj_GetNick (DWORD gObjId,char*nick)
{
memcpy (nick,(char*)(gObjOffset+(gObjSize*gObjId)+gObjNick),11);

}


//Get Char
char* gObj_GetChar(int PlayerID,int gObjParam)
{
	return (char*)(PlayerID*gObjSize+gObjOffset+gObjParam);
}

//Verify is connected
bool gObjIsConnected(DWORD wId)
{
	gObj_GetNick(wId,Character);
	if(wId<8000||wId>9000)return false;
	DWORD Status=gObj_GetInt(wId,gObj_isonline);
	if(Status>=3 && strcmpi(Character,"GoldenBudg")!=0)return true;
	return false;
}

//Send data
//void DataSendAll(unsigned char* Packet,int Lenght)

//{
//	for(int i=6400;i<7400;i++)
//	if(gObjIsConnected(i))
//	DataSend(i,Packet,Lenght);
//}

//Send Server Msg
void GCServerMsgSend(const char* Message,DWORD wId,int Type)
{	
	BYTE *Packet;
	Packet = (BYTE*)malloc(200);
	memset(Packet,0x00,200);
	*Packet=0xC1;

	if(Type==1){
		*(Packet+2)=0x00;}
	else if(Type==2){
		*(Packet+2)=0x02;}

	memcpy((Packet+13),Message,strlen(Message));
	
	int Len=(strlen(Message)+0x13);
	*(Packet+1)=Len;
	
	DataSend(wId,Packet,Len);
	free(Packet);
}
void AllServerMsgSend(char *message, ...) 
{
	for(int i = MIN_PLAYERID; i < MAX_PLAYERID; i++)
	{
		GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == 3)
			GCServerMsgStringSend(message, i, 0);
	}
}
void SendBarMessage(DWORD PlayerID,int Color,LPCTSTR szText)
{
	#define	MAX_PACKET_LEN		0xFF

	BYTE buff[MAX_PACKET_LEN-0x0e];
	FillMemory(buff,(MAX_PACKET_LEN-0x0e),0x20);
	BYTE Len=(BYTE)strlen(szText);

	buff[0]=0xC1;
	buff[1]=Len+0x0E;
	buff[2]=0x0D;
	buff[3]=0x0A;
	buff[4]=0x01;
	buff[5]=0x01;
	buff[6]=0x00;
	buff[7]=0x00;

	switch(Color){
	case 1: // Vermelhor
		buff[8]		=	255; //R
		buff[9]		=	0;	 //G
		buff[10]	=	0;	 //B	
		break;
	case 2:
		buff[8]		=	0;	 //R
		buff[9]		=	255; //G
		buff[10]	=	0;   //B
		break;
	case 3:
		buff[8]		=	255; //R
		buff[9]		=	0;	 //G
		buff[10]	=	0;	 //B
		break;
	case 4:
		buff[8]		=	0;
		buff[9]		=	255;
		buff[10]	=	255;		
		break;
	case 5:
		buff[8]		=	255;
		buff[9]		=	0;
		buff[10]	=	255;		
		break;
	case 6:
		buff[8]		=	255;
		buff[9]		=	255;
		buff[10]	=	0;		
		break;
	case 7:
		buff[8]		=	255;
		buff[9]		=	255;
		buff[10]	=	255;		
		break;
	default:
		buff[8]		=	255;
		buff[9]		=	255;
		buff[10]	=	255;		
		break;
	}

	buff[11]=0xFF;
	buff[12]=0x14;

	strncpy((char*)&buff[0x0d],szText,Len);

	buff[Len+0x0d]=0;

	SendBarMsg(PlayerID,(LPSTR)buff,buff[1]);
}

void ServerMsgSend(DWORD wId,int Type,char Sender[20],const char* Message,...)
{
	char szBuffer[1024];
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(szBuffer,Message,pArguments);
	va_end(pArguments);

		//Packet 1
	BYTE *Packet;
	Packet = (BYTE*)malloc(200);
	memset(Packet,0x00,200);
	*Packet=0xC1;

	if(Type)
	{
		*(Packet+2)=0x02;
	}
	else
	{
		*(Packet+2)=0x00;
	}
	memcpy((Packet+3),Sender,strlen(Sender));
	memcpy((Packet+13),szBuffer,strlen(szBuffer));
	
	//Packet 1
	int Len=(strlen(szBuffer)+0x13);
	*(Packet+1)=Len;
	
	if(!wId)
	{	
		DataSendAll(Packet,Len);
	}
	else if(gObjIsConnected(wId))
	{
		DataSend(wId,Packet,Len);
	}
	free(Packet);
}

void NPCSay(DWORD PlayerID,DWORD iNpcID,char *Text)
{
	DWORD cNpcID = (DWORD)GetPlayerAddress(iNpcID);
	NPCTalk(cNpcID,Text,PlayerID);
}


unsigned char Role(unsigned char range) {
	srand(static_cast<int>(time(NULL)));
	return (rand() % range);
}




WORD gObj_GetStr(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level, Player+gObjStr, sizeof(WORD));
return level;
}
WORD gObj_GetAgi(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level, Player+gObjDex, sizeof(WORD));
return level;
}
WORD gObj_GetEne(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level, Player+gObjEne, sizeof(WORD));
return level;
}
WORD gObj_GetVit(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level, Player+gObjVit, sizeof(WORD));
return level;
}
WORD gObj_GetLead(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level, Player+gObjLead, sizeof(WORD));
return level;
}

WORD gObj_GetPoints(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level, Player+gObjLupp, sizeof(WORD));
return level;
}

void *gObj_GetNickDuel (DWORD gObjId)
{
	return(char*)(gObjOffset+(gObjSize*gObjId)+gObjNick);
}

//Extra

void CallSkillEffectToMap(DWORD PlayerID,BYTE Skill, BYTE Status,DWORD MobID,int isSkill)
{
	if(isSkill==1)
	{
		BYTE pNewProtocol[7]={0xC1,0x07,0x07,Status,HIBYTE(MobID),LOBYTE(MobID),Skill};
		DataSendToMap(PlayerID,pNewProtocol,pNewProtocol[1]);
	}else if(isSkill==2)
	{
		char sBuff[9] = {0xC1, 0x09, 0x2D, 0x00, 0x01, 0x00, Skill, 0x00, Status};
		DataSend(PlayerID,(PBYTE)sBuff,sBuff[1]);
	}
}

void CallSkillEffect(DWORD PlayerID,BYTE Skill, BYTE Status,DWORD MobID,int isSkill)
{
	if(isSkill==1)
	{
		BYTE pNewProtocol[7]={0xC1,0x07,0x07,Status,HIBYTE(MobID),LOBYTE(MobID),Skill};
		DataSendAllNear(PlayerID,pNewProtocol,pNewProtocol[1],16);
	}else if(isSkill==2)
	{
		char sBuff[9] = {0xC1, 0x09, 0x2D, 0x00, 0x01, 0x00, Skill, 0x00, Status};
		DataSend(PlayerID,(PBYTE)sBuff,sBuff[1]);
	}
}

void DataSendToMap ( int PlayerID , PBYTE Protocol , DWORD ProtocolLen)
{
	BYTE *me_map  = (BYTE*) ((PlayerID * gObjSize) + (gObjOffset + gObjMapID));
	for ( int i = MIN_PLAYERID ; i < MAX_PLAYERID ; i ++ )
	{
		BYTE *map  = (BYTE*) ((i * gObjSize) + (gObjOffset + gObjMapID));
		if (*map == *me_map)
		{
			DataSend(i,(PBYTE)Protocol,ProtocolLen);
		}
	}
}

void DataSendAllNear ( int PlayerID , PBYTE Protocol , DWORD ProtocolLen, int dist)
{
	BYTE *me_map  = (BYTE*) ((PlayerID * gObjSize) + (gObjOffset + gObjMapID));
	BYTE *me_posx = (BYTE*) ((PlayerID * gObjSize) + (gObjOffset + gObjPosX));
	BYTE *me_posy = (BYTE*) ((PlayerID * gObjSize) + (gObjOffset + gObjPosY));
	for ( int i = MIN_PLAYERID ; i < MAX_PLAYERID ; i ++ )
	{
		BYTE *map  = (BYTE*) ((i * gObjSize) + (gObjOffset + gObjMapID));
		BYTE *posx = (BYTE*) ((i * gObjSize) + (gObjOffset + gObjPosX));
		BYTE *posy = (BYTE*) ((i * gObjSize) + (gObjOffset + gObjPosY));
		if (*map == *me_map)
		{
			if (( *posx <= *me_posx + dist) && (*posx >= *me_posx - dist ))
			{
				if (( *posy <= *me_posy + dist) && (*posy >= *me_posy - dist ))
				{
					DataSend(i,(PBYTE)Protocol,ProtocolLen);
				}
			}
		}
	}
}

int MonsterAddAndSpawn(WORD Monster,BYTE Map,BYTE X, BYTE Y)
{
	int MobCount = *(DWORD *)(MonsterCount);
	
	if((MobCount + 1) < MIN_PLAYERID)
	{
		MobCount++;
		*(DWORD *)(MonsterCount) = MobCount;
		*(WORD *)(12 * MobCount + MonsterReads) = Monster;
		*(BYTE *)(12 * MobCount + MonsterReads+2) = Map;
		*(BYTE *)(12 * MobCount + MonsterReads+3) = 30;
		*(BYTE *)(12 * MobCount + MonsterReads+4) = X;
		*(BYTE *)(12 * MobCount + MonsterReads+5) = Y;
		*(BYTE *)(12 * MobCount + MonsterReads+6) = 2;
		*(BYTE *)(12 * MobCount + MonsterReads+7) = X;
		*(BYTE *)(12 * MobCount + MonsterReads+8) = Y;

		int MobID = gObjAddMonsters(*(BYTE *)(12 * MobCount + (MonsterReads+2)));
		if(MobID>=0)
		{
			int MobNr = *(WORD *)(12 * MobCount + MonsterReads);
			gObjSetPosMonster(MobID, MobCount);
			gObjSetMonsters(MobID, MobNr);
		}

		return MobID;
	}
	else
	{		
		MessageBox(NULL,"Monster attribute max over!!", "Monsters overflow", 0);
		return -1;
	}
}

int GetItemInLocation ( DWORD PlayerID, BYTE Location)
{
	DWORD * inv = (DWORD*) ( gObjOffset + ( gObjSize * PlayerID) + gObjInventory );

	WORD * pitemId = (WORD*) ( ( Location * GS_ITEMSIZE ) + *inv + 6 );
	
	if ( *pitemId >= 9000 )
	{
		return -1;
	}
	return *pitemId;
}

UINT GetKind(DWORD MobID)
{
	UINT result=0;
	if ((MobID>=0)&&(MobID<MIN_PLAYERID))
	{
		result=gObj_GetInt(MobID,0xA4);
	}
	return result;
}



void NpcRecvTalk(DWORD * pObjAddressOfNPC, char* pstrTalkOfNPC, DWORD PlayerID)
{
	char sTalkBuf[1000] = {0};
	int Npc=(int)pObjAddressOfNPC[0];
	int NpcKind=GetKind(Npc);

	switch(NpcKind)
	{
	//case 236: //Golden Archer
	//	NPCGoldenArcher(PlayerID);
	//	return;
	//	break;

	case 479: //Gate Keepper
		Duel.NPCTalk_GateKeeper(PlayerID);
		return;
		break;
	//case 465:
	//	SantaClaus(PlayerID);
	//	return;
	//	break;

	}
	ChatTargetSend(pObjAddressOfNPC, sTalkBuf, PlayerID);
}

void StringSendToMap(char*Text,int Map,int type)
{
	for (int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
	{
		if(gObjIsConnected(i) && gObj_GetMap(i) == Map)
		{
			GCServerMsgStringSend(Text,i,type);
		}
	}
}

LPSTR GetName(DWORD PlayerID)
{
	LPSTR result=" ";
	if ((PlayerID>=MIN_PLAYERID)&&(PlayerID<MAX_PLAYERID))
	{
		GOBJSTRUCT *pObj = (GOBJSTRUCT*)(PlayerID*gObjSize + gObjOffset);
		result=pObj->Name;
	}
	return result;
}

//When user exit game
int OnCharacterLeaveGame(int aIndex) {
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int ID=aIndex-MIN_PLAYERID;
	//Update PCPoints
	char szQuery[255];
	wsprintfA(szQuery,"UPDATE MuOnline.dbo.Character SET PcPoints = '%d' WHERE Name = '%s'",Config.PCPoints.sPoints[ID],gObj->Name);
	SQL.DoQuery(szQuery);

	return ObjMemFree(aIndex);
}

bool IsOnGame(int iIndex)
{
	if ((iIndex>=MIN_MONSTERID)&&(iIndex<MAX_PLAYERID))
	{
		LPGOBJSTRUCT pObj = (LPGOBJSTRUCT)(iIndex*gObjSize + gObjBaseAddr);
		if (pObj->Connected==3)
		{
			return true;
		}else{
			return false;
		}
	} else {
		return false;
	}
}
void SendNoticeToAll(char * Notice)
{
	for (int i=8000;i<9000;i++)
	{
		if(gObjIsConnected(i)==true)
		{
			GCServerMsgStringSend(Notice,i,0x00);
		}
	}
}


int Random(int min,int max) 
{
	srand((unsigned int) time(NULL)); 
    if(min>=max) 
        return 0; 
    int d=max-min; 
    return (rand()%(d+1)+min); 
}  





void DataSendNear (int Map,int X,int Y, PBYTE Protocol , DWORD ProtocolLen, int dist)
{
	for ( int i = MIN_PLAYERID ; i < MAX_PLAYERID ; i ++ )
	{
		BYTE *map  = (BYTE*) ((i * gObjSize) + (gObjBaseAddr + gObjMapID));
		BYTE *posx = (BYTE*) ((i * gObjSize) + (gObjBaseAddr + gObjPosX));
		BYTE *posy = (BYTE*) ((i * gObjSize) + (gObjBaseAddr + gObjPosY));
		if (*map == Map)
		{
			if (( *posx <= X + dist) && (*posx >= X - dist ))
			{
				if (( *posy <= Y + dist) && (*posy >= Y - dist ))
				{
					DataSend(i,(PBYTE)Protocol,ProtocolLen);
				}
			}
		}
	}
}

void QuestSay(int aIndex,const char *Format,...)
{
	char Message[1024];
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message,sizeof(Message), Format, pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSend(aIndex,Packet, Len);
	free (Packet);
}