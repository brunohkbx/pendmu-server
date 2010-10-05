/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include <process.h>
#include "stdafx.h"
#include "Gameserver.h"
#include "Utils.h"
#include "DuelSystem.h"
#include "Global.h"
#include "User.h"
#include "Log.h"

void DuelSystemClass__InsideTrigger(void * lpParam);
DuelSystemClass Duel;

void DuelSystemClass::SendEndDuelNotification(DWORD PlayerID, char* Winner, char* Looser)
{
	PMSG_DUEL_FINISH pMsg;
	
	pMsg.hc = 0xC1;
	pMsg.size = sizeof(pMsg);
	pMsg.headcode = 0xAA;
	pMsg.subcode = 0x0C;
	memcpy(pMsg.szWinner, Winner, 10);
	memcpy(pMsg.szLooser, Looser, 10);

	DataSend(PlayerID, (BYTE*)&pMsg, pMsg.size);
}

void DuelSystemClass::NPCTalk_GateKeeper(DWORD PlayerID)
{	
	BYTE Dialog[0x5C]={0};
		
	Dialog[0]= 0xC1;
	Dialog[1]= 0x5C;
	Dialog[2]= 0xAA;
	Dialog[3]= 0x06;

	for( int Room = 0; Room < 4; Room++)
	{
		if(DuelRoom[Room] == 1)
		{
			memcpy (&Dialog[4 + Room * 22], gObj_GetNickDuel(Player[0][Room]), 10 );
			memcpy (&Dialog[4+10 + Room * 22], gObj_GetNickDuel(Player[1][Room]), 10 );
			Dialog[4+19+1 + Room * 22]= 0x01;
			Dialog[4+19+2 + Room * 22]= 0x01;				
		}
	}
		
	BYTE buff[4] = { 0xC3 , 0x04 , 0x30 , 0x21 };
	DataSend (PlayerID,buff , buff[1]);
	DataSend( PlayerID , (PBYTE)Dialog , Dialog[1] );	
}

BOOL DuelSystemClass::isInDuelRoom(DWORD PlayerID)
{
	for(int Room = 0;Room < 4;Room++)
	{
		if((Player[0][Room] == PlayerID) || (Player[1][Room] == PlayerID))
		{
			return 1;
		}
	}
	return 0;
}

BYTE DuelSystemClass::GetSpectatorPosition(DWORD PlayerID, BYTE Room)
{
	for(int Pos = 0;Pos < 10;Pos++)
	{
		if(Spectator[Pos][Room] == PlayerID)
		{
			return Pos;
		}
	}
	return 0xFF;
}

BYTE DuelSystemClass::SetSpectator(DWORD PlayerID, BYTE Room)
{
	for(int Pos = 0;Pos < 10;Pos++)
	{
		if(Spectator[Pos][Room] == 0)
		{
			Spectator[Pos][Room] = PlayerID;
			return Pos;
		}
	}
	return 0xFF;	
}

int DuelSystemClass::DuelOK_EnterRoom(DWORD PlayerID1, DWORD PlayerID2)
{
	if(isNewSystem == 1)
	{
		int EnterTo = -1;

		if(isInDuelRoom(PlayerID1) == 0)
		{
			for(int Room = 0;Room < 4;Room++)
			{
				if(DuelRoom[Room] == 0)
				{
					EnterTo = Room;
					DuelRoom[Room] = 1;
					break;
				}
			}

			if(EnterTo != -1)
			{
				Player[0][EnterTo] = PlayerID1;
				Player[1][EnterTo] = PlayerID2;
				WarpRoom(PlayerID1,EnterTo);
				WarpRoom(PlayerID2,EnterTo);

				int ID1=PlayerID1-MIN_PLAYERID;
				int ID2=PlayerID2-MIN_PLAYERID;
				pObjGS[ID1].isInDuelEvent=1;
				pObjGS[ID2].isInDuelEvent=1;
			}
		}

		return EnterTo;
	}else
	{
		return 10;
	}
}

