/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "ChatCore.h"
#include "Log.h"
#include "User.h"
#include "Structure.h"
#include "configs.h"
#include "CQuestSystem.h"
#include "SQL_Manager.h"

cChat ChatSystem;

//Post Global Messages : "/post"
void cChat::ChatGlobal(DWORD aIndex,char* msg)
{
	char* Name;
	Name = (char*)gObj_GetChar(aIndex,gObjNick);
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	if(Config.IsPost==0)
	{
		GCServerMsgStringSend(MSG01,aIndex,1);
		return;
	}

	else if(!strcmpi("/post ",msg))
	{
		GCServerMsgStringSend(MSG02,aIndex,1);
		Log.outError("[POST] [%s]: [%s] syntax error \n",gObj->AccountID,Name);
		return;
	}

	else if(strlen(msg)<1)
	{
		GCServerMsgStringSend(MSG03,aIndex,1);
		Log.outError("[POST] [%s]: [%s] syntax error \n",gObj->AccountID,Name);
		return;
	}

	else if((int)gObj_GetLevel(aIndex)<Config.PostLevel)
	{
		char levelmsg[120];
		sprintf_s(levelmsg,MSG04,Config.PostLevel);
		GCServerMsgStringSend(levelmsg,aIndex,1);
		Log.outError("[POST] [%s]: [%s] not enought Level \n",gObj->AccountID,Name);
		return;
	}
	
	else if(gObj->Money < Config.PostCost)
	{
		char OutputZenLack[120]={0};
		sprintf(OutputZenLack,MSG05,Config.PostCost);
		GCServerMsgStringSend(OutputZenLack,aIndex,1);
		Log.outError("[POST] [%s]: [%s] not enought Zend \n",gObj->AccountID,Name);
		return;
	}
	

	char Buff[255]={0};
	gObj->Money = gObj->Money - Config.PostCost;
	GCMoneySend(aIndex,gObj->Money);
	ServerMsgSend(0,1,Name,MSG06,msg);
	Log.outNormal("[POST] %s : %s \n",Name,msg);
	conLog.ConsoleOutputDT("[POST] %s : %s",Name,msg);
	sprintf(Buff,"[POST]: %s : %s",Name,msg);
	cWriteLog(Buff);
}


