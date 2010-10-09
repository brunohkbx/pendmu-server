//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;//
// Advanced Coderz Group SoftWare		//
// Imperial Guardian Fort Event Source	//
// Fully Coded by SmallHabit			//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;//


#include "stdafx.h"
#include "ImperialEvent.h"
#include "GameServer.h"
#include "User.h"
#include "Utils.h"
#include "Log.h"


IMPERIALCONFIGSTRUCT ImperialConfig;
IMPERIALMAINSTRUCT ImperialMain;
IMPERIALMONSTERCFGSTRUCT ImperialMobCfg;
IMPERIALGATECFGSTRUCT ImperialGateCfg;
ImperialEvent Imperial;

void ImperialFort_StartStandBy(void * lpParam);
void ImperialFort_StartStage1(void * lpParam);
void ImperialFort_StartStage2(void * lpParam);
void ImperialFort_CheckState(void * lpParam);
void ImperialFort_GateCloseTimer(void * lpParam);
void ImperialFort_StandBy(void * lpParam);
void ImperialFort_StandBy2(void * lpParam);
void ImperialFort_StartStage3(void * lpParam);
void DieRegen(void * lpParam);

void ImperialEvent::ImperialLoadConfig()
{	
	char FileName[] = "..//OptionsData//Events//ImperialEvent.ini";
	ImperialConfig.MinimumLevel = GetPrivateProfileInt("ImperialGuardianFort", "ImperialEventReqLevel", 15, FileName);
	ImperialConfig.CheckInvite = GetPrivateProfileInt("ImperialGuardianFort", "ImperialEventCheckPaper", 1, FileName);
}

void ImperialEvent::Init()
{	
	SYSTEMTIME t;
	GetLocalTime(&t);

	if(t.wDayOfWeek == 1 || t.wDayOfWeek == 4){ Imperial.EventDay = 1; }
	else if(t.wDayOfWeek == 2 || t.wDayOfWeek == 5){ Imperial.EventDay = 2; }
	else if(t.wDayOfWeek == 3 || t.wDayOfWeek == 6){ Imperial.EventDay = 3; }
	else if(t.wDayOfWeek == 0){ Imperial.EventDay = 4; }

	if(Imperial.EventDay == 1)
	{
	//gObjTeleport(i,69,231,14);
	Imperial.EventMap = 69;
	}
	else if(Imperial.EventDay == 2)
	{
	//gObjTeleport(i,70,86,66);
	Imperial.EventMap = 70;
	}
	else if(Imperial.EventDay == 3)
	{
	//gObjTeleport(i,71,154,186);
	Imperial.EventMap = 71;
	}
	else if(Imperial.EventDay == 4)
	{
	//gObjTeleport(i,72,93,67);
	Imperial.EventMap = 72;
	}

	ImperialLoadConfig();

	ImperialMobCfg.nMonsterOfEvent = 0;
	ImperialGateCfg.nGateOfEvent = 0;
	ImperialUserCount = 0;
	Imperial.CanUseTwisting = 0;

	ImperialMain.Stage = 1;
	ImperialMain.Status = 0;

	Imperial.StartStandByTimer = 60; //236
	Imperial.StandByTimer = 144; //236
	Imperial.Stage1Timer = 144; //2348
	Imperial.Stage2Timer = 144; //2348
	Imperial.Stage3Timer = 144; //2348
	Imperial.Stage4Timer = 144; //2348
	Imperial.Stage5Timer = 144; //2348
	Imperial.StandByRun = 0;
	Imperial.ImperialIsRun = 0;
	Imperial.ImperialCanGo = 0;
	
	for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
	{
		ImperialMain.UserIsInFort[GET_USER_INDEX(i)] = 0;
	}

	for(int i=0;i<255;i++)
	{
		ImperialMobCfg.MobsID[i] = 0;
		ImperialMobCfg.MobsMap[i] = 0;
		ImperialGateCfg.GatesID[i] = 0;
		ImperialGateCfg.GatesNum[i] = 0;
	}

	_beginthread( ImperialFort_CheckState, 0, NULL  );

	//Log.outInfo("Imperial Fort Event Loaded");
}

void ImperialEvent::EventClearIndex(int Index)
{
	GateDelete();
	MonstersDelete();

	ImperialMain.Stage = 1;
	ImperialMain.Status = 0;

	Imperial.StartStandByTimer = 60; //236
	Imperial.StandByTimer = 144; //236
	Imperial.Stage1Timer = 144; //2348
	Imperial.Stage2Timer = 144; //2348
	Imperial.Stage3Timer = 144; //2348
	Imperial.Stage4Timer = 144; //2348
	Imperial.Stage5Timer = 144; //2348
	Imperial.StandByRun = 0;
	Imperial.ImperialIsRun = 0;
	Imperial.ImperialCanGo = 0;
	Imperial.CanUseTwisting = 0;
		
	ImperialMobCfg.nMonsterOfEvent = 0;
	ImperialGateCfg.nGateOfEvent = 0;
	ImperialUserCount = 0;

	ImperialMain.UserIsInFort[GET_USER_INDEX(Index)] = 0;

	for(int i=0;i<255;i++)
	{
		ImperialMobCfg.MobsID[i] = 0;
		ImperialMobCfg.MobsMap[i] = 0;
		ImperialGateCfg.GatesID[i] = 0;
		ImperialGateCfg.GatesNum[i] = 0;
	}
}

