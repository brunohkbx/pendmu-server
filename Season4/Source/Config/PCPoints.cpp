/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "PCPoints.h"
#include "User.h"
#include "GameServer.h"
#include "Log.h"
#include "Common.h"
#include "Structure.h"
#include "Utils.h"
#include "Global.h"



int PCPointShop::SQLGetPoints(DWORD PlayerID) 
{
	
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(PlayerID);
	char szQueryBuff[500];
	wsprintfA(szQueryBuff, "SELECT PCPoints FROM Character WHERE Name = '%s';", gObj->Name);
	unsigned int PCPoints = SQL.ReturnInt("PCPoints",szQueryBuff);
	unsigned int Max=32767;
	if (PCPoints>Max)
		PCPoints=Max;
	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(PCPoints) , HIBYTE(PCPoints) , LOBYTE(Max) , HIBYTE(Max)};
	DataSend(PlayerID,(PBYTE)Packet,Packet[1]);	
	return PCPoints;
}

void PCPointShop::SQLSetStatus(DWORD PlayerID) 
{
	int ID=PlayerID-MIN_PLAYERID;
	char sBuf[255]={0};

	LPGOBJSTRUCT pObj = (LPGOBJSTRUCT)(PlayerID*gObjSize + gObjBaseAddr);

	if((pObjGS[ID].PCInfoMod==1)&&(pObjGS[ID].PCInfoReceived==1))
	{
		char Query[500]={0};

		wsprintf(Query,"UPDATE Character SET PCPoints = %d Where Name = '%s'",pObjGS[ID].PCPlayerPoints,GetName(PlayerID));
		SQL.DoQuery(Query);

		wsprintf(sBuf, "[PCPointShop] SaveInfo [%s][%s] Points: %d",pObj->AccountID,pObj->Name,pObjGS[ID].PCPlayerPoints);
		Log.outNormal(sBuf,14);
		pObjGS[ID].PCInfoMod=0;
	} else {
		if (pObjGS[ID].PCInfoReceived==0)
		{
			this->GetInfo(PlayerID);
			//Gs_GCServerMsgStringSend("[PCPointShop] SYSTEM ERROR, REQUESTING POINTS RECORD!",PlayerID, 0x01);

			//wsprintf(sBuf, "[PCPointShop][ERROR][%s][%s] RE-REQUESTING PCPoints RECORD!",pObj->AccountID,pObj->Name);
			//DebugInfo(sBuf,14);
		} else {
			//wsprintf(sBuf, "[PCPointShop] Already Saved [%s][%s] Points: %d",pObj->AccountID,pObj->Name,pObjSCFMT[ID].PCPlayerPoints);
			//DebugInfo(sBuf,14);
		}
	}
}