void cChat::ChatAddStats(DWORD aIndex, LPCSTR IpBuffer, BYTE CMD_STATS_TYPE) 
{


	int Points = atoi(IpBuffer);
	char* Name;
	Name = (char*)gObj_GetChar(aIndex,gObjNick);
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	if(Config.IsAdd == 0)
	{
		GCServerMsgStringSend(MSG07,aIndex, 1);
		return;
	}

	else if((int)gObj_GetLevel(aIndex) < Config.AddLevel)
	{
		char levelmsg[120];
		sprintf(levelmsg,MSG08,Config.AddLevel);
		GCServerMsgStringSend(levelmsg, aIndex, 1);
		Log.outError("[Add] [%s]: [%s] not enought Level \n",gObj->AccountID,Name);
		return;
	}

	else if(strlen(IpBuffer) <1 || Points<1)
	{
		GCServerMsgStringSend(MSG09, aIndex, 1);
		Log.outError("[Add] [%s]: [%s] syntax error \n",gObj->AccountID,Name);
		return;
	}

	else if((int) gObj_GetInt(aIndex,gObjLupp)<Points)
	{
		GCServerMsgStringSend(MSG10, aIndex, 1);
		Log.outError("[Add] [%s]: [%s] lacking points \n",gObj->AccountID,Name);
		return;
	}

	else if(gObj->Money < Config.AddCost)
	{
		char OutputZenLack[120]={0};
		sprintf(OutputZenLack,MSG11,Config.AddCost);
		GCServerMsgStringSend(OutputZenLack,aIndex,1);
		Log.outError("[Add] [%s]: [%s] lacking Zend \n",gObj->AccountID,Name);
		return;
	}


	else if (Points>Config.AddMaxPoints)
	{
		char exceedpoint[120];
		sprintf(exceedpoint,MSG12,Config.AddMaxPoints);
		GCServerMsgStringSend(exceedpoint,aIndex,1);
		Log.outError("[Add] [%s]: [%s] exceed points \n",gObj->AccountID,Name);
		return;
	}

	else if(CMD_STATS_TYPE == 4 && GetPlayerClass(aIndex) != 64 && GetPlayerClass(aIndex) != 66)
	{
		GCServerMsgStringSend(MSG13, aIndex, 1);
		Log.outError("[Add] [%s]: [%s] syntax error \n",gObj->AccountID,Name);
		return;
	}

	else if(Points > 100)
	{
	
		WORD wStr,wDex,wViatality,wEnergy,wLeader ;
		DWORD dwLvUpPoint;
		PBYTE  pADataAddr ;
		pADataAddr = (PBYTE)(aIndex*gObjSize +gObjOffset) ;

		_asm 
		{
			push eax
			push ebx
			mov eax,pADataAddr
			xor ebx,ebx
			mov bx,WORD PTR [eax+0xDC]
			mov wStr,bx
			mov bx,WORD PTR [eax+0xDE] 
			mov wDex,bx
			mov bx,WORD PTR [eax+0xE0]
			mov wViatality,bx
			mov bx,WORD PTR [eax+0xE2]
			mov wEnergy,bx
			mov bx,WORD PTR [eax+0x100]
			mov wLeader,bx
			mov ebx,DWORD PTR [eax+0xAC]
			mov dwLvUpPoint,ebx
			pop ebx
			pop eax
		}
		Log.outNormal("[%s]: [%s] Before Add: %d Str %d Agi %d Vit %d Ene %d Lead %d \n",gObj->AccountID,Name,dwLvUpPoint,wStr,wDex,wViatality,wEnergy,wLeader);


		WORD wTmpAddPoint = 0 ;
		DWORD dwTmpAddPoint = 0 ;

		wTmpAddPoint = Points ;
		dwTmpAddPoint = wTmpAddPoint ;
		if ( wTmpAddPoint >0)
		{
			switch (CMD_STATS_TYPE)
			{
			case 0x00:
				_asm 
				{
					push eax
					push ebx
					mov eax,pADataAddr
					xor ebx,ebx
					mov bx,WORD PTR [eax+0xDC]
					add bx,wTmpAddPoint
					mov WORD PTR [eax+0xDC],bx
					mov ebx,DWORD PTR [eax+0xAC]
					sub ebx,dwTmpAddPoint
					mov DWORD PTR [eax+0xAC],ebx
					pop ebx
					pop eax
				}
				break;
			case 0x01: 
				_asm
				{
					push eax
					push ebx
					mov eax,pADataAddr
					xor ebx,ebx
					mov bx,WORD PTR [eax+0xDE]
					add bx,wTmpAddPoint
					mov WORD PTR [eax+0xDE],bx
					mov ebx,DWORD PTR [eax+0xAC]
					sub ebx,dwTmpAddPoint
					mov DWORD PTR [eax+0xAC],ebx
					pop ebx
					pop eax
				}
				break;
			case 0x02:
				_asm
				{
					push eax
					push ebx
					mov eax,pADataAddr
					xor ebx,ebx
					mov bx,WORD PTR [eax+0xE0]
					add bx,wTmpAddPoint
					mov WORD PTR [eax+0xE0],bx
					mov ebx,DWORD PTR [eax+0xAC]
					sub ebx,dwTmpAddPoint
					mov DWORD PTR [eax+0xAC],ebx
					pop ebx
					pop eax
				}
				break;
			case 0x03:
				_asm
				{
					push eax
					push ebx
					mov eax,pADataAddr
					xor ebx,ebx
					mov bx,WORD PTR [eax+0xE2]
					add bx,wTmpAddPoint
					mov WORD PTR [eax+0xE2],bx
					mov ebx,DWORD PTR [eax+0xAC]
					sub ebx,dwTmpAddPoint
					mov DWORD PTR [eax+0xAC],ebx
					pop ebx
					pop eax
				}
				break;
			case 0x04:
				_asm
				{
					push eax
					push ebx
					mov eax,pADataAddr
					xor ebx,ebx
					mov bx,WORD PTR [eax+0x100]
					add bx,wTmpAddPoint
					mov WORD PTR [eax+0x100],bx
					mov ebx,DWORD PTR [eax+0xAC]
					sub ebx,dwTmpAddPoint
					mov DWORD PTR [eax+0xAC],ebx
					pop ebx
					pop eax
				}
				break;
			}
				
		}
		_asm 
		{
			push eax
			push ebx
			mov eax,pADataAddr
			xor ebx,ebx
			mov bx,WORD PTR [eax+0xDC]
			mov wStr,bx
			mov bx,WORD PTR [eax+0xDE]
			mov wDex,bx
			mov bx,WORD PTR [eax+0xE0]
			mov wViatality,bx
			mov bx,WORD PTR [eax+0xE2]
			mov wEnergy,bx
			mov bx,WORD PTR [eax+0x100]
			mov wLeader,bx
			mov ebx,DWORD PTR [eax+0xAC]
			mov dwLvUpPoint,ebx
			pop ebx
			pop eax
		}


		gObj->Money = gObj->Money - Config.AddCost;
		GCMoneySend(aIndex,gObj->Money);

		Log.outNormal("[%s]: [%s] After Add: %d Str %d Agi %d Vit %d Ene %d Lead %d \n",gObj->AccountID,Name,dwLvUpPoint,wStr,wDex,wViatality,wEnergy,wLeader);
		GCServerMsgStringSend(MSG14, aIndex, 1);

		return;
		}




	else if (Points<=100&&Points>0)
	{
		gObj->Money = gObj->Money - Config.AddCost;
		GCMoneySend(aIndex,gObj->Money);
		BYTE IpMsg[5] = {0xC1, 0x05, 0xF3, 0x06, CMD_STATS_TYPE};
		for(int i = 0; i < Points; i++)
		CGLevelUpPointAdd(IpMsg, aIndex);
		char Succes[130];
		int lupp = gObj_GetInt(aIndex,gObjLupp);
		sprintf(Succes, MSG15,Points,lupp);
		GCServerMsgStringSend(Succes,aIndex,1);
		conLog.ConsoleOutputDT("[%s]: %s Add: %d Points",gObj->AccountID,Name,Points);
		Log.outNormal("[%s]: [%s] Add: %d Points \n",gObj->AccountID,Name,Points);
		return;
	}
}



