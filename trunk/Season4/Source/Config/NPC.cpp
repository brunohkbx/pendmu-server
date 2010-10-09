/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "stdafx.h"
#include "GameServer.h"
#include "User.h"
#include "Common.h"
#include "Utils.h"
#include "NPC.h"
#include "Log.h"
#include "Items.h"
#include "SQL_Manager.h"
#include "Structure.h"
#include "CQuestSystem.h"
#include <stdio.h>


RewardItem GaItem[255];



//int useproto=GetPrivateProfileIntA("Protocol","GSProtocol",0,"..\\OptionsData\\Options.ini");
int needrena = GetPrivateProfileIntA("Event","GoldenArcherNeedRena",2,"..\\OptionsData\\Options.ini");
void NPCTalkEx(DWORD aIndex, DWORD aDestIndex) 
{
	GOBJSTRUCT * gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	GOBJSTRUCT * nObj = (GOBJSTRUCT*)OBJECT_POINTER(aDestIndex);
	bool bResult = false;

	if(nObj->Class == 236 && Config.IsGADrop == 1)
	{
		//unsigned char GAMsg[7] = {0xc1, 0x07, 0x94, 0x00};
		//memcpy(&GAMsg[4], &gObj->m_Quest[8], 2);
		//DataSend(aIndex, GAMsg, 7);
		char Query1[500]={0};
		int ID=aIndex-MIN_PLAYERID;
		wsprintfA(Query1, "SELECT MuttoNumber FROM T_MU2003_EVENT WHERE AccountID = '%s';", gObj->AccountID);
		pObjGS[ID].myregRena = SQL.ReturnInt("MuttoNumber",Query1);
		
		char Query2[500]={0};
		wsprintf(Query2,"UPDATE T_MU2003_EVENT SET EventChips = %d WHERE AccountID = '%s'",pObjGS[ID].myregRena,gObj->AccountID);
		SQL.DoQuery(Query2);
		//gObj->EventChipCount = pObjGS[ID].myregRena;
	}

		if(nObj->Class == 258)
		{
			g_Quest.NPCTalk1(nObj,aIndex);
		}




		 if (nObj->Class == 522)
		{	
		//C3 0A 30 24 XX XX XX XX XX XX - Imperial Fort
		BYTE Packet[4] = {0xC3, 0x0A, 0x30, 0x22};
				
		Packet[4] = 0x00; //07
		Packet[5] = 0x00; //6D
		Packet[6] = 0x00; //A6
		Packet[7] = 0x00; //0E
		Packet[8] = 0x00;
		Packet[9] = 0x00;

		DataSend(aIndex, &Packet[0], Packet[1]);

		Log.outNormal("[%s][%s] Click on Jerry The Adviser",gObj->AccountID,gObj->Name);
		bResult = true;
	}
	else
	{
		bResult = false;
	}
	//if(nObj->Class == 465)
	//{
	//	SantaClaus(aIndex);
	//}

}
void GoldenArcher(DWORD aIndex,DWORD ItemAddress)
{
	if (Config.IsGADrop = 1)
	{
	
		GOBJSTRUCT * gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
		int ID = aIndex - MIN_PLAYERID;
		//pObjGS[ID].myregRena = NPCSQL->GetFieldInt("T_MU2003_EVENT","MuttoNumber","WHERE AccountID = '%s'",gObj->AccountID);
		int AddressInv = ItemAddress+12;
		if (CheckItemInv(aIndex,0x1C15,0x00,AddressInv)==true)
		{
			pObjGS[ID].myregRena++;
	
			if (pObjGS[ID].myregRena>=Config.GANeedRena)
			{
				pObjGS[ID].myregRena=pObjGS[ID].myregRena-needrena;
				int i = Role(Config.GAItemscount);
				int RandOp=0;
				int RandLv=0;
				int RandLuck=0;
				int RandSkill=0;
				if (GaItem[i].Option>0)
				{
					RandOp = Role(7);
				}
				if(GaItem[i].Level>0)
				{
					RandLv = Role(GaItem[i].Level);
				}
				if(GaItem[i].Luck>0)
				{
					RandLuck = Random(0,1);
				}
				if(GaItem[i].Skill>0)
				{
					RandSkill = Random(0,1);
				}
				int Item=GaItem[i].Type*512+GaItem[i].Index;
				ItemSerialCreateSend (aIndex,gObj->MapNumber,gObj->X,gObj->Y,Item,RandLv,0,RandSkill,RandLuck,RandOp,aIndex,GaItem[i].Excellent,0);
			
				//char QueryGa[1024]={0};
				//wsprintf(QueryGa,"Update %s.dbo.T_MU2003_EVENT SET EventChips = %d WHERE ACCountID = '%s'",SQLDataBase,pObjGS[ID].myregRena,gObj->Name);
				//NPCSQL->ExecData(QueryGa);
			
			}
		}
		else
		{
			Log.outError("[Anti-Hack]: [%s][%s] Trying to hack in NPC Golden Archer",gObj->AccountID,gObj->Name);
			GCServerMsgStringSend("[Anti-Hack]: Trying to hack in NPC Golden Archer",aIndex,1);
			//CloseClient(aIndex);
		}
	}
}

