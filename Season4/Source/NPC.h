/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#ifndef NPC_H
#define NPC_H

#include <windows.h>

struct RewardItem
{
	int Type;
	int Index;
	int Level;
	int Skill;
	int Luck;
	int Option;
	int Excellent;
	int Duration;
	int itemscount;
};


void  GoldenArcher(DWORD aIndex,DWORD ItemAddress);
void GoldenArcherInit(DWORD dwArgv,int state,char *FileName);
void NPCTalkEx(DWORD aIndex, DWORD aDestIndex);

extern RewardItem GaItem[255];
void SantaClaus (DWORD aIndex);
//bool isRena(int aIndex);
void GoldenArcherSaveData(DWORD aIndex);

#endif