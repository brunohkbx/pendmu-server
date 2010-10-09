/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/
//Includes & Defines
#include "Protocols.h"
#include "GameServer.h"
#include "Global.h"
#include "ChatCore.h"
#include "User.h"
//#include "DropItem.h"
#include "Creature.h"
#include "Log.h"
#include "Common.h"
#include "DuelSystem.h"
#include "PCpoints.h"
#include "NPC.h"
#include "Structure.h"
#include "CQuestSystem.h"
#include "ChaosMachine.h"
#include "MoveReq.h"

BYTE RecvTable[256]  =  {
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
		0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0xD7,0x1E,0x1F,
		0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
		0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
		0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
		0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
		0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
		0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
		0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
		0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
		0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
		0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
		0xD0,0xD1,0xD2,0x1D,0xD4,0xD5,0xD6,0xDC,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xD6,
		0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
		0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF 
	} ;

extern BYTE RecvTable[256];
//Protocol Server-->Client
BYTE ProtocolServer(BYTE Type)
{

	if(Config.IsProtocol == 0) //KOR
	{
		switch(Type)
		{
			case 0x1D: return 0xD3; //Walk
			case 0xD6: return 0xDF; //Movefix
			case 0xDC: return 0xD7; //Attack
			//case 0xD7: return 0x10; //MagicSkill
		}
	}
	/*
	else if(Config.IsProtocol == 1) //JPN
	{
		switch(Type)
		{
			case 0x1D: return 0x1D; //Walk
			case 0xD6: return 0xD6; //Movefix
			case 0xDC: return 0xDC; //Attack
			//case 0xD7: return 0xD7; //MagicSkill
		}
	}
	*/
	else if(Config.IsProtocol == 2) //VTM
	{
		switch(Type)
		{
			case 0x1D: return 0xD9; //Walk
			case 0xD6: return 0xDC; //Movefix
			case 0xDC: return 0x15; //Attack
			//case 0xD7: return 0x1D; //MagicSkill
		}
	}
	else if(Config.IsProtocol == 3) //ENG
	{
		switch(Type)
		{
			case 0x1D: return 0xD4; //Walk
			case 0xD6: return 0x15; //Movefix
			case 0xDC: return 0x11; //Attack
			//case 0xD7: return 0xD7; //MagicSkill
		}
	}
	else if(Config.IsProtocol == 4) //CHS
	{
		switch(Type)
		{
			//case 0x1D: return 0xD7; //Walk 1D
			case 0xD6: return 0xD7; //Movefix
			case 0xDC: return 0xD9; //Attack 
			//case 0xD7: return 0x1D; //MagicSkill
		}
	}
	else
	{
		switch(Type)
		{
			case 0x1D: return 0xD3; //Walk
			case 0xD6: return 0xDF; //Movefix
			case 0xDC: return 0xD7; //Attack
			//case 0xD7: return 0x10; //MagicSkill
		}
	}

	return Type;
}

//Protocol Client-->Server
BYTE ProtocolClient(BYTE Type)
{	
	if(Config.IsProtocol == 0) //KOR
	{
		switch(Type)
		{
			case 0xD3: return 0x1D; //Walk
			case 0xDF: return 0xD6; //Movefix
			case 0xD7: return 0xDC; //Attack
			//case 0x10: return 0xD7; //MagicSkill
		}
	}
	/*
	else if(Config.IsProtocol == 1) //JPN
	{
		switch(Type)
		{
			case 0x1D: return 0x1D; //Walk
			case 0xD6: return 0xD6; //Movefix
			case 0xDC: return 0xDC; //Attack
			//case 0xD7: return 0xD7; //MagicSkill
		}
	}
	*/
	else if(Config.IsProtocol == 2) //VTM
	{
		switch(Type)
		{
			case 0xD9: return 0x1D; //Walk 
			case 0xDC: return 0xD6; //Movefix
			case 0x15: return 0xDC; //Attack
			//case 0x1D: return 0xD7; //MagicSkill
		}
	}
	else if(Config.IsProtocol == 3) //ENG
	{
		switch(Type)
		{
			case 0xD4: return 0x1D; //Walk
			case 0x15: return 0xD6; //Movefix
			case 0x11: return 0xDC; //Attack
			//case 0xD7: return 0xD7; //MagicSkill
		}
	}
	else if(Config.IsProtocol == 4) //CHS
	{
		switch(Type)
		{
			//case 0xD7: return 0x1D; //Walk 1D
			case 0xD7: return 0xD6; //Movefix
			case 0xD9: return 0xDC; //Attack D9
			//case 0x1D: return 0xD7; //MagicSkill

		}
	}
	else
	{
		switch(Type)
		{
			case 0xD3: return 0x1D; //Walk
			case 0xDF: return 0xD6; //Movefix
			case 0xD7: return 0xDC; //Attack
			//case 0x10: return 0xD7; //MagicSkill
		}
	}
	
	return Type;
}