void GoldenArcherSaveData(DWORD aIndex)
{
	int ID = aIndex - MIN_PLAYERID;
	GOBJSTRUCT * gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	char QueryGa2[500]={0};
	wsprintf(QueryGa2,"UPDATE T_MU2003_EVENT SET MuttoNumber = %d WHERE AccountID = '%s'",pObjGS[ID].myregRena,gObj->AccountID);
	SQL.DoQuery(QueryGa2);
}
	

void GoldenArcherInit(DWORD dwArgv,int state,char *FileName)
{
	Config.GAItemscount=0;
	FILE *file;
	char sLineTxt[1000] = {0};
	BOOL bRead = FALSE;
	int i=0;
	int leestatus=-1;
	char path[500]; 
	wsprintf(path, "%s", FileName);
	file=fopen(path,"r");
	if(file == NULL)
	{
		MessageBox(NULL, "GoldenArcher.txt Read Failed", "Error ", 0);
		::ExitProcess(0);
	}
	
	
	rewind(file);
	
	while(fgets(sLineTxt, 255, file) != NULL)
	{
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;  
		
		if(bRead == FALSE && (UINT)(sLineTxt[0]-0x30) == dwArgv) 
			bRead = TRUE;	

		if(bRead==TRUE && strlen(sLineTxt)<3)
		{
			UINT q = 0;
			sscanf(sLineTxt, "%d", &q);
			leestatus = q;
		}
		if(state==leestatus)
		{
			if(bRead==TRUE && strlen(sLineTxt)>3)
			{
				if ((sLineTxt[0] == 'e')&&(sLineTxt[1] == 'n')&&(sLineTxt[2] == 'd'))
					leestatus = -1;
				else
				{
					int n[8] = {0};
					sscanf(sLineTxt, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
					
					GaItem[i].Type			= n[0];
					GaItem[i].Index			= n[1];
					GaItem[i].Level			= n[2];	
					GaItem[i].Option		= n[3];	
					GaItem[i].Luck			= n[4];	
					GaItem[i].Skill			= n[5];
					GaItem[i].Duration		= n[6];	
					GaItem[i].Excellent		= n[7];	
					Config.GAItemscount++;
					i++;
				}
			}
		}			
	}

	rewind(file);
	fclose(file);
	conLog.ConsoleOutput("[GoldenArcher] Total %d Items Read",Config.GAItemscount);

}


void SantaClaus (DWORD aIndex)
{
	GOBJSTRUCT * gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	int ItemType = 67;
	int ItemNr = 8;
	int Item = ItemType*512+ItemNr;
	ItemSerialCreateSend (aIndex,gObj->MapNumber,gObj->X,gObj->Y,Item,0,0,0,0,0,aIndex,0,0);
	Log.outNormal ("[%s][%s]: Receive from Santa Claus",gObj->AccountID,gObj->Name);
	conLog.ConsoleOutputDT("[%s][%s] Receive from Santa Claus",gObj->AccountID,gObj->Name);
	return;
}



/*
bool isRena(int aIndex)
{
	GOBJSTRUCT * gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	for(int i = 10; i < 76; i++)
	{

		if(gObj->pInventory[i].m_Type == 0x1C15 && gObj->pInventory[i].m_Level == 0)
		{
			return true;
		}
		
	}
	return false;
}
*/