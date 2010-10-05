/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/
#include "GameServer.h"
#include "User.h"

//Get gObjId
/*
int gObjGetgObjId(char *CharName)
{
	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == PLAYER_PLAYING)
		{
			if(gObj->Name == CharName)
			{
				return i;
			}
		}
	}
}

void AllServerMsgSend(char *message, ...) 
{
	for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == PLAYER_PLAYING)
			GCServerMsgStringSend(message, i, 0);
	}
}
*/