void DuelSystemClass::WarpRoom(DWORD PlayerID, BYTE Room)
{
	int Gate = 0;
	BOOL isSpectator = 0;
	switch(Room)
	{
		case 0:
		{
			if(Player[0][Room] == PlayerID)
			{
				Gate = 295;
			}else if(Player[1][Room] == PlayerID)
			{
				Gate = 296;
			}else
			{
				Gate = 303;
				isSpectator = 1;
			}
		}break;
		case 1:
		{
			if(Player[0][Room] == PlayerID)
			{
				Gate = 297;
			}else if(Player[1][Room] == PlayerID)
			{
				Gate = 298;
			}else
			{
				Gate = 304;
				isSpectator = 1;
			}
		}break;
		case 2:
		{
			if(Player[0][Room] == PlayerID)
			{
				Gate = 299;
			}else if(Player[1][Room] == PlayerID)
			{
				Gate = 300;
			}else
			{
				Gate = 305;
				isSpectator = 1;
			}
		}break;
		case 3:
		{
			if(Player[0][Room] == PlayerID)
			{
				Gate = 301;
			}else if(Player[1][Room] == PlayerID)
			{
				Gate = 302;
			}else
			{
				Gate = 306;
				isSpectator = 1;
			}
		}break;
		case 0xFF:
		{
			Gate = 294;
		}
	}	

	if((isSpectator == 1) && (DuelRoom[Room] == 1))
	{
		if(SetSpectator(PlayerID,Room) != 0xFF)
		{
			gObjMoveGate_JMP(PlayerID, Gate);
			SetDuelInfo(PlayerID,Room);
		} else {
			GCServerMsgStringSend(MSG18,PlayerID, 0x01);
		}
	} else {
		gObjMoveGate_JMP(PlayerID, Gate);
	}
}