void ImperialEvent::EventClear()
{	
	GateDelete();
	MonstersDelete();

	ImperialMain.Stage = 1;
	ImperialMain.Status = 0;

	Imperial.StartStandByTimer = 60; //236
	Imperial.StandByTimer = 144; //236
	Imperial.Stage1Timer = 144; //2348
	Imperial.Stage2Timer = 144; //2348
	Imperial.Stage3Timer = 144; //2348
	Imperial.Stage4Timer = 144; //2348
	Imperial.Stage5Timer = 144; //2348
	Imperial.StandByRun = 0;
	Imperial.ImperialIsRun = 0;
	Imperial.ImperialCanGo = 0;
	Imperial.CanUseTwisting = 0;
	
	ImperialMobCfg.nMonsterOfEvent = 0;
	ImperialGateCfg.nGateOfEvent = 0;
	ImperialUserCount = 0;

	for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
	{	
		ImperialMain.UserIsInFort[GET_USER_INDEX(i)] = 0;
	}

	for(int i=0;i<255;i++)
	{
		ImperialMobCfg.MobsID[i] = 0;
		ImperialMobCfg.MobsMap[i] = 0;
		ImperialGateCfg.GatesID[i] = 0;
		ImperialGateCfg.GatesNum[i] = 0;
	}
}

//Check Item, Level, and Player Count
bool ImperialEvent::CheckCanEnter(int aIndex)
{	
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
		
	if(gObj->Level >= ImperialConfig.MinimumLevel)
	{
		if(ImperialConfig.CheckInvite == 1)
		{	//Index = 14, ID = 102
			if(gObjGetItemCountInInventory(aIndex,0x1C66,0) < 1)
			{
				Log.outError("[%s][%s] ImperialEvent::CheckCanEnter() - Count(0x1A26) < 1.",gObj->AccountID,gObj->Name);
				
				//Send Message to client
				Messages.outNormal(aIndex,"[Imperial Fort] Lacking ticket to enter!");

				//Send Message box to client
				BYTE Packet[13] = { 0xC1, 0x0D, 0xF7, 0x06, 0x01, 0x07, 0x01, 0x00, 0x31, 0xE0, 0xFD, 0x28, 0x1C } ;
				DataSend(aIndex, &Packet[0], Packet[1]);
				return false;
			}
		}
	
		if(gObj->PartyNumber == -1)
		{
			Log.outError("[%s][%s] ImperialEvent::CheckCanEnter() - Not in Party.",gObj->AccountID,gObj->Name);
			
			//Send Message to client
			Messages.outNormal(aIndex,"[Imperial Fort] Event only for party!");
			return false;
		}
		
		if(Imperial.ImperialIsRun == 0)
		{
			ImperialEnter(aIndex);	
		}
		else
		{
			Messages.outNormal(aIndex,"[Imperial Fort] Someone is fighting right now.");
		}
		
		Log.outInfo("[%s][%s] ImperialEvent::CheckCanEnter() - OK.",gObj->AccountID,gObj->Name);
		return true;
	}
	else
	{
		//Error
		Log.outError("[%s][%s] ImperialEvent::CheckCanEnter() - ERROR.",gObj->AccountID,gObj->Name);
		//Messages.outNormal(aIndex,"Num :%d",gObj->PartyNumber);
		return false;
	}
}

void ImperialEvent::ImperialEnter(int aIndex)
{	
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	
	SYSTEMTIME t;
	GetLocalTime(&t);
	
	/*char DayName[10];
	
	if(t.wDayOfWeek == 1){ sprintf_s(DayName,"Monday"); }
	else if(t.wDayOfWeek == 2){ sprintf_s(DayName,"Tuesday"); }
	else if(t.wDayOfWeek == 3){ sprintf_s(DayName,"Wednesday");	}
	else if(t.wDayOfWeek == 4){ sprintf_s(DayName,"Thursday"); }
	else if(t.wDayOfWeek == 5){ sprintf_s(DayName,"Friday"); }
	else if(t.wDayOfWeek == 6){ sprintf_s(DayName,"Saturday"); }
	else if(t.wDayOfWeek == 0){ sprintf_s(DayName,"Sunday"); }*/
	
	if(t.wDayOfWeek == 1 || t.wDayOfWeek == 4){ Imperial.EventDay = 1; }
	else if(t.wDayOfWeek == 2 || t.wDayOfWeek == 5){ Imperial.EventDay = 2; }
	else if(t.wDayOfWeek == 3 || t.wDayOfWeek == 6){ Imperial.EventDay = 3; }
	else if(t.wDayOfWeek == 0){ Imperial.EventDay = 4; }


	if(gObj->PartyNumber != -1)
	{	
		EventClear();

		if(Imperial.EventDay == 1)
		{
		SetMobs(1,1,"ImperialMobs.dat",0);
		SetGates(1,1,"ImperialGates.dat");
		}
		else if(Imperial.EventDay == 2)
		{
		SetMobs(2,2,"ImperialMobs.dat",0);
		SetGates(2,2,"ImperialGates.dat");
		}
		else if(Imperial.EventDay == 3)
		{
		SetMobs(3,3,"ImperialMobs.dat",0);
		SetGates(3,3,"ImperialGates.dat");
		}
		else if(Imperial.EventDay == 4)
		{
		SetMobs(4,4,"ImperialMobs.dat",0);
		SetGates(4,4,"ImperialGates.dat");
		}

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObjOther = (GOBJSTRUCT*)OBJECT_POINTER(i);
			
			if(gObj->Connected == 3 && gObjOther->PartyNumber == gObj->PartyNumber)
			{	
				if(Imperial.EventDay == 1)
				{
				gObjTeleport(i,69,231,14);
				Imperial.EventMap = 69;
				}
				else if(Imperial.EventDay == 2)
				{
				gObjTeleport(i,70,86,66);
				Imperial.EventMap = 70;
				}
				else if(Imperial.EventDay == 3)
				{
				gObjTeleport(i,71,154,186);
				Imperial.EventMap = 71;
				}
				else if(Imperial.EventDay == 4)
				{
				gObjTeleport(i,72,93,68);
				Imperial.EventMap = 72;
				}
				Messages.outNormal(i,"[Imperial Fort] Teleporting to Event Map.");

				PMSG_FORT_EVENT_TIMER pMsg;
				//0xC1, 0x0D, 0xF7, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28
				pMsg.h.c = 0xC1;
				pMsg.h.size = 0x0D;
				pMsg.h.headcode = 0xF7;
				pMsg.h.subcode = 0x04;
				pMsg.Status = 0x01;
				pMsg.Unk4 = 0x00;
				pMsg.TimerL = LOBYTE(Imperial.StartStandByTimer);
				pMsg.TimerH = HIBYTE(Imperial.StartStandByTimer);
				pMsg.Unk5 = 0x00;
				pMsg.Mob = 0;

				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);

				ImperialMain.UserIsInFort[GET_USER_INDEX(i)] = 1;
				ImperialMain.Status = 0;
				ImperialMain.Stage = 1;
				Imperial.ImperialIsRun = 1;
				ImperialUserCount++;

				if(Imperial.StandByRun == 0)
				{
				Imperial.StandByRun = 1;
				_beginthread( ImperialFort_StartStandBy, 0, NULL  );
				}

				Messages.outNormal(i,"[Imperial Fort] Event will start in 1 minute.");
			}
		}
	}
	else
	{
				Messages.outNormal(aIndex,"[Imperial Fort] Event only for party.");
	}
}

