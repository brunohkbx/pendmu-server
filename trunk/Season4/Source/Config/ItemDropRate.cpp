/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "StdAfx.h"
#include "GameServer.h"
#include "ItemDropRate.h"
#include <stdio.h>
#include "Creature.h"
#include "Log.h"

int ItemHighestDropRate=0;

UINT ItemDropRate(DWORD dwArgv, int state,char *FileName)
{
	FILE *fp;
	char sLineTxt[1000] = {0};
	BOOL bRead = FALSE;
	int leestatus=-1;
	int i=0;
	nDropRateCount = 0;

	char path[255]; 
	wsprintf(path, "%s", FileName);
	//GetCurrentDirectory(50,path);
	//strcat(path,"\\data\\"); 
	//strcat(path,FileName); 

	if((fp=fopen(path, "r")) == NULL)
	{
		MessageBox(NULL, "ItemDropRate.txt Failed", "--::Syrius DLL::-- ", 0);
		bDropRateConfig = FALSE;
		return 0;
	}else
	{
		bDropRateConfig = TRUE;
		
	}
		
	rewind(fp);
		
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
				if ((sLineTxt[0] == 'e')&&(sLineTxt[1] == 'n')&&(sLineTxt[2] == 'd'))
				{
					leestatus = -1;
				} else {
					UINT n[20] = {0};
					sscanf(sLineTxt, "%d %d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10]);														
					DropRateConfig[i].Type		= n[0];
					DropRateConfig[i].Index		= n[1];
					DropRateConfig[i].Level		= n[2];	
					DropRateConfig[i].Opt		= n[3];	
					DropRateConfig[i].Luck		= n[4];	
					DropRateConfig[i].Skill		= n[5];
					DropRateConfig[i].Duration	= n[6];	
					DropRateConfig[i].Rate		= n[7];	
					DropRateConfig[i].Minlvl	= n[8];	
					DropRateConfig[i].Maxlvl	= n[9];	
					DropRateConfig[i].DropMap	= n[10];
					if (ItemHighestDropRate<n[7])
					{
						ItemHighestDropRate=n[7];
					}
					i++;
				}
			}
		}
	}
	
	rewind(fp);
	fclose(fp);

	nDropRateCount = i;
	//Log portion for bug tracing
	char sBuf[255] = {0};
	wsprintf(sBuf, "[Drop System] Enabled: %d / Total Records: %d / Highest Rate: %d",bDropRateConfig,nDropRateCount,ItemHighestDropRate);
	conLog.ConsoleOutput("%s", sBuf);

	return 1;
}

//Global variable Used to keep track of certain variables so they dont repeat
extern int	itemRandVersion;
int			PreviousItemPosition = 0;

int GetDropConfigurationItem(int OriginalDropRate, int cMapId, int wMonsterLv, int wMonsterId)
{
	//Checking Values
	if (wMonsterId==0) { wMonsterId=1; }
	if (wMonsterLv==0) { wMonsterLv=1; }

	//Loading Initial array with values
	int ItemDropList[MaximumDropBuffer];
	int ItemFoundCounter = 0;

	//Will be subarray for actual drop
	int ItemDropFinal[MaximumDropBuffer];
	int ItemDropCounter = 0;

	//Random used variables
	int HighestDropRate = 0;
	int NewDropRate = 0;
	int TempDropRate = 0;
	int FinalItemPosition = 0;

	//Log Portion
	char sBuf[255] = {0};

	//Getting all items with the value that is less or equals to the drop rate
	if (ItemHighestDropRate>=OriginalDropRate)
	{
		for(int i=0;i<nDropRateCount;i++)
		{
			if (i<MaximumDropBuffer)
			{
				if(((DropRateConfig[i].DropMap == -1) || (DropRateConfig[i].DropMap == cMapId)) && ((wMonsterLv>=DropRateConfig[i].Minlvl) && (wMonsterLv<=DropRateConfig[i].Maxlvl)))
				{
					if(OriginalDropRate <= DropRateConfig[i].Rate) 
					{	
						ItemDropList[ItemFoundCounter]=i;
						ItemFoundCounter += 1;
					}
				}
			}
		}
	} else {
		ItemFoundCounter=0;
	}
	
	if (ItemFoundCounter>0)
	{
		//wsprintf(sBuf, "[Drop System][Rate: %d][Found: %d][Level: %d][ID: %d] Preparing to drop Item...",OriginalDropRate,ItemFoundCounter,wMonsterLv,wMonsterId);
		//LogLine("%s\n", sBuf);

		//Getting Highest Drop rate from new array
		//=====================================================================
		for(int i=0;i<ItemFoundCounter;i++)
		{
			//Getting Drop Rate of the selected item list
			TempDropRate=DropRateConfig[ItemDropList[i]].Rate;

			//Checking if Drop Rate is Higher than previous item
			if (TempDropRate>HighestDropRate)
			{
				HighestDropRate=TempDropRate;
			}
		}

		//Generating New drop % from the range
		//=====================================================================
		if (HighestDropRate>1)
		{
			srand(time_seed()+wMonsterLv+wMonsterId);
			NewDropRate = (rand()/(((double)RAND_MAX + 1)/HighestDropRate));

			if (NewDropRate>OriginalDropRate)
			{
				NewDropRate=NewDropRate/2;
			} 
			else if (NewDropRate==0)
			{
				srand(time_seed()*wMonsterLv*wMonsterLv/wMonsterId);
				NewDropRate = (rand()/(((double)RAND_MAX + 1)/HighestDropRate));
			}
		}

		//Getting new set of items from the Array with higher drop rate
		//=====================================================================
		for(int i=0;i<ItemFoundCounter;i++)
		{
			if (i<MaximumDropBuffer)
			{
				if(NewDropRate <= DropRateConfig[ItemDropList[i]].Rate) 
				{	
					ItemDropFinal[ItemDropCounter]=ItemDropList[i];
					ItemDropCounter += 1;
				}
			}
		}
		
		if (ItemDropCounter>0)
		{
			if (ItemDropCounter>1)
			{
				//Generating a random items from array
				//=====================================================================
				srand(time_seed()*wMonsterId/wMonsterLv);
				FinalItemPosition = rand()/(((double)RAND_MAX + 1)/ItemDropCounter);

				if (FinalItemPosition==PreviousItemPosition)
				{
					srand(time_seed()-wMonsterId+wMonsterLv);
					FinalItemPosition = rand()/((RAND_MAX + 1)/ItemDropCounter);
				}
			} else {
				FinalItemPosition = 0;
			}

			FinalItemPosition = FinalItemPosition+1;
			PreviousItemPosition = FinalItemPosition;

		//	wsprintf(sBuf, "[Drop System][GET ITEM] Start Rate: %d / Found Items: %d / Highest Rate: %d / New Rate: %d / Drop Items: %d / Drop Index: %d[%d]",OriginalDropRate,ItemFoundCounter,HighestDropRate,NewDropRate,ItemDropCounter,ItemDropFinal[FinalItemPosition-1],FinalItemPosition-1);
		//	LogLine("%s\n", sBuf);

			//Returning the item
			//=====================================================================
			return ItemDropFinal[FinalItemPosition-1];
		} else {
			return -1;
		}
	} else {
		//Return -1 if item has not been found
		//=====================================================================
		return -1;
	}
}