//Something with "Protocol of skills"
WORD MakeWord(BYTE loByte,BYTE hiByte)
{
	WORD x=0;

	_asm
	{
		XOR EAX,EAX
		MOV AL, loByte
		MOV AH, hiByte
		MOV x, AX
	}

	return x;
}


//Protocol Core
bool ProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial)
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	//BYTE pProtocol[pMaxLen] ;
	//memcpy (pProtocol,aRecv,aLen+1 );
	BYTE ProtocolType = aRecv[0];
	switch (ProtocolType)
	{
		case 0xC1:
			if(Config.IsProtocol==0)
			{
				switch(BYTE(protoNum))
				{
					case 0x10:
						protoNum = 0xD7;
						aRecv[2] = 0xD7;
						break;
					case 0xF1:
					// FIx Login
						aRecv[1] -= 0x02;
						aLen = aRecv[1];
						int i;
						for(i = 24; i<50; i++)
						aRecv[i] = aRecv[i+2];
						break;
				
				
				case 0xD0:
					if(aRecv[1]== 0x04&&aRecv[3] == 0x06)
					{
						PCPoint.OpenShop(aIndex);
						return true;
					}
					if(aRecv[3] == 0x05)
					{
						PCPoint.BuyItem(aIndex,aRecv[4]);
						return true;
					}
					break;

				}
			}
		
			else if(Config.IsProtocol==1) //JPN
			{
				switch(BYTE(protoNum))
				{
					/*
					case 0xD7:
						protoNum = 0xD7;
						aRecv[2] = 0xD7;
						break;
						*/
					case 0xD0:
						if(aRecv[1]== 0x04&&aRecv[3] == 0x06)
						{
							PCPoint.OpenShop(aIndex);
							return true;
						}
						if(aRecv[3] == 0x05)
						{
							PCPoint.BuyItem(aIndex,aRecv[4]);
							return true;
						}
						break;
				}
			}
			else if(Config.IsProtocol == 2) //VTM
			{
				switch(BYTE(protoNum))
				{
					case 0x10:
						protoNum = 0xD7;
						aRecv[2] = 0xD7;
						break;
				}
			}

			else if(Config.IsProtocol == 3) //ENG
			{
				switch(BYTE(protoNum))
				{
					case 0xDB:
						protoNum = 0xD7;
						aRecv[2] = 0xD7;
						break;
				}
			}

			else if(Config.IsProtocol == 4) //CHS
			{
				switch(BYTE(protoNum))
				{
				case 0x1D:
					protoNum = 0xD7;
					aRecv[2] = 0xD7;
					break;
				}
			}
			break;
	}


		switch(BYTE(protoNum))
		{
			case 0x00: //Move & chat Protocol
			{
				ChatSystem.ChatDataSend(aIndex,aRecv);				
			}		
			break;	
		
		case 0x03:
			{
				int Map = (int)gObj_GetMap(aIndex);
				if(Map == 64)gObjMoveGate_JMP(aIndex, 294);

				//SetPCPoint(aIndex);
				//PCPoint.SQLGetPoints(aIndex);
				PCPoint.GetInfo(aIndex);
				GCServerMsgStringSend(ConnectNotice1,aIndex,0);
				GCServerMsgStringSend(ConnectNotice2,aIndex,0);
				GCServerMsgStringSend(ConnectNotice3,aIndex,0);
				g_Quest.LoadQuest(aIndex);
				conLog.ConsoleOutputDT("[%s][%s][%d] Connect.",gObj->AccountID,gObj->Name,aIndex);
#ifdef Season5
		if(gObj->pInventory[RING_01].m_Type == 0x1A7A || gObj->pInventory[RING_02].m_Type == 0x1A7A) //SKeleton Ring
		{
			gObj->m_Change = 14;
			gObjViewportListProtocolCreate(gObj);
		}


				//Load Quest Pending
				BYTE Packet3[6]={0xC1,0x05,0xF6,0x0F,0x255,0x00};
				BYTE Packet4[6]={0xC1,0x05,0xF7,0x0F,0x255,0x00};

				Log.outError("Season 5 Quest System");
				DataSend(aIndex, &Packet3[0], Packet3[1]);
				DataSend(aIndex, &Packet4[0], Packet4[1]);
		
#endif
			
			}
			break;
#ifdef Season5
			

	//case 0x06:
	//	CGLevelUpPointAdd((PMSG_LVPOINTADD *)aRecv, aIndex);
	//	break;
	case 0xF1://Login protocol (Season 5)
		{
			aRecv[1] -= 0x02;
			aLen = aRecv[1];
			for (int i = 24; i<52; i++)
				aRecv[i] = aRecv[i+2];
			
		}break;

	case 0xF6://New S5 Packet
		{
			BYTE Packet3[6]={0xC1,0x05,0xF6,0x0F,0x255,0x00};
			BYTE Packet4[6]={0xC1,0x05,0xF7,0x0F,0x255,0x00};
			BYTE pNewProtocol[0x05]={0xC1,0x05,0x18,0x01,0x7A};
			DataRecv(RecvTable[pNewProtocol[2]], pNewProtocol, pNewProtocol[1], aIndex, Encrypt, Serial );
			//SCFPanelInfoSend(aIndex);
			//	return true;

			Log.outError("Season 5 Quest System");
			DataSend(aIndex, &Packet3[0], Packet3[1]);
			return true;
		}
		break;

	case 0x8E: //S5 Warp Menu Fix
			if(gObj->m_iDuelUser == -1)
			{
			g_MoveReq.Teleport(aIndex,aRecv[8]);
			}
			return true;
		break;
	case 0x24: //Panda Fix (Equip Guardian)

			if(aRecv[4] == RING_01 || aRecv[4] == RING_02)
				{
					if(gObj->m_Change == 14) //SKeleton Ring
					{
						gObj->m_Change = -1;
						gObjViewportListProtocolCreate(gObj);
					}
				}
	break;

	case 0x86: // Chaos Machine (New Wing Mix)
		ChaosboxCombinationEx(aIndex,aRecv[3]);
	break;
		//IN WORK - Imperial Guardian and Double Goer EVENT PROTOCOLS
		/*	case 0xF7:		
			Imperial.CheckCanEnter(aIndex);
			return true;
		break;
	case 0xBF: // Season 5 Double Goer Event
		{

			if(aRecv[1] == 0x05 && aRecv[3] == 0x0E)
			{
				DoubleGoer.EnterDoubleGoer(aIndex,(int)aRecv[4]+12);
				return true;
			}
			
		}break;
	case 0xDC: //Can't Kill Gate, while Event not started, or in standby. ^^
			if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 0)
			{	
				return true;
			}
			else if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 1)
			{
				for(int i=0;i<ImperialGateCfg.nGateOfEvent;i++)
				{	
					if(ImperialGateCfg.GatesID[i] != 0)
					{
						if((aRecv[4] + aRecv[3] * 256) == ImperialGateCfg.GatesID[i]  && ImperialGateCfg.GatesNum[i] != 1)
						{
						//Messages.outYellow(aIndex,"Attack Gate : %d %d",(aRecv[4] + aRecv[3] * 256), ImperialGateCfg.GatesID[i]);
						return true;
						}
					}
				}
				//Messages.outYellow(aIndex,"Attack Mob : %d",(aRecv[4] + aRecv[3] * 256));
			}
		break;
	case 0x19: //Can't Kill Gate, while Event not started, or in standby. ^^
		if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 0)
			{	
				return true;
			}
		else if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 1)
			{
				for(int i=0;i<ImperialGateCfg.nGateOfEvent;i++)
				{	
				if(ImperialGateCfg.GatesID[i] != 0)
					{
						if((aRecv[6] + aRecv[5] * 256) == ImperialGateCfg.GatesID[i]  && ImperialGateCfg.GatesNum[i] != 1)
						{
						//Messages.outYellow(aIndex,"Attack Gate : %d %d",(aRecv[6] + aRecv[5] * 256), ImperialGateCfg.GatesID[i]);
						return true;
						}
					}
				}
			}
		break;
	case 0x10: //Can't Kill Gate, while Event not started, or in standby. ^^
		if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 0)
			{	
				return true;
			}
		else if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 1)
			{	
				for(int i=0;i<ImperialGateCfg.nGateOfEvent;i++)
				{	
					if(ImperialGateCfg.GatesID[i] != 0)
					{
						if((aRecv[10] + aRecv[9] * 256) == ImperialGateCfg.GatesID[i]  && ImperialGateCfg.GatesNum[i] != 1)
						{
						//Messages.outYellow(aIndex,"Attack Gate : %d %d",(aRecv[10] + aRecv[9] * 256), ImperialGateCfg.GatesID[i]);
						return true;
						}
					}
				}
			}
		break;
	case 0x1E: //Can't Kill Gate, while Event not started, or in standby. ^^
		if(Imperial.EventDay == 1)
			{	
				if(gObj->MapNumber == 69)
				{
					if(gObj->Y >= 52 && (gObj->X > 230 && gObj->X < 236) && Imperial.CanUseTwisting == 0) //Gate 2
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 77 && gObj->Y <= 82) && (gObj->X >= 216 && gObj->X <= 219) && Imperial.CanUseTwisting == 0) //Gate 3
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 22 && gObj->Y <= 29) && (gObj->X >= 193 && gObj->X <= 197) && Imperial.CanUseTwisting == 0) //Gate 4
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 22 && gObj->Y <= 29) && (gObj->X >= 166 && gObj->X <= 170) && Imperial.CanUseTwisting == 0) //Gate 5
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 50 && gObj->Y <= 70) && (gObj->X >= 152 && gObj->X <= 157) && Imperial.CanUseTwisting == 0) //Gate 6
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 76 && gObj->Y <= 80) && (gObj->X >= 178 && gObj->X <= 184) && Imperial.CanUseTwisting == 0) //Gate 7
					{
						if(aRecv[4] == 0x29) return true;
					}
				}
			}
		if(Imperial.EventDay == 2)
			{	
				if(gObj->MapNumber == 70)
				{
					if((gObj->Y >= 61 && gObj->Y <= 68) && (gObj->X > 50 && gObj->X < 54) && Imperial.CanUseTwisting == 0) //Gate 2
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 63 && gObj->Y <= 66) && (gObj->X >= 19 && gObj->X <= 21) && Imperial.CanUseTwisting == 0) //Gate 3
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 90 && gObj->Y <= 92) && (gObj->X >= 34 && gObj->X <= 39) && Imperial.CanUseTwisting == 0) //Gate 4
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 114 && gObj->Y <= 116) && (gObj->X >= 38 && gObj->X <= 45) && Imperial.CanUseTwisting == 0) //Gate 5
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 151 && gObj->Y <= 153) && (gObj->X >= 53 && gObj->X <= 57) && Imperial.CanUseTwisting == 0) //Gate 6
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 108 && gObj->Y <= 113) && (gObj->X >= 107 && gObj->X <= 109) && Imperial.CanUseTwisting == 0) //Gate 7
					{
						if(aRecv[4] == 0x29) return true;
					}
				}
			}
		if(Imperial.EventDay == 3)
			{	
				if(gObj->MapNumber == 71)
				{
					if((gObj->Y >= 190 && gObj->Y <= 195) && (gObj->X > 119 && gObj->X < 122) && Imperial.CanUseTwisting == 0) //Gate 2
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 192 && gObj->Y <= 198) && (gObj->X >= 89 && gObj->X <= 92) && Imperial.CanUseTwisting == 0) //Gate 3
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 131 && gObj->Y <= 133) && (gObj->X >= 220 && gObj->X <= 226) && Imperial.CanUseTwisting == 0) //Gate 4
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 157 && gObj->Y <= 159) && (gObj->X >= 220 && gObj->X <= 226) && Imperial.CanUseTwisting == 0) //Gate 5
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 190 && gObj->Y <= 192) && (gObj->X >= 220 && gObj->X <= 226) && Imperial.CanUseTwisting == 0) //Gate 6
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 215 && gObj->Y <= 217) && (gObj->X >= 165 && gObj->X <= 170) && Imperial.CanUseTwisting == 0) //Gate 7
					{
						if(aRecv[4] == 0x29) return true;
					}
				}
			}
		if(Imperial.EventDay == 4)
			{	
				if(gObj->MapNumber == 72)
				{
					if((gObj->Y >= 66 && gObj->Y <= 70) && (gObj->X >= 50 && gObj->X <= 52) && Imperial.CanUseTwisting == 0) //Gate 2
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 92 && gObj->Y <= 90) && (gObj->X >= 30 && gObj->X <= 35) && Imperial.CanUseTwisting == 0) //Gate 3
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 174 && gObj->Y <= 176) && (gObj->X >= 31 && gObj->X <= 37) && Imperial.CanUseTwisting == 0) //Gate 4
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 188 && gObj->Y <= 194) && (gObj->X >= 50 && gObj->X <= 52) && Imperial.CanUseTwisting == 0) //Gate 5
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 190 && gObj->Y <= 192) && (gObj->X >= 220 && gObj->X <= 226) && Imperial.CanUseTwisting == 0) //Gate 6
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 129 && gObj->Y <= 135) && (gObj->X >= 155 && gObj->X <= 157) && Imperial.CanUseTwisting == 0) //Gate 7
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 129 && gObj->Y <= 135) && (gObj->X >= 195 && gObj->X <= 197) && Imperial.CanUseTwisting == 0) //Gate 8
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 157 && gObj->Y <= 159) && (gObj->X >= 222 && gObj->X <= 227) && Imperial.CanUseTwisting == 0) //Gate 9
					{
						if(aRecv[4] == 0x29) return true;
					}

					if((gObj->Y >= 21 && gObj->Y <= 28) && (gObj->X >= 214 && gObj->X <= 216) && Imperial.CanUseTwisting == 0) //Gate 10
					{
						if(aRecv[4] == 0x29) return true;
					}
				}
			}
		if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 0)
			{	
				if(aRecv[4] == 0x29) return true;
			}
		//else if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 1)
		//	{   
		//		if(aRecv[4] == 0x29) return true;
		//	}
		break;
	case 0xD7: //Can't Kill Gate, while Event not started, or in standby. ^^
		if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 0)
			{	
				return true;
			}
		else if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(aIndex)] == 1 && ImperialMain.Status == 1)
			{
				for(int i=0;i<ImperialGateCfg.nGateOfEvent;i++)
				{	
					if(ImperialGateCfg.GatesID[i] != 0)
					{
						if((aRecv[10] + aRecv[9] * 256) == ImperialGateCfg.GatesID[i]  && ImperialGateCfg.GatesNum[i] != 1)
						{
						//Messages.outYellow(aIndex,"Attack Gate : %d %d",(aRecv[10] + aRecv[9] * 256), ImperialGateCfg.GatesID[i]);
						return true;
						}
					}
				}
			}
		break; */

#endif
		case 0x30:
		    NPCTalkEx(aIndex, (aRecv[4] + aRecv[3] * 256));
		break;

		case 0x95:
			{
				DWORD Address=0x00;
				BYTE MyTable[2]={aRecv[4],aRecv[3]};
				memcpy(&Address,&MyTable,sizeof(MyTable));
				GoldenArcher(aIndex,Address);
				//Log Tracing
				//conLog.ConsoleOutput("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",aRecv[0],aRecv[1],aRecv[2],aRecv[3],aRecv[4],aRecv[5],aRecv[6],aRecv[7],aRecv[8],aRecv[9],aRecv[10],aRecv[11],aRecv[12],aRecv[13],aRecv[14],aRecv[15],aRecv[16],aRecv[17],aRecv[18],aRecv[19],aRecv[20],aRecv[21],aRecv[22],aRecv[23],aRecv[24],aRecv[25],aRecv[26],aRecv[27],aRecv[28],aRecv[29],aRecv[30]);
			}
			break;

		case 0xBC: // Lahap dupe
			{
				int Error = 0;
		
				for(int i = 8000; i<9000; i++)
				{
					if(gObj->TargetNumber == i)
					Error = 1;
			
					if(Error)
					break;
				}
		
				if(Error)
				{
					Log.outError("[%s][%s] ANTI-HACK [LAHAP PACKET]",gObj->AccountID,gObj->Name);
					conLog.ConsoleOutputDT("[%s][%s] ANTI-HACK [LAHAP PACKET]",gObj->AccountID,gObj->Name);
					return true;
				}
			}
			break;

		case 0xAA:
		{
			if (Duel.isNewSystem==1)
			{
				if(aRecv[3]==0x01)
				{
					//Log Tracing
					//conLog.ConsoleOutput("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",aRecv[0],aRecv[1],aRecv[2],aRecv[3],aRecv[4],aRecv[5],aRecv[6],aRecv[7],aRecv[8],aRecv[9],aRecv[10],aRecv[11],aRecv[12],aRecv[13],aRecv[14],aRecv[15],aRecv[16],aRecv[17],aRecv[18],aRecv[19],aRecv[20],aRecv[21],aRecv[22],aRecv[23],aRecv[24],aRecv[25],aRecv[26],aRecv[27],aRecv[28],aRecv[29],aRecv[30]);
					
#ifdef GameServer90_CS
					//Fake Packet
					BYTE pNewProtocol[0x05]={0xC1,0x05,0x18,0x01,0x7A};
					DataRecv (RecvTable[pNewProtocol[2]], pNewProtocol, pNewProtocol[1], aIndex, Encrypt, Serial );
					GCServerMsgStringSend("Can't Duel In This Server",aIndex, 0x01);
					return true;
#endif
#ifdef GameServer90
					DWORD TargetID=0x00;
					BYTE ConCatenate[2]={aRecv[5],aRecv[4]};
					memcpy(&TargetID,&ConCatenate,sizeof(ConCatenate));
					
					
					int playerLevel = gObj_GetLevel(aIndex);
					int targetLevel = gObj_GetLevel(TargetID);
					if((playerLevel < Duel.MinLevel) || (targetLevel < Duel.MinLevel))
					{
						//Fake Packet
						BYTE pNewProtocol[0x05]={0xC1,0x05,0x18,0x01,0x7A};
						DataRecv (RecvTable[pNewProtocol[2]], pNewProtocol, pNewProtocol[1], aIndex, Encrypt, Serial );
						char sbuf[255]={0};
						wsprintf(sbuf,MSG23,Duel.MinLevel);
						GCServerMsgStringSend(sbuf,aIndex, 0x01);
						return true;
					}
					//Save User IDs for eachother
					pObjGS[aIndex-MIN_PLAYERID].DuelRequested=TargetID;
					pObjGS[TargetID-MIN_PLAYERID].DuelRequested=aIndex;
					
					//Create New Packet
					BYTE pNewLen=aRecv[1]-1;
					aRecv[0] = 0xC1;
					aRecv[1] = pNewLen;
					aRecv[2] = 0xAA;
					memcpy (&aRecv[3], &aRecv[4], pNewLen-4 );
					DataRecv(protoNum, aRecv, pNewLen, aIndex, Encrypt, Serial );
					return true;
				}
				if(aRecv[3] == 0x02)
				{
					if(aRecv[4] == 0x00)
					{
						DWORD TargetID = 0;
						BYTE ConCatenate[2]={aRecv[6],aRecv[5]};
						memcpy(&TargetID,&ConCatenate,2);
						BYTE aRecv[5]={0xC1,0x05,0xAA,0x03,0x00};
						DataSend ( TargetID, aRecv ,aRecv[1]);
						gObj_Write(TargetID,0xF04,-1);
						gObj_Write(aIndex,0xF08,-1);
						return true;
					}
					BYTE pNewLen=aRecv[1]-2;
					aRecv[0] = 0xC1;
					aRecv[1] = pNewLen;
					aRecv[2] = 0xAC;
					memcpy (&aRecv[3], &aRecv[4], pNewLen-3 );
					protoNum = 0xAC;
					DataRecv(protoNum, aRecv, pNewLen, aIndex, Encrypt, Serial );
					return true;
				}
				if(aRecv[3] == 0x07)
				{
					//Fake Packet
					BYTE pNewProtocol[0x05]={0xC1,0x05,0x18,0x01,0x7A};
					DataRecv(RecvTable[pNewProtocol[2]], pNewProtocol, pNewProtocol[1], aIndex, Encrypt, Serial );
					Duel.WarpRoom(aIndex,aRecv[4]);
					return true;
				}
#endif
			}
		}
		break;
		}
	
	
	DataRecv(protoNum,aRecv,aLen,aIndex,Encrypt,Serial);
	return true;
	}