void ImperialFort_CheckState(void * lpParam)
{
	while(true)
	{	
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{		
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);
			
			if(gObj->Connected == 3)
			{	
				gObjCheckPaperCountInInventory(i);

				if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 0)
				{
				gObjTeleport(i,0,125,124);
				//Imperial.EventClear();
				//Messages.outNormal(i,"Map Imperial.EventMap, In Fort 0");

				//Clear Event 2
				Imperial.EventClearIndex(i);
				}
			}
			
			if(gObj->Connected == 3)
			{	
				if(gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
				{
				//Imperial.EventClear();
				//gObjTeleport(i,0,125,124);
				DataSend(i, &Packet[0], Packet[1]);
				//Messages.outNormal(i,"Map != Imperial.EventMap, In Fort 1");

				//Clear Event 2
				Imperial.EventClearIndex(i);
				}
			}		
			
			if(Imperial.ImperialIsRun == 1)
			{
				if(gObj->Connected == 3)
				{
					if(gObj->MapNumber == Imperial.EventMap && gObj->PartyNumber == -1 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{
					DataSend(i, &Packet[0], Packet[1]);
					//Messages.outNormal(i,"Map = Imperial.EventMap, Party -1, In Fort 1");
					Imperial.EventClearIndex(i);
					}
					
					if(gObj->MapNumber == Imperial.EventMap && gObj->PartyNumber == -1 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1)
					{
					Imperial.EventClearIndex(i);
					//Messages.outNormal(i,"Map = Imperial.EventMap, Party -1, In Fort != 1");
					}

					if(UserCountInMap(Imperial.EventMap) == 0)
					{
					Imperial.EventClear();
					//Messages.outNormal(i,"Map = Imperial.EventMap users 0");
					}
				}
			}

			if(Imperial.ImperialIsRun == 0)
			{
				if(gObj->Connected == 3)
				{
					if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{
					//Clear Event 2
					Imperial.EventClearIndex(i);
					DataSend(i, &Packet[0], Packet[1]);
					//Messages.outNormal(i,"Map = Imperial.EventMap, In Fort 1");
					}

					if(gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1)
					{
					Imperial.EventClearIndex(i);
					//DataSend(i, &Packet[0], Packet[1]);
					//Messages.outNormal(i,"Map = Imperial.EventMap, In Fort !=1");
					}
				}
			}
		}
		//Log.outError("Imperial Status %d",ImperialMain.Status);
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_EndEvent(void * lpParam)
{
	while(true)
	{	
		Sleep(5000);
		Imperial.EventClear();
		_endthread();
	}
	_endthread();
}

void ImperialFort_StartStage5(void * lpParam)
{
	while(true)
	{	
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		if(ImperialMobCfg.nMonsterOfEvent <= 0)
		{	
				//End Event Succes
				ImperialMain.Status = 0;

				PMSG_FORT_EVENT_TIMER pMsg;
				pMsg.h.c = 0xC1;
				pMsg.h.size = 0x0D;
				pMsg.h.headcode = 0xF7;
				pMsg.h.subcode = 0x04;
				pMsg.Status = 0x01;
				pMsg.Unk4 = 0x00;
				pMsg.TimerL = 0;
				pMsg.TimerH = 0;
				pMsg.Unk5 = 0x00;
				pMsg.Mob = 0;
				
				for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
				{	
					GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

					if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 5 && (ImperialMain.Status == 3 || ImperialMain.Status == 0))
					{	
						int Experience = 1234567890;
			
						PMSG_FOR_END_MESSAGE pMsg;
						pMsg.h.c = 0xC1;
						pMsg.h.size = 0x0D;
						pMsg.h.headcode = 0xF7;
						pMsg.h.subcode = 0x06;
						pMsg.Type = 0x02;
						pMsg.Experience = Experience;
						DataSend(i, (BYTE*)&pMsg, pMsg.h.size);

						gObj->Experience += Experience;
						GCLevelUpMsgSend(i,0);

						gObjTeleport(i,0,125,124);

						//Clear Event 2
						//Imperial.EventClearIndex(i);

						ImperialMain.UserIsInFort[GET_USER_INDEX(i)] = 0;

						_beginthread( ImperialFort_EndEvent, 0, NULL  );
					}
				}
			_endthread();
		}

		if(Imperial.Stage5Timer <= 0)
		{	
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3)
				{	
					if(ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{	
						DataSend(i, &Packet[0], Packet[1]); //Send Fail Message
						gObjTeleport(i,0,125,124);
							
						//Clear Event 2
						Imperial.EventClearIndex(i);
					}
				}
			}
			_endthread();
		}

		Imperial.Stage5Timer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x02;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.Stage5Timer);
		pMsg.TimerH = HIBYTE(Imperial.Stage5Timer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = ImperialMobCfg.nMonsterOfEvent;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);		
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 5 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3) )
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 5 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 5 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1 && ImperialMain.Stage == 5 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
				{
				gObjTeleport(i,0,125,125);
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StandBy3(void * lpParam)
{
	while(true)
	{	
		if(Imperial.StandByTimer < 1)
		{	
			Imperial.StandByTimer = 0;
			ImperialMain.Status = 3;
			ImperialMain.Stage = 5;

			Imperial.CanUseTwisting = 1;

			MonstersDelete();
			SetMobs(4,4,"ImperialMobs.dat",4);
			SetMobs(4,4,"ImperialMobs.dat",5);

			_beginthread( ImperialFort_StartStage5, 0, NULL  );

			_endthread();
		}

		Imperial.StandByTimer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x01;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.StandByTimer);
		pMsg.TimerH = HIBYTE(Imperial.StandByTimer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = 0;
		
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);
				
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1)
				{
				gObjTeleport(i,0,125,125);
				//Imperial.EventClear();
				//_endthread();
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StartStage4(void * lpParam)
{
	while(true)
	{	
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		if(ImperialMobCfg.nMonsterOfEvent <= 0)
		{	
			if(Imperial.EventDay != 4)
			{
				//End Event Succes
				ImperialMain.Status = 0;

				PMSG_FORT_EVENT_TIMER pMsg;
				pMsg.h.c = 0xC1;
				pMsg.h.size = 0x0D;
				pMsg.h.headcode = 0xF7;
				pMsg.h.subcode = 0x04;
				pMsg.Status = 0x01;
				pMsg.Unk4 = 0x00;
				pMsg.TimerL = 0;
				pMsg.TimerH = 0;
				pMsg.Unk5 = 0x00;
				pMsg.Mob = 0;
				
				for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
				{	
					GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

					if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 4 && (ImperialMain.Status == 3 || ImperialMain.Status == 0))
					{	
						int Experience = 1234567890;
			
						PMSG_FOR_END_MESSAGE pMsg;
						pMsg.h.c = 0xC1;
						pMsg.h.size = 0x0D;
						pMsg.h.headcode = 0xF7;
						pMsg.h.subcode = 0x06;
						pMsg.Type = 0x02;
						pMsg.Experience = Experience;
						DataSend(i, (BYTE*)&pMsg, pMsg.h.size);

						gObj->Experience += Experience;
						GCLevelUpMsgSend(i,0);

						gObjTeleport(i,0,125,124);

						//Clear Event 2
						//Imperial.EventClearIndex(i);

						ImperialMain.UserIsInFort[GET_USER_INDEX(i)] = 0;

						_beginthread( ImperialFort_EndEvent, 0, NULL  );

					}
				}

			}
			else
			{	
				Imperial.CanUseTwisting = 1;
				Imperial.StandByTimer = 144;
				_beginthread( ImperialFort_StandBy3, 0, NULL  );
			}

			_endthread();
		}

		if(Imperial.Stage4Timer <= 0)
		{	
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3)
				{	
					if(ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{	
						DataSend(i, &Packet[0], Packet[1]); //Send Fail Message
						gObjTeleport(i,0,125,124);
							
						//Clear Event 2
						Imperial.EventClearIndex(i);
					}
				}
			}
			_endthread();
		}

		Imperial.Stage4Timer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x02;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.Stage4Timer);
		pMsg.TimerH = HIBYTE(Imperial.Stage4Timer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = ImperialMobCfg.nMonsterOfEvent;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);		
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 4 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3) )
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 4 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 4 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1 && ImperialMain.Stage == 4 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
				{
				gObjTeleport(i,0,125,125);
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StartStage3(void * lpParam)
{
	while(true)
	{	
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		if(ImperialMobCfg.nMonsterOfEvent <= 0)
		{	
			//Prepare to Stage 4 (Kill Boss)
			ImperialMain.Status = 3;
			ImperialMain.Stage = 4;

			PMSG_FORT_EVENT_TIMER pMsg;
			pMsg.h.c = 0xC1;
			pMsg.h.size = 0x0D;
			pMsg.h.headcode = 0xF7;
			pMsg.h.subcode = 0x04;
			pMsg.Status = 0x01;
			pMsg.Unk4 = 0x00;
			pMsg.TimerL = 0;
			pMsg.TimerH = 0;
			pMsg.Unk5 = 0x00;
			pMsg.Mob = 0;
			
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 3 && (ImperialMain.Status == 3 || ImperialMain.Status == 0))
				{	
					DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
				}
			}

			MonstersDelete();
			
			if(Imperial.EventDay == 1)
			{
			SetMobs(1,1,"ImperialMobs.dat",3);
			}
			else if(Imperial.EventDay == 2)
			{
			SetMobs(2,2,"ImperialMobs.dat",3);
			}
			else if(Imperial.EventDay == 3)
			{
			SetMobs(3,3,"ImperialMobs.dat",3);
			}
			else if(Imperial.EventDay == 4)
			{
			SetMobs(4,4,"ImperialMobs.dat",3);
			}

			_beginthread( ImperialFort_StartStage4, 0, NULL  );

			_endthread();
		}

		if(Imperial.Stage3Timer <= 0)
		{	
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3)
				{	
					if(ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{	
						DataSend(i, &Packet[0], Packet[1]); //Send Fail Message
						gObjTeleport(i,0,125,124);
							
						//Clear Event 2
						Imperial.EventClearIndex(i);
					}
				}
			}
			_endthread();
		}

		Imperial.Stage3Timer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x02;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.Stage3Timer);
		pMsg.TimerH = HIBYTE(Imperial.Stage3Timer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = ImperialMobCfg.nMonsterOfEvent;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);		
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 3 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3) )
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 3 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 3 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1 && ImperialMain.Stage == 3 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
				{
				gObjTeleport(i,0,125,125);
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StandBy2(void * lpParam)
{
	while(true)
	{	
		if(Imperial.StandByTimer < 1)
		{	
			Imperial.StandByTimer = 0;
			ImperialMain.Status = 3;
			ImperialMain.Stage = 3;

			Imperial.CanUseTwisting = 1;

			MonstersDelete();
			if(Imperial.EventDay == 1)
			{
			SetMobs(1,1,"ImperialMobs.dat",2);
			}
			else if(Imperial.EventDay == 2)
			{
			SetMobs(2,2,"ImperialMobs.dat",2);
			}
			else if(Imperial.EventDay == 3)
			{
			SetMobs(3,3,"ImperialMobs.dat",2);
			}
			else if(Imperial.EventDay == 4)
			{
			SetMobs(4,4,"ImperialMobs.dat",2);
			}

			_beginthread( ImperialFort_StartStage3, 0, NULL  );

			_endthread();
		}

		Imperial.StandByTimer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x01;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.StandByTimer);
		pMsg.TimerH = HIBYTE(Imperial.StandByTimer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = 0;
		
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);
				
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1)
				{
				gObjTeleport(i,0,125,125);
				//Imperial.EventClear();
				//_endthread();
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StartStage2(void * lpParam)
{
	while(true)
	{	
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		if(ImperialMobCfg.nMonsterOfEvent <= 0)
		{	
			//Prepare to Stage 3 (kill gates)(move to position)
			ImperialMain.Status = 3;
			ImperialMain.Stage = 2;

			Imperial.CanUseTwisting = 1;

			PMSG_FORT_EVENT_TIMER pMsg;
			pMsg.h.c = 0xC1;
			pMsg.h.size = 0x0D;
			pMsg.h.headcode = 0xF7;
			pMsg.h.subcode = 0x04;
			pMsg.Status = 0x01;
			pMsg.Unk4 = 0x00;
			pMsg.TimerL = 0;
			pMsg.TimerH = 0;
			pMsg.Unk5 = 0x00;
			pMsg.Mob = 0;
			
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 2 && (ImperialMain.Status == 3 || ImperialMain.Status == 0))
				{	
					DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
				}
			}
			Imperial.StandByTimer = 144;
			_beginthread( ImperialFort_StandBy2, 0, NULL  );

			_endthread();
		}

		if(Imperial.Stage2Timer <= 0)
		{	
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3)
				{	
					if(ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{	
						DataSend(i, &Packet[0], Packet[1]); //Send Fail Message
						gObjTeleport(i,0,125,124);
							
						//Clear Event 2
						Imperial.EventClearIndex(i);
					}
				}
			}
			_endthread();
		}

		Imperial.Stage2Timer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x02;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.Stage2Timer);
		pMsg.TimerH = HIBYTE(Imperial.Stage2Timer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = ImperialMobCfg.nMonsterOfEvent;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);		
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 2 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3) )
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 2 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 2 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1 && ImperialMain.Stage == 2 && ( ImperialMain.Status == 1 || ImperialMain.Status == 3))
				{
				gObjTeleport(i,0,125,125);
				//Imperial.EventClear();

				//_endthread();
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StandBy(void * lpParam)
{
	while(true)
	{	
		if(Imperial.StandByTimer < 1)
		{	
			Imperial.StandByTimer = 0;
			ImperialMain.Status = 3;
			ImperialMain.Stage = 2;

			Imperial.CanUseTwisting = 1;

			MonstersDelete();
			if(Imperial.EventDay == 1)
			{
			SetMobs(1,1,"ImperialMobs.dat",1);
			}
			else if(Imperial.EventDay == 2)
			{
			SetMobs(2,2,"ImperialMobs.dat",1);
			}
			else if(Imperial.EventDay == 3)
			{
			SetMobs(3,3,"ImperialMobs.dat",1);
			}
			else if(Imperial.EventDay == 4)
			{
			SetMobs(4,4,"ImperialMobs.dat",1);
			}

			_beginthread( ImperialFort_StartStage2, 0, NULL  );

			_endthread();
		}

		Imperial.StandByTimer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x01;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.StandByTimer);
		pMsg.TimerH = HIBYTE(Imperial.StandByTimer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = 0;
		
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);
				
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1)
				{
				gObjTeleport(i,0,125,125);
				//Imperial.EventClear();
				//_endthread();
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StartStage1(void * lpParam)
{
	while(true)
	{	
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		if(ImperialMobCfg.nMonsterOfEvent <= 0)
		{	
			//Prepare to Stage 2 (kill gates)(move to position)
			ImperialMain.Status = 3;
			ImperialMain.Stage = 1;

			Imperial.CanUseTwisting = 1;

			PMSG_FORT_EVENT_TIMER pMsg;
			pMsg.h.c = 0xC1;
			pMsg.h.size = 0x0D;
			pMsg.h.headcode = 0xF7;
			pMsg.h.subcode = 0x04;
			pMsg.Status = 0x01;
			pMsg.Unk4 = 0x00;
			pMsg.TimerL = 0;
			pMsg.TimerH = 0;
			pMsg.Unk5 = 0x00;
			pMsg.Mob = 0;
			
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 1 && (ImperialMain.Status == 3 || ImperialMain.Status == 0))
				{	
					DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
				}
			}
			_beginthread( ImperialFort_StandBy, 0, NULL  );

			_endthread();
		}

		if(Imperial.Stage1Timer <= 0)
		{	
			for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
			{	
				GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);

				if(gObj->Connected == 3)
				{	
					if(ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
					{	
						DataSend(i, &Packet[0], Packet[1]); //Send Fail Message
						gObjTeleport(i,0,125,124);
							
						//Clear Event 2
						Imperial.EventClearIndex(i);
					}
				}
			}
			_endthread();
		}

		Imperial.Stage1Timer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x02;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.Stage1Timer);
		pMsg.TimerH = HIBYTE(Imperial.Stage1Timer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = ImperialMobCfg.nMonsterOfEvent;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);		
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 1 && ImperialMain.Status == 1)
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 1 && ImperialMain.Status == 1)
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1 && ImperialMain.Stage == 1 && ImperialMain.Status == 1)
			{	
				DataSend(i, &Packet[0], Packet[1]);

				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1 && ImperialMain.Stage == 1 && ImperialMain.Status == 1)
				{
				gObjTeleport(i,0,125,125);
				}
			}
		}
		Sleep(1000);
	}
	_endthread();
}