UINT PCPointShop::ReadFile()
{
	DWORD dwArgv=0;
	FILE *fp;
	char sLineTxt[255] = {0};
	BOOL bRead = FALSE;
	
	this->HowManyItems=0;
	this->MobPointRecords=0;

	srand((unsigned)time(NULL));
	char path[255]; 

	if((fp=fopen("..\\OptionsData\\PCPoint.txt", "r")) == NULL)
	{
		MessageBox(NULL, "PCPoint.txt Load Failed", "Error ", 0);
		IsPCPointSystem = FALSE;
		return 0;
	}

	IsPCPointSystem = TRUE;

	rewind(fp);
	
	int leestatus=-1;
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;  
		
		if(bRead == FALSE && (UINT)(sLineTxt[0]-0x30) == dwArgv) bRead = TRUE;			

		if(bRead==TRUE && strlen(sLineTxt)<3)
		{
			UINT q = 0;
			sscanf(sLineTxt, "%d", &q);
			leestatus = q;
		}

		if(leestatus == 0)
		{
			if(bRead==TRUE && strlen(sLineTxt)>3)
			{
				if ((sLineTxt[0] == 'e')&&(sLineTxt[1] == 'n')&&(sLineTxt[2] == 'd'))
				{
					leestatus = -1;
				} else {
					sscanf(sLineTxt, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &Items[HowManyItems].ItemIndex , &Items[HowManyItems].ItemID , &Items[HowManyItems].X, &Items[HowManyItems].Y,&Items[HowManyItems].Level, &Items[HowManyItems].Opt,&Items[HowManyItems].Luck, &Items[HowManyItems].Skill,&Items[HowManyItems].Dur,&Items[HowManyItems].Exc,&Items[HowManyItems].NewOpt1,&Items[HowManyItems].NewOpt2,&Items[HowManyItems].NewOpt3,&Items[HowManyItems].NewOpt4,&Items[HowManyItems].NewOpt5,&Items[HowManyItems].Cost);
					Items[HowManyItems].SlotX=CalcItemXY(Items[HowManyItems].X,Items[HowManyItems].Y);
					this->HowManyItems++;
				}
			}
		}
		if(leestatus == 1)
		{
			if(bRead==TRUE && strlen(sLineTxt)>3)
			{
				if ((sLineTxt[0] == 'e')&&(sLineTxt[1] == 'n')&&(sLineTxt[2] == 'd'))
				{
					leestatus = -1;
				} else {
					sscanf(sLineTxt, "%d %d", &pPCMobPoint[MobPointRecords].MobID , &pPCMobPoint[MobPointRecords].Points);
					this->MobPointRecords++;
				}
			}
		}
	}

	rewind(fp);
	fclose(fp);

	//Log portion for bug tracing
	char sBuf[255] = {0};
	wsprintf(sBuf, "[PCPointShop] Item Records: %d / Monster Records: %d",this->HowManyItems,this->MobPointRecords);
	conLog.ConsoleOutput("%s", sBuf);

	return 1;
}

int PCPointShop::SearchIndex(int Position)
{
	for(int i=0;i<HowManyItems;i++)
	{
		if(Position==Items[i].SlotX)
			return i;
	}
	return (-1);
}

int PCPointShop::CalcItemXY(int X,int Y)
{
	int YPos=0;
	int XPos=0;
	int j=-1;
	Y-=1;

	while(YPos<15)
	{
		XPos=0;
		while(XPos<8)
		{
			if((PC_Shop[XPos+(YPos*8)]==0) && (PC_Shop[XPos+(YPos*8)+X-1]==0) && (XPos+X-1<8))
			{
				if(Y==0)
				{
					for(j=0;j<X;j++)
						PC_Shop[XPos+(YPos*8)]=1;
					return (XPos+(YPos*8));
				}else
				{

					if((PC_Shop[(XPos+(YPos*8))+(Y*8)]==0) /*&& (PC_Shop[(XPos+(YPos*8)+X)+(Y*8)]==0)*/ && (XPos+X-1<8))
					{
						for(j=0;j<X;j++)
						{
							for(int z=1;z<=Y;z++)
							{
								PC_Shop[XPos+(YPos*8)+j+z*8]=1;
							}
							PC_Shop[XPos+(YPos*8)+j]=1;
						}
						return (XPos+(YPos*8));
					}
				}
			}
			XPos++;
		}
		YPos++;
	}

	return j;
}

int PCPointShop::MakePacket()
{
	int PacketSize=0;
	int PacketFlag=0;
	int Size=0;

	BYTE Packet1[11]={0xC1,0x05,0xD0,0x06,0x00,0xC2,0x00,0x36,0x31,HIBYTE(HowManyItems),LOBYTE(HowManyItems)};
	BYTE Packet2[4680];

	for(int i=0;i<HowManyItems;i++)
	{
		int LuckOptLevel=((Items[i].Opt/4)+(Items[i].Luck*4)+(Items[i].Level*8) + (Items[i].Skill*128));
		int ItemIndex=Items[i].ItemIndex*16;

		
	
			BYTE BetaPacket[13]={Items[i].SlotX,Items[i].ItemID,LuckOptLevel,Items[i].Dur,0x00,Items[i].Exc,ItemIndex,Items[i].NewOpt1,Items[i].NewOpt2,Items[i].NewOpt3,Items[i].NewOpt4,Items[i].NewOpt5,0x00};
			PacketSize=(sizeof(BetaPacket)*(i+1));
			memcpy(&Packet2[PacketFlag],BetaPacket,PacketSize );
				
		PacketFlag=PacketSize;
	}

	Size=(sizeof(Packet1)+PacketSize);
	memcpy(&PCPointPacket,Packet1, sizeof(Packet1));
	memcpy(&PCPointPacket[sizeof(Packet1)],Packet2, sizeof(Packet1)+PacketSize);
	PCPointPacket[6]=HIBYTE(Size);
	PCPointPacket[7]=LOBYTE(Size);

	return (sizeof(Packet1)+PacketSize);
}