void ProtocolCoreSend(DWORD PlayerID,PBYTE tpProtocol,DWORD ProtocolLen)
{
	int iKorSend = 0;
	BYTE pNewProtocol[pMaxLen];
	DWORD dwNewLen = 0;
	BYTE ProtocolType;
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(PlayerID);
	/*
	switch(tpProtocol[0])
	{
	case 0xC1:
		switch(tpProtocol[2])
		{

			case 0x17: // NPC Die
			//DieNPCEx(aIndex,(aSend[4] + aSend[3] * 256));
				//PCPoint.IncreasePoints(PlayerID,3);
			break;
			
			case 0xF3:
			switch(tpProtocol[3])
			{
			case 0x05: // Level Up
				//PCPoint.IncreasePoints(PlayerID,UpPoints);
				break;
			}
			break;		
		}
		break;
		
	}
	*/

	if (tpProtocol[0] < (BYTE)0xC1 || tpProtocol[0] > (BYTE)0xC4) 
	{
		return;
	}

	if ((tpProtocol[0] == (BYTE)0xC1) || tpProtocol[0] == (BYTE)0xC3)
	{
		ProtocolType  = tpProtocol[2] ;
	}

	else
	{
		ProtocolType  = tpProtocol[3] ;
	}

	switch (ProtocolType)
	{
#ifdef GameServer90
		case 0xAA:			//DUEL DIALOG SEND TO OPPONENT ANS
		{
			if ((Duel.isNewSystem == 1))
			{

				DWORD TargetID;
				BYTE ConCatenate[2]={tpProtocol[5],tpProtocol[4]};
				memcpy(&TargetID,&ConCatenate,2);


				PBYTE pProtocol = tpProtocol;
				iKorSend=1 ;
				dwNewLen=0x11 ;
				pNewProtocol[0]= 0xC1;
				pNewProtocol[1]= dwNewLen;
				pNewProtocol[2]= 0xAA;
				pNewProtocol[3]= 0x01;
				if(pProtocol[4]==0x00)
				{
					pNewProtocol[4]= 0x0F;		//CANCEL
				}
				else
				{
					pNewProtocol[4]= 0x00;		//OK
				}
				memcpy (&pNewProtocol[5], &pProtocol[4], dwNewLen-4 );
				if(pNewProtocol[4] == 0x00)
				{					
					Duel.DuelOK_EnterRoom(pObjGS[PlayerID-MIN_PLAYERID].DuelRequested,PlayerID);
					//return;
					// --------------------------
				}
			}
		}
		break;

		case 0xAB:			//END DUEL
		{
			if (Duel.isNewSystem==1)
			{
				PBYTE pProtocol = tpProtocol;
				iKorSend=1 ;
				dwNewLen=0x05 ;
				pNewProtocol[0]= 0xC1;
				pNewProtocol[1]= dwNewLen;
				pNewProtocol[2]= 0xAA;
				pNewProtocol[3]= 0x03;
				pNewProtocol[4]= 0x00;
				//BYTE Win = 0;
	
				//if(pProtocol[5] == 0x53)
				//{
				//	Win = 1;
				//}

				Duel.ClearRoombyPlayerID(PlayerID);
			}
		}break;

		case 0xAC:			//DUEL DIALOG SEND TO OPPONENT
		{
			if (Duel.isNewSystem==1)
			{
				PBYTE pProtocol = tpProtocol;
				iKorSend=1 ;
				dwNewLen=0x10 ;
				pNewProtocol[0]= 0xC1;
				pNewProtocol[1]= dwNewLen;
				pNewProtocol[2]= 0xAA;
				pNewProtocol[3]= 0x02;
				memcpy (&pNewProtocol[4], &pProtocol[3], dwNewLen-3 );
			}
		}
		break;

		case 0xAD:			//DUEL SCORE SEND
		{
			if (Duel.isNewSystem==1)
			{

				PBYTE pProtocol = tpProtocol;
				iKorSend=1 ;
				dwNewLen=0x0A ;
				pNewProtocol[0]= 0xC1;
				pNewProtocol[1]= dwNewLen;
				pNewProtocol[2]= 0xAA;
				pNewProtocol[3]= 0x04;
				memcpy (&pNewProtocol[4], &pProtocol[3], dwNewLen-3 );
			}
			
		}
		break;
#endif
	}

	if(iKorSend == 1)
		DataSend(PlayerID, pNewProtocol ,dwNewLen);
	else
		DataSend ( PlayerID, tpProtocol ,ProtocolLen);
}