//Reload Command
void cChat::ChatReload(DWORD PlayerID,char* msg)
{	
	GOBJSTRUCT * gObj = (GOBJSTRUCT*)OBJECT_POINTER(PlayerID);

	
	if(Config.IsReload==0)
	{
		
		GCServerMsgStringSend("Reload Command had been disable.",PlayerID,1);
		return;
	}


	if(VerifyGM(PlayerID)==false)
	{
		GCServerMsgStringSend("You aren't a GM.",PlayerID,1);
		return;
	}

	else 
	{
	
		IniciaIni();
		LoadIni();

		Log.outInfo("[Reload][%s][%s] Used \"/reload\" command.",gObj->AccountID,gObj->Name);
		Log.outInfo("[Reload] Files .ini succesfully reloaded.");
		conLog.ConsoleOutput("[Reload][%s][%s] Used \"/reload\" command.",gObj->AccountID,gObj->Name);
		conLog.ConsoleOutput("[Reload] Files .ini succesfully reloaded.");
			
		GCServerMsgStringSend("[Reload] Reload Succesfully.",PlayerID,1);
	
	}
	
}

//Change skin
void cChat::ChatSkin(DWORD aIndex,char* msg)
{	
	if(Config.IsSkin==0)
	{
		GCServerMsgStringSend("Skin Command had been disable",aIndex,1);
		return;
	}
	if (Config.IsOnlyGMSkin==1)
	{
	
		if(VerifyGM(aIndex)==false)
		{
			GCServerMsgStringSend("Skin Command only for GM",aIndex,1);
			return;
		}
	}

	if ((int)gObj_GetLevel(aIndex)<Config.SkinLevel)
	{
		char Error[100];
		sprintf(Error,MSG16,Config.SkinLevel);
		GCServerMsgStringSend(Error,aIndex,1);
		return;
	}

	int skin = atoi(msg);
	int playerId = (int)aIndex;

	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(playerId);
	gObj->m_Change = skin;
	gObjViewportListProtocolCreate(gObj);
}