void PCPointShop::Init()
{
	int i=0;

	for(i=0;i<120;i++)
		PC_Shop[i]=0x00;

	for(i=0;i<MAX_PLAYERID-MIN_PLAYERID;i++)
	{
		pObjGS[i].PCInfoReceived=0;
		pObjGS[i].PCInfoMod=0;
		pObjGS[i].PCPlayerPoints=0;
	}

	ReadFile();
	PacketSizes=MakePacket();

	MaxPlayerPoints=32767;
	PCPoint.AddWhenKillMobs=GetPrivateProfileInt("Character","AddPCPointsWhenKillMobs",1,"..\\OptionsData\\Options.ini");
	PCPoint.OnlyForGM=GetPrivateProfileInt("Character","PCPointsOnlyForGM",1,"..\\OptionsData\\Options.ini");
}

void PCPointShop::OpenShop(DWORD PlayerID)
{
	if(OnlyForGM==1)
	{
		if(VerifyGM(PlayerID)==true)
		{
			DataSend(PlayerID,PCPointPacket,PacketSizes);
		}
		else
			return;
	}
	else
	{
		//BYTE OpenPacket[11]={0xC1,0x05,0xD0,0x06,0x00,0xC2,0x00,0x36,0x31,0x00,0x00};
		//DataSend(PlayerID,OpenPacket,OpenPacket[1]);
		//Sleep(10);
		DataSend(PlayerID,PCPointPacket,PacketSizes);
		return;
	}
}

void PCPointShop::BuyItem(DWORD PlayerID,int Position)
{
	int ID=PlayerID-MIN_PLAYERID;
	LPGOBJSTRUCT pObj = (LPGOBJSTRUCT)(PlayerID*gObjSize + gObjBaseAddr);
	char sBuf[255]		= {0};
	int i=SearchIndex(Position);
	BOOL IfBuy=FALSE;

	if(i!=(-1))
	{
		if(Items[i].Cost<pObjGS[ID].PCPlayerPoints)
		{
			int RewardItem=Items[i].ItemIndex*512+Items[i].ItemID;
			ItemSerialCreateSend(PlayerID,235,0,0,(DWORD)RewardItem,Items[i].Level,Items[i].Dur,Items[i].Skill,Items[i].Luck,(Items[i].Opt/4),-1,Items[i].Exc,0);
			DecreasePoints(PlayerID,Items[i].Cost);
			IfBuy=TRUE;
		}
	}
	//Log
	if((IfBuy==TRUE) && (i!=(-1)))
	{
		wsprintf(sBuf, "[PCPointShop] BuyItem [%s][%s] Item {%d %d} Cost: %d",pObj->AccountID,pObj->Name,Items[i].ItemIndex,Items[i].ItemID,Items[i].Cost);
		Log.outNormal(sBuf);
	} else {
		wsprintf(sBuf, "[PCPointShop] Attempt to BuyItem [%s][%s] Item {%d %d} Cost: %d",pObj->AccountID,pObj->Name,Items[i].ItemIndex,Items[i].ItemID,Items[i].Cost);
		Log.outError(sBuf,14);
	}
}