void ImperialFort_StartStandBy(void * lpParam)
{
	while(true)
	{	
		Sleep(1000);
		if(Imperial.StandByRun == 0)
		{	
			_endthread();
		}

		if(Imperial.StartStandByTimer < 1)
		{	
			Imperial.StartStandByTimer = 0;
			ImperialMain.Status = 1;
			_beginthread( ImperialFort_StartStage1, 0, NULL  );

			_endthread();
		}

		Imperial.StartStandByTimer -= 4;

		PMSG_FORT_EVENT_TIMER pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0D;
		pMsg.h.headcode = 0xF7;
		pMsg.h.subcode = 0x04;
		pMsg.Status = 0x01;
		pMsg.Unk4 = 0x00;
		pMsg.TimerL = LOBYTE(Imperial.StartStandByTimer);
		pMsg.TimerH = HIBYTE(Imperial.StartStandByTimer);
		pMsg.Unk5 = 0x00;
		pMsg.Mob = 0;
		
		BYTE Packet[13] = {0xC1, 0x0D, 0xF7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(i);
				
			if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, (BYTE*)&pMsg, pMsg.h.size);
			}
			else if(gObj->Connected == 3 && gObj->MapNumber != Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClearIndex(i);

				_endthread();
			}
			else if(UserCountInMap(Imperial.EventMap) == 0 && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] == 1)
			{	
				DataSend(i, &Packet[0], Packet[1]);
				Imperial.EventClear();
				_endthread();
			}
			else
			{	
				if(gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap && ImperialMain.UserIsInFort[GET_USER_INDEX(i)] != 1)
				{
				gObjTeleport(i,0,125,125);
				}
			}
		}
	}
	_endthread();
}