//Online Show
void cChat::OnlineAll(DWORD aIndex)
{
	if (VerifyGM(aIndex==false)) return;

	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int GMs = 0, Players = 0;
	for (int i=8000; i<9000; i++)
	{
		if (gObjIsConnected(i)==true)
		{
			if (VerifyGM(aIndex)==true)
				GMs++;
			else
				Players++;
		}
	}
	char online1[100];
	
	sprintf(online1, "[Online]: Total : %d users connected.", GMs+Players);
	GCServerMsgStringSend(online1,aIndex,1);

	char online2[100];

	sprintf(online2, "[Online] : GM's : %d, Players : %d.", GMs, Players);
	GCServerMsgStringSend(online2,aIndex,1);
}
void cChat::GetTime(DWORD aIndex)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	char timestr[130];
	sprintf_s(timestr, MSG17,time.wHour,time.wMinute,time.wSecond);
	GCServerMsgStringSend(timestr,aIndex,1);
}

void cChat::FireWork (DWORD aIndex,char * msg)
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	if (VerifyGM(aIndex) == false) return;
	int Type = atoi(msg);
	if (Type>100) return;
	else
	FireWorksSend(gObj->MapNumber, gObj->X, gObj->Y,Type);
	return;
}

void cChat::FireworkAll (DWORD aIndex,char * msg)
{
	if (VerifyGM(aIndex) == false) return;
	int Type = atoi(msg);
	if (Type>100) return;
	else
	FireWorksSendAll(Type);
}

void cChat::QuestInfo(DWORD aIndex)
{
	GOBJSTRUCT *lpObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);


	if(lpObj->m_Quest[10] >= Config.QuestCount+1)
	{
		QuestSay(aIndex,MSG31,lpObj->Name); //~[Quest] : %s you finished all quests
		return;
	}
	if(lpObj->m_Quest[9] == 0)
	{
		int iQIndex;
		iQIndex = lpObj->m_Quest[10];
		QuestSay(aIndex,MSG32,g_Quest.m_QuestData[iQIndex].szQuestInfo);//~[Quest] : %s:
		return;
		
	}
	else
	{
		int iQIndex;
		iQIndex = lpObj->m_Quest[10];
		QuestSay(aIndex,MSG33,0x00); //~[Quest] : QuestName:
		QuestSay(aIndex,MSG34,g_Quest.m_QuestData[iQIndex].szQuestName); //~[Quest] : %s:
		QuestSay(aIndex,MSG35,0x00); //~[Quest] : QuestInfo:
		QuestSay(aIndex,MSG34,g_Quest.m_QuestData[iQIndex].szQuestInfo);//~[Quest] : %s:
	}	

}
/*void cChat::TestMail(DWORD aIndex)
{
	char char2[] = "Test Subject";
	char char3[] = "Test Content";
	SQL.SendMail(aIndex,char2,char3);
	
}*/

