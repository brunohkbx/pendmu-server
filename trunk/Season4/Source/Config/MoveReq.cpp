#include "stdafx.h"
#include "movereq.h"
#include "WzMemScript.h"
#include "Log.h"
#include "GameServer.h"
#include "Utils.h"


CMoveSystem g_MoveReq;

void CMoveSystem::Init()
{
	for(int i=0;i<MAX_MOVES;i++)
	{
		this->m_MoveData[i].iIndex = 0;
		this->m_MoveData[i].iMoney = 0;
		this->m_MoveData[i].iLevel = 0;
		this->m_MoveData[i].iGate = 0;
	}
}

void CMoveSystem::InitGate()
{
	for(int i=0;i<MAX_GATES;i++)
	{
		this->m_GateData[i].iIndex = 0;
		this->m_GateData[i].iType = 0;
		this->m_GateData[i].iMapNum = 0;
		this->m_GateData[i].iX1 = 0;
		this->m_GateData[i].iY1 = 0;
		this->m_GateData[i].iX2 = 0;
		this->m_GateData[i].iY2 = 0;
		this->m_GateData[i].iTarget = 0;
		this->m_GateData[i].iDir = 0;
		this->m_GateData[i].iLevel = 0;
	}
}

void CMoveSystem::LoadFile(char *filename)
{
	this->Init();
	
	if((SMDFile = fopen(filename, "r")) == NULL)
	{
		MessageBoxA(0,"CMoveManager::LoadFile() error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	SMDToken Token;
	int iIndex;
	char szMoveKor[40] = {0};
	char szMoveEng[40] = {0};
	int iMoney = 0;
	int iLevel = 0;
	int iGate = 0;
	int MoveReqs = 0;

	while(true)
	{
		Token = GetToken();

		if(MoveReqs == 255)
			break;

		iIndex = TokenNumber;
		
		Token = GetToken();
		memcpy(szMoveKor,TokenString,sizeof(szMoveKor));

		Token = GetToken();
		memcpy(szMoveEng,TokenString,sizeof(szMoveEng));

		Token = GetToken();
		iMoney = TokenNumber;

		Token = GetToken();
		iLevel = TokenNumber;

		Token = GetToken();
		iGate = TokenNumber;
		//Log.outInfo("%d '%s' '%s' %d %d %d",iIndex,szMoveKor,szMoveEng,iMoney,iLevel,iGate);

		this->Insert(iIndex,szMoveKor,szMoveEng,iMoney,iLevel,iGate);	
		MoveReqs++;
	}

	fclose(SMDFile);
	conLog.ConsoleOutput("[Pendulum] File [%s] is Loaded",filename); 
	return;
}

void CMoveSystem::LoadGate(char *filename)
{
	this->InitGate();
	
	if((SMDFile = fopen(filename, "r")) == NULL)
	{
		MessageBoxA(0,"g_MoveManager::LoadGate() error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	SMDToken Token;
	int iIndex;
	int iType = 0;
	int iMapNum = 0;
	int iX1 = 0;
	int iY1 = 0;
	int iX2 = 0;
	int iY2 = 0;
	int iTarget = 0;
	int iDir = 0;
	int iLevel = 0;
	int GateReqs = 0;

	while(true)
	{
		Token = GetToken();

		if(GateReqs == 290)
			break;

		iIndex = TokenNumber;

		Token = GetToken();
		iType = TokenNumber;

		Token = GetToken();
		iMapNum = TokenNumber;

		Token = GetToken();
		iX1 = TokenNumber;
		
		Token = GetToken();
		iY1 = TokenNumber;

		Token = GetToken();
		iX2 = TokenNumber;

		Token = GetToken();
		iY2 = TokenNumber;

		Token = GetToken();
		iTarget = TokenNumber;

		Token = GetToken();
		iDir = TokenNumber;

		Token = GetToken();
		iLevel = TokenNumber;

		//Log.outInfo("%d %d %d %d %d %d %d %d %d %d",iIndex,iType,iMapNum,iX1,iY1,iX2,iY2,iTarget,iDir,iLevel);

		this->InsertGate(iIndex,iType,iMapNum,iX1,iY1,iX2,iY2,iTarget,iDir,iLevel);	
		GateReqs++;
	}

	fclose(SMDFile);
	Log.outNormal("[Pendulum] File [%s] is Loaded",filename); 
	return;
}

void CMoveSystem::InsertGate(int iIndex,int iType,int iMapNum,int iX1,int iY1,int iX2,int iY2,int iTarget,int iDir,int iLevel)
{
	this->m_GateData[iIndex].iIndex = iIndex;
	this->m_GateData[iIndex].iType = iType;
	this->m_GateData[iIndex].iMapNum = iMapNum;
	this->m_GateData[iIndex].iX1 = iX1;
	this->m_GateData[iIndex].iY1 = iY1;
	this->m_GateData[iIndex].iX2 = iX2;
	this->m_GateData[iIndex].iY2 = iY2;
	this->m_GateData[iIndex].iTarget = iTarget;
	this->m_GateData[iIndex].iDir = iDir;
	this->m_GateData[iIndex].iLevel = iLevel;
}

void CMoveSystem::Insert(int iIndex,char *szMoveKor,char *szMoveEng, int iMoney,int iLevel,int iGate)
{
	this->m_MoveData[iIndex].iIndex = iIndex;
	strcpy(this->m_MoveData[iIndex].szMoveKor,szMoveKor);
	strcpy(this->m_MoveData[iIndex].szMoveEng,szMoveEng);
	this->m_MoveData[iIndex].iMoney = iMoney;
	this->m_MoveData[iIndex].iLevel = iLevel;
	this->m_MoveData[iIndex].iGate = iGate;
}

void CMoveSystem::MoveTeleport(int aIndex,char *MapName)
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	for(int i=0;i<MAX_MOVES;i++)
	{
		if(!_strcmpi(MapName, this->m_MoveData[i].szMoveEng))
		{	
			int TeleportMap;
			int iError = 0;
			//Messages.outNormal(aIndex,"Finded %s %d",MapName,i);
			
			if(this->m_GateData[this->m_MoveData[i].iGate].iX1 == this->m_GateData[this->m_MoveData[i].iGate].iX2)
			this->m_GateData[this->m_MoveData[i].iGate].iX2++;
			if(this->m_GateData[this->m_MoveData[i].iGate].iY1 == this->m_GateData[this->m_MoveData[i].iGate].iY2)
			this->m_GateData[this->m_MoveData[i].iGate].iY2++;
			
			int FinalX = min(this->m_GateData[this->m_MoveData[i].iGate].iX1,this->m_GateData[this->m_MoveData[i].iGate].iX2)+rand()%(max(this->m_GateData[this->m_MoveData[i].iGate].iX1,this->m_GateData[this->m_MoveData[i].iGate].iX2)-min(this->m_GateData[this->m_MoveData[i].iGate].iX1,this->m_GateData[this->m_MoveData[i].iGate].iX2));
			int FinalY = min(this->m_GateData[this->m_MoveData[i].iGate].iY1,this->m_GateData[this->m_MoveData[i].iGate].iY2)+rand()%(max(this->m_GateData[this->m_MoveData[i].iGate].iY1,this->m_GateData[this->m_MoveData[i].iGate].iY2)-min(this->m_GateData[this->m_MoveData[i].iGate].iY1,this->m_GateData[this->m_MoveData[i].iGate].iY2));
#ifdef Season5			
			if(IsExistWingItem(aIndex) == 65535 && this->m_GateData[this->m_MoveData[i].iGate].iMapNum == 10)
			{
				//return no wings
				gObjTeleport(aIndex, gObj->MapNumber, gObj->X,gObj->Y);
				iError = 1;
			}
			
			if(iError == 1)
			{
				if(IsExistPetItem(aIndex) != 6659 && this->m_GateData[this->m_MoveData[i].iGate].iMapNum == 10)
				{
					//return no dinorant
					Messages.outNormal(aIndex,"You are currently not able to warp.");
					gObjTeleport(aIndex, gObj->MapNumber, gObj->X,gObj->Y);
					iError = 0;
					return;
				}
			}
#endif
			if(gObj->Level < this->m_MoveData[i].iLevel)
			{	
				Messages.outNormal(aIndex,"You need %d level to warp. %d",this->m_MoveData[i].iLevel,gObj->Level);
				return;
			}
			
			if(gObj->Money < this->m_MoveData[i].iMoney)
			{
				Messages.outNormal(aIndex,"Not enought zen.");
				return;
			}

			gObj->Money -= this->m_MoveData[i].iMoney;
			GCMoneySend(aIndex,gObj->Money);

			TeleportMap = this->m_GateData[this->m_MoveData[i].iGate].iMapNum;
			gObjTeleport(aIndex, TeleportMap, FinalX,FinalY);
		}
	}
}

void CMoveSystem::Teleport(int aIndex, int MovNum)
{	
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	int TeleportMap;
	int iError = 0;

	if(this->m_GateData[this->m_MoveData[MovNum].iGate].iX1 == this->m_GateData[this->m_MoveData[MovNum].iGate].iX2)
		this->m_GateData[this->m_MoveData[MovNum].iGate].iX2++;
	if(this->m_GateData[this->m_MoveData[MovNum].iGate].iY1 == this->m_GateData[this->m_MoveData[MovNum].iGate].iY2)
		this->m_GateData[this->m_MoveData[MovNum].iGate].iY2++;
	
	int FinalX = min(this->m_GateData[this->m_MoveData[MovNum].iGate].iX1,this->m_GateData[this->m_MoveData[MovNum].iGate].iX2)+rand()%(max(this->m_GateData[this->m_MoveData[MovNum].iGate].iX1,this->m_GateData[this->m_MoveData[MovNum].iGate].iX2)-min(this->m_GateData[this->m_MoveData[MovNum].iGate].iX1,this->m_GateData[this->m_MoveData[MovNum].iGate].iX2));
	int FinalY = min(this->m_GateData[this->m_MoveData[MovNum].iGate].iY1,this->m_GateData[this->m_MoveData[MovNum].iGate].iY2)+rand()%(max(this->m_GateData[this->m_MoveData[MovNum].iGate].iY1,this->m_GateData[this->m_MoveData[MovNum].iGate].iY2)-min(this->m_GateData[this->m_MoveData[MovNum].iGate].iY1,this->m_GateData[this->m_MoveData[MovNum].iGate].iY2));

/*	if(gObj->m_PK_Level > 3)
	{
		Messages.outNormal(aIndex,"PK can't use warp menu");
		return;
	}*/
#ifdef Season5
	if(IsExistWingItem(aIndex) == 65535 && this->m_GateData[this->m_MoveData[MovNum].iGate].iMapNum == 10)
	{
		//return no wings
		gObjTeleport(aIndex, gObj->MapNumber, gObj->X,gObj->Y);
		iError = 1;
	}
	
	if(iError == 1)
	{
		if(IsExistPetItem(aIndex) != 6659 && this->m_GateData[this->m_MoveData[MovNum].iGate].iMapNum == 10)
		{
			//return no dinorant
			Messages.outNormal(aIndex,"You are currently not able to warp.");
			gObjTeleport(aIndex, gObj->MapNumber, gObj->X,gObj->Y);
			iError = 0;
			return;
		}
	}
#endif
	if(gObj->Level < this->m_MoveData[MovNum].iLevel)
	{	
		Messages.outNormal(aIndex,"You need %d level to warp. %d",this->m_MoveData[MovNum].iLevel,gObj->Level);
		return;
	}
	
	if(gObj->Money < this->m_MoveData[MovNum].iMoney)
	{
		Messages.outNormal(aIndex,"Not enought zen.");
		return;
	}

	gObj->Money -= this->m_MoveData[MovNum].iMoney;
	GCMoneySend(aIndex,gObj->Money);

	TeleportMap = this->m_GateData[this->m_MoveData[MovNum].iGate].iMapNum;
	gObjTeleport(aIndex, TeleportMap, FinalX,FinalY);
}