void ImperialEvent::MonsterManager(int aIndex, int mIndex)
{
	GOBJSTRUCT *mObj = (GOBJSTRUCT*) OBJECT_POINTER (mIndex);
	GOBJSTRUCT *pObj = (GOBJSTRUCT*) OBJECT_POINTER (aIndex);

	for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
	{	
		GOBJSTRUCT *mObj = (GOBJSTRUCT*) OBJECT_POINTER (i);
		if((mIndex == i && mObj->MapNumber == Imperial.EventMap) && ( Imperial.ImperialIsRun == 1 )) 
		{ 
			Imperial.EventClearIndex(i); 
		}
	}

	if((mObj->Class == 525 && mObj->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
	{
		BYTE Packet2[6] = {0xC1, 0x06, 0xBF, 0x09, 0x01, 0x00 };
		Packet2[5] = 0x02;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*) OBJECT_POINTER (i);

			if((gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
			{	
					for(int n=0;n<255;n++)
					{	
						if(ImperialGateCfg.GatesID[n] != 0)
						{
							if(ImperialGateCfg.GatesNum[n] == 3 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 2;
								ImperialMain.Status = 0; //Can't Kill All
								Imperial.CanUseTwisting = 0;
								//Messages.outNormal(i,"Killed 3 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 4 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 3;
								ImperialMain.Status = 1; //Can't Kill Gates
								Imperial.CanUseTwisting = 0;
								//Set Imperial Status
								//Messages.outNormal(i,"Killed 4 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 6 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{	
								Imperial.ImperialCanGo = 5;
								ImperialMain.Status = 0; //Can't Kill All
								Imperial.CanUseTwisting = 0;
								//Messages.outNormal(i,"Killed 6 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 7 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 6;
								ImperialMain.Status = 1; //Can't Kill All
								//Messages.outNormal(i,"Killed 7 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 8 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 7;
								ImperialMain.Status = 1; //Can't Kill All
								//Messages.outNormal(i,"Killed 8 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 1)
							{	
								DataSend(i, &Packet2[0], Packet2[1]);
								//Messages.outNormal(i,"Killed 1 gates");
							}

							//Messages.outNormal(i,"Gate[%d][%d][%d]",ImperialGateCfg.GatesID[n],ImperialGateCfg.GatesNum[n],Imperial.ImperialCanGo);
						}
					}
			}
		}
	}

	if((mObj->Class == 524 && mObj->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
	{
		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*) OBJECT_POINTER (i);

			if((gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
			{	
					for(int n=0;n<255;n++)
					{	
						if(ImperialGateCfg.GatesNum[n] == 2 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
						{
						Imperial.ImperialCanGo = 1;
						//Messages.outNormal(i,"Killed 2 gates");
						}
						if(ImperialGateCfg.GatesNum[n] == 5 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
						{
						Imperial.ImperialCanGo = 4;
						ImperialMain.Status = 3; //Can Kill All
						//Messages.outNormal(i,"Killed 5 gates");
						}
					}
			}
		}
	}

	if((mObj->Class == 528 && mObj->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
	{
		BYTE Packet2[6] = {0xC1, 0x06, 0xBF, 0x09, 0x01, 0x00 };
		Packet2[5] = 0x02;

		for(int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
		{	
			GOBJSTRUCT *gObj = (GOBJSTRUCT*) OBJECT_POINTER (i);

			if((gObj->Connected == 3 && gObj->MapNumber == Imperial.EventMap) && (Imperial.ImperialIsRun == 1))
			{	
					for(int n=0;n<255;n++)
					{	
						if(ImperialGateCfg.GatesID[n] != 0)
						{	
							if(ImperialGateCfg.GatesNum[n] == 2 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 1;
							//	Messages.outNormal(i,"Killed 2 gates");
							}
						
							if(ImperialGateCfg.GatesNum[n] == 3 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 2;
								ImperialMain.Status = 0; //Can't Kill All
								Imperial.CanUseTwisting = 0;
							//	Messages.outNormal(i,"Killed 3 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 4 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 3;
								ImperialMain.Status = 1; //Can't Kill Gates
								Imperial.CanUseTwisting = 0;
								//Set Imperial Status
							//	Messages.outNormal(i,"Killed 4 gates");
							}
							
							if(ImperialGateCfg.GatesNum[n] == 5 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 4;
								ImperialMain.Status = 3; //Can Kill All
							//	Messages.outNormal(i,"Killed 5 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 6 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{	
								Imperial.ImperialCanGo = 5;
								ImperialMain.Status = 0; //Can't Kill All
								Imperial.CanUseTwisting = 0;
							//	Messages.outNormal(i,"Killed 6 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 7 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 6;
								ImperialMain.Status = 1; //Can't Kill All
								Imperial.CanUseTwisting = 0;
							//	Messages.outNormal(i,"Killed 7 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 8 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 7;
							//	Messages.outNormal(i,"Killed 8 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 9 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 8;
							//	Messages.outNormal(i,"Killed 9 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 9 && ImperialGateCfg.GatesID[n] == mObj->m_Index)
							{
								Imperial.ImperialCanGo = 9;
								ImperialMain.Status = 0; //Can't Kill All
							//	Messages.outNormal(i,"Killed 9 gates");
							}

							if(ImperialGateCfg.GatesNum[n] == 1)
							{	
								DataSend(i, &Packet2[0], Packet2[1]);
							//	Messages.outNormal(i,"Killed 1 gates");
							}

						//	Messages.outNormal(i,"Gate[%d][%d][%d]",ImperialGateCfg.GatesID[n],ImperialGateCfg.GatesNum[n],Imperial.ImperialCanGo);
						}
					}
			}
		}
	}
}

void GateDelete()
{	
	for(int i=0;i<255;i++)
	{	
		if(ImperialGateCfg.GatesID[i] !=0)
		{
			gObjDel(ImperialGateCfg.GatesID[i]);
			ImperialGateCfg.GatesNum[i] = 0;
			ImperialGateCfg.GatesID[i] = 0;
		}
	}
}

//Add Gates For Event
void AddGates(BYTE Map, int GateNumber, BYTE PosX, BYTE PosY, int Dir, int Num)
{	
	for(int i=0;i<255;i++)
	{
		if(ImperialGateCfg.GatesNum[i] == Num)
		{
			Log.outError("[Imperial Fort] Gate with that number already exists.");
			return;
		}
	}
	int iGateIndex = gObjAddMonsters(Map);

	if(iGateIndex >= 0)
	{	
		GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(iGateIndex);

		gObjSetMonsters(iGateIndex, GateNumber);
		gObj->X = PosX; gObj->TX = PosX; gObj->MTX = PosX; gObj->m_OldX = PosX; gObj->StartX = PosX;
		gObj->Y = PosY; gObj->TY = PosY; gObj->MTY = PosY; gObj->m_OldY = PosY;	gObj->StartY = PosY;
		gObj->MapNumber = Map;
		
		//SetMonster
		gObj->Live = 1;
		gObj->m_PosNum = 0xFFFF;
		gObj->m_MoveRange = 0;
		gObj->m_Attribute = 0x3C;
		gObj->MaxRegenTime = 0x3E8;
		gObj->Level = 2;
		gObj->Type = 2;
		gObj->Dir = Dir;
		gObj->RegenTime = 0;
		gObj->DieRegen = 0;

		ImperialGateCfg.GatesID[ImperialGateCfg.nGateOfEvent] = iGateIndex;
		ImperialGateCfg.GatesNum[ImperialGateCfg.nGateOfEvent] = Num;
		ImperialGateCfg.nGateOfEvent++;

		Log.outError("[Imperial Fort] Gate Created [%d][%d][%d].",iGateIndex,ImperialGateCfg.nGateOfEvent,Num);
	}
	else
	{
		Log.outError("[Imperial Fort] Add Gates Error");
	}
}

//Set Monster For Event
UINT SetGates(DWORD dwArgv, int state,char *FileName)
{
	FILE *fp;
	char sLineTxt[255] = {0};
	char sDataOfMonster[255] = {0};
	BOOL bRead = FALSE;
	
	srand((unsigned)time(NULL));

	char path[50]; 
	wsprintf(path, "..//OptionsData//Events//%s", FileName);
	fopen_s(&fp,path,"r");

	if((fp == NULL))
	{
		if (strcmp (FileName, "ImperialGates.dat")==0)
		{	
			MessageBox(NULL, "Gates Loading Failed", "Error", 0);
		}
		return 0;
	}

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


			if(state == leestatus)
			{
				if(bRead==TRUE && strlen(sLineTxt)>3)
				{
					if(0<5800)
					{
						int MobID, MobMap,MobX, MobY,Dir,Num;
						sscanf_s(sLineTxt, "%d %d %d %d %d %d", &MobID, &MobMap, &MobX, &MobY, &Dir, &Num);

						if (strcmp(FileName,"ImperialGates.dat")==0)
						{	
							AddGates(MobMap, MobID, MobX, MobY,Dir, Num);
						}
					}
				}
			}
	}

	rewind(fp);
	
	return 1;
}

//Add Monsters For Event
void AddMonsters(BYTE Map, int MonsterNumber, BYTE PosX, BYTE PosY, int State)
{	
	for(int i=0;i<255;i++)
	{
		if(ImperialMobCfg.MobState[i] == 3)
		{
			Log.outError("[Imperial Fort] Monster with that state already exists.");
			return;
		}
	}

	int iMonsterIndex = gObjAddMonsters(Map);
	
	if(iMonsterIndex >= 0)
	{	
		GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(iMonsterIndex);

		gObjSetMonsters(iMonsterIndex, MonsterNumber);
		gObj->X = PosX; gObj->TX = PosX; gObj->MTX = PosX; gObj->m_OldX = PosX; gObj->StartX = PosX;
		gObj->Y = PosY; gObj->TY = PosY; gObj->MTY = PosY; gObj->m_OldY = PosY;	gObj->StartY = PosY;
		gObj->MapNumber = Map;
		//SetMonster
		gObj->Live = 1;
		gObj->m_PosNum = 0xFFFF;
		gObj->m_MoveRange = 5;
		gObj->m_Attribute = 0x3C;
		gObj->MaxRegenTime = 0x3E8;
		gObj->Level = 2;
		gObj->Type = 2;
		gObj->Dir = 1;
		gObj->RegenTime = 0;
		gObj->DieRegen = 0;
	
		ImperialMobCfg.MobsID[ImperialMobCfg.nMonsterOfEvent] = iMonsterIndex;
		ImperialMobCfg.MobState[ImperialMobCfg.nMonsterOfEvent] = State;

		ImperialMobCfg.nMonsterOfEvent++;

		Log.outError("[Imperial Fort] Monster Created [%d][%d].",iMonsterIndex,ImperialMobCfg.nMonsterOfEvent);
	}
	else
	{
		Log.outError("[Imperial Fort] Add Monster Error");
	}
}

//Set Monster For Event
UINT SetMobs(DWORD dwArgv, int state,char *FileName,int State)
{
	FILE *fp;
	char sLineTxt[255] = {0};
	char sDataOfMonster[255] = {0};
	BOOL bRead = FALSE;
	
	srand((unsigned)time(NULL));

	char path[50]; 
	wsprintf(path, "..//OptionsData//Events//%s", FileName);
	fopen_s(&fp,path,"r");

	if((fp == NULL))
	{
		if (strcmp (FileName, "ImperialMobs.dat")==0)
		{	
			MessageBox(NULL, "Monsters Loading Failed", "Error", 0);
		}
		return 0;
	}

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


			if(state == leestatus)
			{
				if(bRead==TRUE && strlen(sLineTxt)>3)
				{
					if(0<5800)
					{
						int MobNr, MobMap,MobX, MobY,MobState,MobBoss;
						sscanf(sLineTxt, "%d %d %d %d %d %d", &MobNr, &MobMap,&MobX,&MobY,&MobState,&MobBoss);

						if (strcmp(FileName,"ImperialMobs.dat")==0)
						{	
							if(State == MobState)
							{
							AddMonsters(MobMap, MobNr, MobX, MobY,MobState);
							ImperialMobCfg.MobsMap[ImperialMobCfg.nMonsterOfEvent] = MobMap;
							ImperialMobCfg.MobBoss[ImperialMobCfg.nMonsterOfEvent] = MobBoss;
							}
						}
					}
				}
			}
	}

	rewind(fp);
	
	return 1;
}

void MonstersDelete()
{
	for(int i=0;i<255;i++)
	{	
		if(ImperialMobCfg.MobsID[i] != 0){
			gObjDel(ImperialMobCfg.MobsID[i]);
			ImperialMobCfg.MobsID[i] = 0;
			ImperialMobCfg.MobsMap[i] = 0;
			ImperialMobCfg.MobBoss[i] = 0;
			ImperialMobCfg.MobState[i] = 0;
			ImperialMobCfg.nMonsterOfEvent = 0;
		}
	}
}