void cChat::ChatDataSend(DWORD gObjId,LPBYTE Protocol)
{
	


	char CommandPost1[] = "/post ";
	char CommandPost2[] = "/Post ";
	char CommandStr[] = "/addstr"; 
	char CommandAgi[] = "/addagi"; 
	char CommandVit[] = "/addvit"; 
	char CommandEne[] = "/addene"; 
	char CommandCmd[] = "/addcmd"; 					
	char CommandReload[] = "/reload";
	char CommandSkin[] = "/skin ";
	char CommandOnl[] = "/online";
	char CommandGetTime[]="/time";
	char CommandFireWork[]= "/firework ";
	char CommandFireWorkAll[]= "/fireworkall ";
	char CommandQuestInfo[]= "/questinfo";
//	char CommandTest[]= "/test";
								
	


	//Post command
	if(!memcmp(&Protocol[13],CommandPost1,strlen(CommandPost1)))
	{
		this->ChatGlobal(gObjId,(char*)Protocol+13+strlen(CommandPost1));
	}
	if(!memcmp(&Protocol[13],CommandPost2,strlen(CommandPost2)))
	{
		this->ChatGlobal(gObjId,(char*)Protocol+13+strlen(CommandPost2));
	}
	
	
	
	//Str command
	if(!memcmp(&Protocol[13],CommandStr,strlen(CommandStr)))
	{
		this->ChatAddStats(gObjId,(char*)Protocol+13+strlen(CommandStr),0);
	}
	//Agi command
	if(!memcmp(&Protocol[13],CommandAgi,strlen(CommandAgi)))
	{
		this->ChatAddStats(gObjId,(char*)Protocol+13+strlen(CommandAgi),1);
	}
	//Vit command
	if(!memcmp(&Protocol[13],CommandVit,strlen(CommandVit)))
	{
		this->ChatAddStats(gObjId,(char*)Protocol+13+strlen(CommandVit),2);
	}
	//Ene command
	if(!memcmp(&Protocol[13],CommandEne,strlen(CommandEne)))
	{
		this->ChatAddStats(gObjId,(char*)Protocol+13+strlen(CommandEne),3);
	}
	
	//Cmd command
	if(!memcmp(&Protocol[13],CommandCmd,strlen(CommandCmd)))
	{
		this->ChatAddStats(gObjId,(char*)Protocol+13+strlen(CommandCmd),4);
	}
	


	//Reload command
	if(!memcmp(&Protocol[13],CommandReload,strlen(CommandReload)))
	{
		this->ChatReload(gObjId,(char*)Protocol+13+strlen(CommandReload));
	}

	//Skin command
	if(!memcmp(&Protocol[13],CommandSkin,strlen(CommandSkin)))
	{
		this->ChatSkin(gObjId,(char*)Protocol+13+strlen(CommandSkin));
	}
	
	//Online command
	if(!memcmp(&Protocol[13],CommandOnl,strlen(CommandOnl)))
	{
		this->OnlineAll(gObjId);
	}
	//Online command
	if(!memcmp(&Protocol[13],CommandGetTime,strlen(CommandGetTime)))
	{
		this->GetTime(gObjId);
	}
	//FireWork command
	if(!memcmp(&Protocol[13],CommandFireWork,strlen(CommandFireWork)))
	{
		this->FireWork(gObjId,(char*)Protocol+13+strlen(CommandFireWork));
	}
	//FireWork All Server command
	if(!memcmp(&Protocol[13],CommandFireWorkAll,strlen(CommandFireWorkAll)))
	{
		this->FireworkAll(gObjId,(char*)Protocol+13+strlen(CommandFireWorkAll));
	}
	//Quest Info command
	if(!memcmp(&Protocol[13],CommandQuestInfo,strlen(CommandQuestInfo)))
	{
		this->QuestInfo(gObjId);
	}

	/*if(!memcmp(&Protocol[13],CommandTest,strlen(CommandTest)))
	{
		this->TestMail(gObjId);
	}*/
}
