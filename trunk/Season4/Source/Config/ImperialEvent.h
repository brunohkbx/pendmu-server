#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>

typedef struct IMPERIALCONFIG {
	int MinimumLevel;
	int CheckInvite;
} IMPERIALCONFIGSTRUCT;

//Imperial Event Main
typedef struct IMPERIALMAIN {
	int Stage;
	int Status;
	DWORD UserIsInFort[1000];
} IMPERIALMAINSTRUCT;

//MonsterStruct
typedef struct IMPERIALMONSTERCFG
{
	int MobID;
	int MobsMap[255];	
	int MobX;
	int MobY;
	UINT nMonsterOfEvent;
	int MobsID[255];
	int MobState[255];
	int MobBoss[255];
}IMPERIALMONSTERCFGSTRUCT;

//GateStruct
typedef struct IMPERIALGATECFG
{
	int MobID;
	int MobMap;	
	int MobX;
	int MobY;
	int Dir;
	int GatesID[255];
	int GatesNum[255];
	UINT nGateOfEvent;
}IMPERIALGATECFGSTRUCT;

class ImperialEvent
{
public:
	void Init();
	void ImperialLoadConfig();
	bool CheckCanEnter(int aIndex);
	void ImperialEnter(int aIndex);
	void EventClearIndex(int Index);
	void EventClear();
	UINT ReadMonsterFile(int EventDay,char *filename);
	UINT ReadGateFile(int EventDay,char *filename);
	void MonsterManager(int aIndex, int mIndex);
	
	int StartStandByTimer;
	int Stage1Timer;
	int Stage2Timer;
	int Stage3Timer;
	int Stage4Timer;
	int Stage5Timer;
	int StandByTimer;
	int StandByRun;
	int ImperialIsRun;
	int ImperialCanGo;
	int ImperialUserCount;

	int EventDay;
	int EventMap;

	int CanUseTwisting;
};

extern IMPERIALCONFIGSTRUCT ImperialConfig;
extern IMPERIALMAINSTRUCT ImperialMain;
extern IMPERIALMONSTERCFGSTRUCT ImperialMobCfg;
extern IMPERIALGATECFGSTRUCT ImperialGateCfg;
extern ImperialEvent Imperial;

//								Status( 1 - Can't go, 2 - can go)
//0xC1, 0x06, 0xBF, 0x09, 0x01, 0x01


//Mode : 01 - StandBy, 02 - Kill Mobs, 03 - Empty, 00 - Standby
		//										ID	Mode	FF	  83	27	  68  Time  Time		Mob
		/*
		BYTE Packet[13] = { 0xC1, 0x0D, 0xF7, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28 };
		
		Packet[9] = LOBYTE(Timer);//LOBYTE(Points)
		Packet[10] = HIBYTE(Timer);//HIBYTE(Points)
		DataSend(aIndex, &Packet[0], Packet[1]);*/

//Packets

struct PBMSG_HEAD_I	// Packet - Byte Type
{
public:

	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};

	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};

//0xC1, 0x0D, 0xF7, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28	
//Imperial Fort Timer Init
//Status : 01 - StandBy, 02 - Kill Mobs, 03 - Empty, 00 - Standby
struct PMSG_FORT_EVENT_TIMER // 0x04
{
	PBMSG_HEAD_I h;
	BYTE Status;
	BYTE Unk1;
	BYTE Unk2;
	BYTE Unk3;
	BYTE Unk4;
	BYTE TimerL;
	BYTE TimerH;
	BYTE Unk5;
	BYTE Mob;
};

struct PMSG_FOR_END_MESSAGE
{
	PBMSG_HEAD_I h;
	BYTE Type;
	BYTE Unk1;
	BYTE Unk2;
	BYTE Unk3;
	unsigned long Experience;
	BYTE Unk4;
};
	

UINT SetMobs(DWORD dwArgv, int state,char *FileName,int State);
UINT SetGates(DWORD dwArgv, int state,char *FileName);
void GateDelete();
void MonstersDelete();