void DuelSystemClass__InsideTrigger(void * lpParam)
{
	char sBuf[255] = {0};	//BUFFER for log messages

	while(true)
	{
		for(int Room = 0; Room < 4; Room++)
		{
			for(int i = 0; i < 10; i++)
			{
				if(Duel.Spectator[i][Room] != 0)
				{
					if (Duel.DuelRoom[Room] == 1)
					{
						Duel.SendDuelInfo(Duel.Spectator[i][Room],Room);
						//wsprintf(sBuf, "[Duel System][Spectator][%s][%s] Spectating in Room: %d",GetUser(Duel.Spectator[i][Room]),GetName(Duel.Spectator[i][Room]),Room);
						//LogLine("%s\n",sBuf);
					} else {
						Duel.DeleteSpectator(Duel.Spectator[i][Room],Room);
					}
				}			
			}

			if (Duel.DuelRoom[Room] == 1)
			{
				LPGOBJSTRUCT pObj1 = (LPGOBJSTRUCT)(Duel.Player[0][Room]*gObjSize + gObjBaseAddr);
				LPGOBJSTRUCT pObj2 = (LPGOBJSTRUCT)(Duel.Player[1][Room]*gObjSize + gObjBaseAddr);

				Duel.DuelRoomTotalScore[Room] = pObj1->m_btDuelScore+pObj2->m_btDuelScore;
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void DuelSystemClass__AutoWarpTrigger(void * lpParam)
{
	while(true)
	{
		for(int i=0;i<MAX_PLAYERID-MIN_PLAYERID;i++)
		{
			if (pObjGS[i].isDuelEnded==1)
			{
				pObjGS[i].DuelWarpSeconds+=1;
	
				if (pObjGS[i].DuelWarpSeconds>15)
				{
					pObjGS[i].isDuelEnded=0;
					pObjGS[i].DuelWarpSeconds=0;
					Duel.WarpRoom(i+MIN_PLAYERID,0xFF);
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void DuelSystemClass::DeleteSpectator(DWORD PlayerID, BYTE Room)
{
	//18	transparent
	//27 	full invisible
	int Pos = GetSpectatorPosition(PlayerID,Room);
	
	if (Pos != 0xFF)
	{
		if(gObjIsConnected(PlayerID) == true)
		{
			//Remove Invisibility Skill
//			gObjSkillStruct[PlayerID].Transparent=0;
			CallSkillEffect(PlayerID,18,0x00,PlayerID,1);
			CallSkillEffect(PlayerID,98,0x00,PlayerID,1);
			WarpRoom(PlayerID,0xFF);

			GCServerMsgStringSend(MSG19,PlayerID, 0x01);
		}
		Spectator[Pos][Room] = 0;
	}
}


void DuelSystemClass::SetDuelInfo(DWORD PlayerID, BYTE Room)
{
	if((gObjIsConnected(Player[0][Room]) == true) && (gObjIsConnected(Player[1][Room]) == true))
	{		
		BYTE Packet0[0x0F] = {0xC1,0x0F,0xAA,0x0B, 0x01};
		memcpy (&Packet0[5], gObj_GetNickDuel(PlayerID), 10 );
		DataSend( PlayerID , (PBYTE)Packet0 , Packet0[1] );

		
		//Send Invisibility Skill
		if(!VerifyGM(PlayerID))
		{
			DWORD Encrypt = 0;
			int Serial = 1;
			gObj_Write(PlayerID,gObjCtl,32);
			BYTE aRecv[22]={0xC1,0x16,0x00,0x5A,0x45,0x45,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x2F,0x68,0x69,0x64,0x65,0x5F,0x6F,0x6E,0x00};
			DataRecv(aRecv[2],aRecv,aRecv[1],PlayerID,Encrypt,Serial);
			gObj_Write(PlayerID,gObjCtl,0);
			CallSkillEffect(PlayerID,98,0x01,PlayerID,1);
		}else
		{
			DWORD Encrypt = 0;
			int Serial = 1;
			BYTE aRecv[22]={0xC1,0x16,0x00,0x5A,0x45,0x45,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x2F,0x68,0x69,0x64,0x65,0x5F,0x6F,0x6E,0x00};
			DataRecv(aRecv[2],aRecv,aRecv[1],PlayerID,Encrypt,Serial);
			CallSkillEffect(PlayerID,98,0x01,PlayerID,1);
		}

		BYTE Packet1[0x1E] = {0xC1,0x1E,0xAA,0x07, 0x00, 0x00};
		memcpy (&Packet1[6], gObj_GetNickDuel(Player[0][Room]), 10 );
		memcpy (&Packet1[6+10], gObj_GetNickDuel(Player[1][Room]), 10 );
		Packet1[6+20] = HIBYTE(Player[0][Room]);
		Packet1[6+21] = LOBYTE(Player[0][Room]);
		Packet1[6+22] = HIBYTE(Player[1][Room]);
		Packet1[6+23] = LOBYTE(Player[1][Room]);
		DataSend( PlayerID , (PBYTE)Packet1 , Packet1[1] );

		BYTE Packet2[0x05] = {0xC1,0x05,0xAA,0x0D, 0x98};	
		DataSend( PlayerID , (PBYTE)Packet2 , Packet2[1] );

		BYTE Packet3[0x0A] = {0xC1,0x0A,0xAA,0x04, HIBYTE(Player[0][Room]), LOBYTE(Player[0][Room]), HIBYTE(Player[1][Room]), LOBYTE(Player[1][Room]),gObj_GetInt(Player[0][Room],0xF10),gObj_GetInt(Player[1][Room],0xF10)};
		DataSend( PlayerID , (PBYTE)Packet3 , Packet3[1] );

	}else
	{
		ClearRoom(Room);
	}

}

void DuelSystemClass::SendDuelInfo(DWORD PlayerID, BYTE Room)
{
	if(isNewSystem == 1)
	{
		if((gObjIsConnected(Player[0][Room]) == true) && (gObjIsConnected(Player[1][Room]) == true) && (DuelRoom[Room] == 1))
		{
			BYTE Packet[0x0C] = {0xC1,0x0C,0xAA,0x05, HIBYTE(Player[0][Room]), LOBYTE(Player[0][Room]), HIBYTE(Player[1][Room]), LOBYTE(Player[1][Room])};
			
			LPGOBJSTRUCT pObj1 = (LPGOBJSTRUCT)(Player[0][Room]*gObjSize + gObjBaseAddr);
			LPGOBJSTRUCT pObj2 = (LPGOBJSTRUCT)(Player[1][Room]*gObjSize + gObjBaseAddr);

			int LifePercent1 = (int)((pObj1->Life * 100) / (pObj1->MaxLife + pObj1->AddLife));
			int ShieldPercent1 = (int)((pObj1->iShield * 100) / (pObj1->iMaxShield + pObj1->iAddShield));
			int LifePercent2 = (int)((pObj2->Life * 100) / (pObj2->MaxLife + pObj2->AddLife));
			int ShieldPercent2 = (int)((pObj2->iShield * 100) / (pObj2->iMaxShield + pObj2->iAddShield));

			Packet[8]  = LifePercent1;
			Packet[9]  = LifePercent2; 
			Packet[10] = ShieldPercent1; 
			Packet[11] = ShieldPercent2; 
			DataSend( PlayerID , (PBYTE)Packet , Packet[1] );

			if (Duel.DuelRoomTotalScore[Room] != (pObj1->m_btDuelScore+pObj2->m_btDuelScore))
			{
				PMSG_DUEL_SCORE pMsg;

				pMsg.hc = 0xC1;
				pMsg.size = sizeof(pMsg);
				pMsg.headcode = 0xAA;
				pMsg.subcode = 0x04;
				pMsg.NumberH1 = HIBYTE(Player[0][Room]);
				pMsg.NumberL1 = LOBYTE(Player[0][Room]);
				pMsg.NumberH2 = HIBYTE(Player[1][Room]);
				pMsg.NumberL2 = LOBYTE(Player[1][Room]);
				pMsg.btDuelScore1 = pObj1->m_btDuelScore;
				pMsg.btDuelScore2 = pObj2->m_btDuelScore;
				DataSend( PlayerID , (BYTE*)&pMsg , pMsg.size );
			}

			//char _debuginfoNew1[1024]="\x00";
			//ToHex((unsigned char *)_debuginfoNew1, Packet, Packet[1]);
			//wsprintf(sBuf, "[Data SEND][NEW][AA][Duel System][%s] %s",GetName(PlayerID),_debuginfoNew1);
			//LogLine("%s\n", sBuf);
		} else {
			DeleteSpectator(PlayerID,Room);			
		}
	}
}

void DuelSystemClass::ClearRoom(BYTE Room)
{
	DuelRoom[Room] = 0;
	DuelRoomTotalScore[Room] = 0;
	Player[0][Room]= 0;
	Player[1][Room]= 0;

	for(int i = 0; i < 10; i++)
		Spectator[i][Room] = 0;
}


void DuelSystemClass::ClearRoombyPlayerID(DWORD PlayerID)
{
	char sBuf[255] = {0};

	//Still Need add buff to Winner
	if(isNewSystem == 1)
	{
		for(int Room = 0; Room < 4; Room++)
		{
			if((Player[0][Room] == PlayerID) || (Player[1][Room] == PlayerID))
			{
				GCServerMsgStringSend(MSG20,Player[0][Room], 0x01);
				GCServerMsgStringSend(MSG20,Player[1][Room], 0x01);

				//Get Winner
				int ScoreLoose,ScoreWin,WinID;
				LPSTR NameLoose,NameWin;

				LPGOBJSTRUCT pObjFirst = (LPGOBJSTRUCT)(Player[0][Room]*gObjSize + gObjBaseAddr);
				LPGOBJSTRUCT pObjSecond = (LPGOBJSTRUCT)(Player[1][Room]*gObjSize + gObjBaseAddr);
				
				if (pObjFirst->m_btDuelScore > pObjSecond->m_btDuelScore)
				{
					ScoreLoose = pObjSecond->m_btDuelScore;
					NameLoose = pObjSecond->Name;

					ScoreWin = pObjFirst->m_btDuelScore;
					NameWin = pObjFirst->Name;
					WinID = pObjFirst->m_Index;
				} else {
					ScoreLoose = pObjFirst->m_btDuelScore;
					NameLoose = pObjFirst->Name;

					ScoreWin = pObjSecond->m_btDuelScore;
					NameWin = pObjSecond->Name;
					WinID = pObjSecond->m_Index;
				}

				this->SendEndDuelNotification(WinID, NameWin, NameLoose);

				
				int ID1=Player[0][Room]-MIN_PLAYERID;
				int ID2=Player[1][Room]-MIN_PLAYERID;
				pObjGS[ID1].isInDuelEvent=0;
				pObjGS[ID1].isDuelEnded=1;
				pObjGS[ID2].isInDuelEvent=0;
				pObjGS[ID2].isDuelEnded=1;

				wsprintf(sBuf, MSG21,Room+1,NameWin,NameLoose);
				SendNoticeToAll(sBuf);
				Log.outInfo("%s\n",sBuf);
				wsprintf(sBuf, MSG22,Room+1,ScoreWin,ScoreLoose);
				SendNoticeToAll(sBuf);
				Log.outInfo("%s\n",sBuf);
				

				DuelRoom[Room] = 0;
				DuelRoomTotalScore[Room] = 0;
				Player[0][Room]= 0;
				Player[1][Room]= 0;

				break;
			}
		}
	}
}


void DuelSystemClass::Init()
{
	isNewSystem  = GetPrivateProfileInt("DuelSystem", "DuelSystemEnabled",1, "..\\OptionsData\\Options.ini") ;
	MinLevel	 = GetPrivateProfileInt("DuelSystem", "DuelSystemMinLevelRequestAccept",1, "..\\OptionsData\\Options.ini") ;
	//Clear Duel Rooms
		for(int Room = 0; Room < 4; Room++)
			ClearRoom(Room);

		//Clear Player Structure
		for(int i=0;i<(MAX_PLAYERID-MIN_PLAYERID);i++)
		{
			pObjGS[i].isInDuelEvent=0;
			pObjGS[i].isDuelEnded=0;
			pObjGS[i].DuelWarpSeconds=0;
		}
	//Start Event Thread
	_beginthread( DuelSystemClass__InsideTrigger, 0, NULL  );
	
	_beginthread( DuelSystemClass__AutoWarpTrigger, 0, NULL  );
}
