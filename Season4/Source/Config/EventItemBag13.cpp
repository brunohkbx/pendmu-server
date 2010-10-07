/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "GameServer.h"
#include "Common.h"
#include "User.h"
#include "Items.h"
#include "Utils.h"
#include "EventItemBag13.h"

int I13thBagCount;
I13thBagData DataFrom13thEIB[255];
//Event Item Bag13 Fixs
void Read13thItemBag()
{
	FILE * fp;
	char sLineTxt[255] = {0};
	int i = 0;
	
	fopen_s(&fp,"..\\Data\\EventItemBag13.txt","r");

	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] != '/' && sLineTxt[1] != '/' && strlen(sLineTxt) > 3)
		{
			int n[5] = {0};
			sscanf_s(sLineTxt, "%d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
			DataFrom13thEIB[i].Type = n[0];
			DataFrom13thEIB[i].Index = n[1];
			DataFrom13thEIB[i].Level = n[2];
			DataFrom13thEIB[i].Skill = n[3];
			DataFrom13thEIB[i].Luck = n[4];
			DataFrom13thEIB[i].AddOpt = n[5];
			I13thBagCount++;
			i++;
		}
	}
	fclose(fp);
}

void __cdecl RingEventItemBoxOpen(GOBJSTRUCT *lpObj)
{
	int level;
	int type;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	
	if (I13thBagCount <= 0)
	{
		return;
	}
	else
	{
		srand(time(NULL));
		int v1 = rand();
		int DropItemNum = v1 % I13thBagCount;
		int x = lpObj->X;
		int y = lpObj->Y;
		int iRND = rand() % 100;
		
		if ( iRND >= 5 )
		{
			if ( iRND >= 20 )
			{
				if ( iRND >= 50 )
				{
					level = 6;
				}
				else
				{
					level = 7;
				}
			}
			else
			{
				level = 8;
			}
		}
		else
		{
			level = 9;
		}
		
		type = DataFrom13thEIB[DropItemNum].Type * 512 + DataFrom13thEIB[DropItemNum].Index;
		Option1 = 1;
		Option2 = rand() % 2;
		
		if ( rand() % 5 >= 1 )
		{
			Option3 = rand() % 3;
		}
		else
		{
			Option3 = 3;
		}
		
		if ( type == 6159 || type == 7181 || type == 7182 )
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}
		
		if ( type == 6656 || type == 6657 || type == 6658 || type == 6664 || type == 6665 || type == 6668 || type == 6669 )
		{
			level = 0;
		}
		
		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,x,y,type,level,0,Option1,Option2,Option3,lpObj->m_Index,0,0);
	}
}