void PCPointShop::IncreasePoints(DWORD PlayerID,int Points)
{
	int ID=PlayerID-MIN_PLAYERID;
	
	if(pObjGS[ID].PCPlayerPoints+Points>MaxPlayerPoints)
	{
		pObjGS[ID].PCPlayerPoints=MaxPlayerPoints;
	}
	else
	{
		pObjGS[ID].PCPlayerPoints+=Points;
	}
	pObjGS[ID].PCInfoMod=1;
	pObjGS[ID].PCInfoReceived=1;
	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(pObjGS[ID].PCPlayerPoints) , HIBYTE(pObjGS[ID].PCPlayerPoints) , LOBYTE(MaxPlayerPoints) , HIBYTE(MaxPlayerPoints)};
	DataSend(PlayerID,(PBYTE)Packet,Packet[1]);
}

void PCPointShop::DecreasePoints(DWORD PlayerID,int Points)
{
	int ID=PlayerID-MIN_PLAYERID;
	
	if(pObjGS[ID].PCPlayerPoints-Points<0)
	{
		pObjGS[ID].PCPlayerPoints=0;
	}
	else
	{
		pObjGS[ID].PCPlayerPoints-=Points;
		//this->SendPoints(PlayerID);
	}
	
	pObjGS[ID].PCInfoMod=1;
	pObjGS[ID].PCInfoReceived=1;
	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(pObjGS[ID].PCPlayerPoints) , HIBYTE(pObjGS[ID].PCPlayerPoints) , LOBYTE(MaxPlayerPoints) , HIBYTE(MaxPlayerPoints)};
	DataSend(PlayerID,(PBYTE)Packet,Packet[1]);
}

void PCPointShop::GetInfo(DWORD PlayerID)
{
	int ID=PlayerID-MIN_PLAYERID;

	pObjGS[ID].PCInfoMod=0;
	pObjGS[ID].PCInfoReceived=0;
	pObjGS[ID].PCPlayerPoints = this->SQLGetPoints(PlayerID);
	//pObjGS[ID].PCPlayerPoints=0;
/*
	if (gObjIsConnected(PlayerID)==true)
	{
		LPGOBJSTRUCT pObj = (LPGOBJSTRUCT)(PlayerID*gObjSize + gObjBaseAddr);
		//wsprintf(sBuf,"SELECT PCPoints, Name FROM %s.dbo.Character WHERE Name = N'%s'", SQLDataBase,pObj->Name);
		//pObjGS[ID].PCPlayerPoints = PSQL->GetFieldInt("Character","PCPoints","WHERE Name = '%s'",pObj->Name);
		
	}
	*/

	//Log
	//wsprintf(sBuf, "[PCPointShop] GetInfo [%s][%s] Points: %d",pObj->AccountID,pObj->Name,PlayerPoints[ID]);
	//DebugInfo(sBuf,14);
}

int PCPointShop::GetRewardPoints(int MobID)
{
	for(int i=0;i<MobPointRecords;i++)
	{
		if(MobID==pPCMobPoint[i].MobID)
			return pPCMobPoint[i].Points;
	}
	return 0;
}

void PCPointShop::LevelUp(DWORD PlayerID, int MobID)
{
	if(PCPoint.AddWhenKillMobs==1)
	{

		int ID=PlayerID-MIN_PLAYERID;
		int RecvPoints		= 0;
		char sBuf[255]		= {0};
		LPGOBJSTRUCT pObj	= (LPGOBJSTRUCT)(PlayerID*gObjSize + gObjBaseAddr);

		if(pObjGS[ID].PCPlayerPoints<MaxPlayerPoints)
		{
			RecvPoints=GetRewardPoints(MobID);
			if (RecvPoints>0)
			{
				IncreasePoints(PlayerID,RecvPoints);

				//Send Blue Text with Points
				wsprintf(sBuf, MSG24,pObj->Name,RecvPoints);
				GCServerMsgStringSend(sBuf,PlayerID, 0x01);
				wsprintf(sBuf, "[PCPointShop][%s] Kill: %d, Earned %d, Total: %d",pObj->Name,MobID,RecvPoints,pObjGS[ID].PCPlayerPoints);
				Log.outNormal("%s\n",sBuf);

				if (pObjGS[ID].PCInfoReceived==0)
				{
					this->GetInfo(PlayerID);
				
				}
			}
		} else 
		{
			GCServerMsgStringSend(MSG25,PlayerID, 0x01);
		}
	}
}