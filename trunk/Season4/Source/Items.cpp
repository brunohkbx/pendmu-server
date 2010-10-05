/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "StdAfx.h"
#include "Items.h"
#include "User.h"
#include "GameServer.h"
#include "Common.h"



DWORD gObjByInventory ( int rinv )
{
	int pinv;
	for ( DWORD i = MIN_PLAYERID ; i < MAX_PLAYERID ; i ++ )
	{
		pinv = *(DWORD*)(i * gObjSize + gObjBaseAddr + gObjInventory);
		if ( rinv==pinv )
		{
			return i;
		}
	}
	return 0xFFFF;
}

//DWORD gObjByWarehouse ( int rinv )
DWORD gObjByWarehouse ( int rinv )
{
	int pinv;

	for ( DWORD i = MIN_PLAYERID ; i < MAX_PLAYERID ; i ++ )
	{
		pinv = *(DWORD*)(i * gObjSize + gObjBaseAddr + gObjWarehouse);
		if ( rinv==pinv )
		{
			return i;
		}
	}
	return 0xFFFF;
} 

bool CheckItemInv(DWORD aIndex,WORD ItemID,WORD Level,int ItemAddress)
{
	if (ItemAddress>75 || ItemAddress<1)
		return false;
	DWORD * inv = (DWORD*) ( gObjBaseAddr  + ( gObjSize * aIndex) + gObjInventory );
	
	WORD * pitemId = (WORD*) ( ( ItemAddress * GS_ITEMSIZE ) + *inv + 6 );
	WORD * pitembyte = (WORD*) ( ( ItemAddress * GS_ITEMSIZE ) + *inv + 8 );
	
	
	if ( *pitemId == ItemID && *pitembyte == Level ) 
	{
		return true;
	}
	
	
	return false;
}
