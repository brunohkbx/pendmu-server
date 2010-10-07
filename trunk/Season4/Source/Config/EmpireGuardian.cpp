#include <process.h>
#include "stdafx.h"
#include "Gameserver.h"
#include "EmpireGuardian.h"

//void DoubleGoer__InsideTrigger(void * lpParam);
EmpGuardian EGEvent;

void EmpGuardian::NPCTalk_GateKeeper(DWORD PlayerID)
{
	BYTE buff[5] = {0xC3,0x05,0x30,0x24,0x00};
	DataSend (PlayerID,buff , buff[1]);
	//DataSend( PlayerID , (PBYTE)Dialog , Dialog[1] );	
}

void EmpGuardian::Init()
{
	//_beginthread( DoubleGoer__InsideTrigger, 0, NULL  );
}
