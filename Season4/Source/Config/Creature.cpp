/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "Gameserver.h"
#include <stdio.h>
//#include "User.h"
//#include "Utils.h"
//#include "Quest.h"
//#include "Log.h"
//#include "Structure.h"
#include "Creature.h"
#include "ItemDropRate.h"
unsigned time_seed()
{
	time_t now = time ( 0 );
	unsigned char *p = (unsigned char *)&now;
	unsigned seed = 0;
	size_t i;
	
	for ( i = 0; i < sizeof now; i++ )
		seed = seed * ( UCHAR_MAX + 2U ) + p[i];
	 
	return seed;
}

 


/*
//When NPC Die (For item drops and other stuff)
bool DieNPCEx(int aIndex,int NPC)
{
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (NPC);
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	//DWORD dwGetTopHitUser = gObjMonterTopHitDamageUser(NPC);
	conLog.ConsoleOutput("OK");
	int aRole = Role(100);
	DWORD dwRand ;
	srand(static_cast<int>(time(NULL)));
	dwRand = (DWORD) rand()%0x4E20 ;//0x2710 = 10000
	
	if(bDropRateConfig==TRUE)
	{	
		for(int i=0;i<nDropRateCount;i++)
		{	
			if((DropRateConfig[i].DropMap == -1) || (DropRateConfig[i].DropMap == gObj->MapNumber))
			{
				UINT  RewardItem= DropRateConfig[i].Type *512 + DropRateConfig[i].Index;		
				if(dwRand <= DropRateConfig[i].Rate) 
				{	
					ItemSerialCreateSend(NPC,gObjNPC->MapNumber,gObjNPC->X,gObjNPC->Y,RewardItem,DropRateConfig[i].Level,DropRateConfig[i].Duration,DropRateConfig[i].Skill,DropRateConfig[i].Luck,DropRateConfig[i].Opt,aIndex,0,0);
					//return 1;
				}	
			}
		}
	}
	
	return true;
}
*/

