#include "Stdafx.h"
#include "ChaosMachine.h"
#include "GameServer.h"
#include "Utils.h"

CHAOSMACHINESTRUCT ChaosCfg;



void __declspec(naked) ChaosboxItemsRegardingEx() 
{
	_asm 
	{
		// Original
		cmp ecx, 0x180f;
		je ItemAllowed;

		// Sekeuromikon piece 1
		cmp ecx, 0x1C67;
		je ItemAllowed;

		// Sekeuromikon piece 2
		cmp ecx, 0x1C68;
		je ItemAllowed;

		// Sekeuromikon piece 3
		cmp ecx, 0x1C69;
		je ItemAllowed;

		// Sekeuromikon piece 4
		cmp ecx, 0x1C6A;
		je ItemAllowed;

		// Sekeuromikon piece 5
		cmp ecx, 0x1C6B;
		je ItemAllowed;

		// Sekeuromikon piece 6
		cmp ecx, 0x1C6C;
		je ItemAllowed;

		// Sealed Golden Box
		cmp ecx, 0x1C79;
		je ItemAllowed;

		// Sealed Silver Box
		cmp ecx, 0x1C7A;
		je ItemAllowed;

		// Silver Key
		cmp ecx, 0x1C70;
		je ItemAllowed;

		// Golden Key
		cmp ecx, 0x1C71;
		je ItemAllowed;

		mov edi, CHAOS_ADR_RETURN;
		jmp edi;

		ItemAllowed:
			mov edi, CHAOS_ADR_ITEM_ALLOW;
			jmp edi;
	}
}

void ChaosMachineLoadConfig()
{	
	char FileName[] = "..//OptionsData//Season5_ChaosMachine.ini";
	ChaosCfg.DimensionBookSucces = GetPrivateProfileInt("ChaosMachine", "DimensionBookSuccess", 100, FileName);
	ChaosCfg.DimensionBookPrice = GetPrivateProfileInt("ChaosMachine", "DimensionBookPrice", 1000000, FileName);
	ChaosCfg.Upgrade14Success = GetPrivateProfileInt("ChaosMachine", "Upgrade14Success", 30, FileName);
	ChaosCfg.Upgrade14Price = GetPrivateProfileInt("ChaosMachine", "Upgrade14Price", 10000000, FileName);
	ChaosCfg.Upgrade15Success = GetPrivateProfileInt("ChaosMachine", "Upgrade15Success", 30, FileName);
	ChaosCfg.Upgrade15Price = GetPrivateProfileInt("ChaosMachine", "Upgrade15Price", 12000000, FileName);
	ChaosCfg.SilverBoxSuccessRate = GetPrivateProfileInt("ChaosMachine", "SilverBoxSuccesRate", 100 , FileName);
	ChaosCfg.GoldenBoxSuccessRate = GetPrivateProfileInt("ChaosMachine", "GoldenBoxSuccesRate", 100 , FileName);

}

void ChaosboxCombinationEx(int aIndex, unsigned char mixid) 
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
	switch(mixid)
	{
	/* Invitation to Imperial Event Sunday */
	case CHAOS_TYPE_IMPERIAL_BOOK:
		/* substracts needed to mix are incompatible */
		if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_IMPERIAL_BOOK))
		{
			ChaosboxFailure(aIndex, CHAOS_TYPE_IMPERIAL_BOOK);
			//LogFile.outFile("[%s][%s] CBMix(%d) substracts authorization failed.", gObj->AccountID, gObj->Name, CHAOS_TYPE_IMPERIAL_BOOK);
			break;
		}

		else
		{
			/* success */
			if(Role(100) <= ChaosCfg.DimensionBookSucces)
			{
				gObjItemStruct CBItem;
				CBItem.m_Type		= 0x1C6D;
				CBItem.m_Durability = 255.0;
				ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_IMPERIAL_BOOK);
				gObj->Money = gObj->Money - ChaosCfg.DimensionBookPrice;
				GCMoneySend(aIndex, gObj->Money);
			}
			else
				ChaosboxFailure(aIndex, CHAOS_TYPE_IMPERIAL_BOOK);
		}
		break;
	/* Item Upgrade +14 */
	case CHAOS_TYPE_UPGRADE_14:
		/* substracts needed to mix are incompatible */
		if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_UPGRADE_14))
		{
			ChaosboxFailure(aIndex,CHAOS_TYPE_UPGRADE_14);
			//LogFile.outFile("[%s][%s] CBMix(%d) substracts authorization failed.", gObj->AccountID, gObj->Name, CHAOS_TYPE_UPGRADE_14);
			break;
		}
		else
		{
			int pChaosNum = 0;
			for(int i=0;i<31;i++)
			{
				if(gObj->pChaosBox[i].m_Type != -1 && gObj->pChaosBox[i].m_Type != 0x1C0D && gObj->pChaosBox[i].m_Type != 0x1C0E && gObj->pChaosBox[i].m_Type != 0x180F)
				{
				//LogFile.outFile("Founded Item[%d][%d]",i,gObj->pChaosBox[i].m_Type);
				pChaosNum = i;
				}
			}
			/* success */
			//Check if is Luck
			if(gObj->pChaosBox[pChaosNum].m_Option2 != 0)
					ChaosCfg.Upgrade14Success += 25;

			if(gObj->pChaosBox[pChaosNum].m_NewOption != 0)
					ChaosCfg.Upgrade14Success += 10;

			if(Role(100) <= ChaosCfg.Upgrade14Success)
			{	
				
				gObjItemStruct CBItem;

				CBItem = gObj->pChaosBox[pChaosNum];
				CBItem.m_Level		= 14;
				//Durability + Level*2+11 = Durability
				float NewDurability = (CBItem.m_Durability-32) +((CBItem.m_Level*2)+11);
				CBItem.m_Durability = NewDurability;
				
				ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_UPGRADE_14);
				gObj->Money = gObj->Money - ChaosCfg.Upgrade14Price;
				GCMoneySend(aIndex, gObj->Money);
			}
			else
				ChaosboxFailure(aIndex, CHAOS_TYPE_UPGRADE_14);
		}
		break;
	/* Item Upgrade +15 */
	case CHAOS_TYPE_UPGRADE_15:
		/* substracts needed to mix are incompatible */
		if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_UPGRADE_15))
		{
			ChaosboxFailure(aIndex,CHAOS_TYPE_UPGRADE_15);
			//LogFile.outFile("[%s][%s] CBMix(%d) substracts authorization failed.", gObj->AccountID, gObj->Name, CHAOS_TYPE_UPGRADE_15);
			break;
		}
		else
		{
			int pChaosNum = 0;
			for(int i=0;i<31;i++)
			{
				if(gObj->pChaosBox[i].m_Type != -1 && gObj->pChaosBox[i].m_Type != 0x1C0D && gObj->pChaosBox[i].m_Type != 0x1C0E && gObj->pChaosBox[i].m_Type != 0x180F)
				{
				//LogFile.outFile("Founded Item[%d][%d]",i,gObj->pChaosBox[i].m_Type);
				pChaosNum = i;
				}
			}
			/* success */
			//Check if is Luck and Excellent
			if(gObj->pChaosBox[pChaosNum].m_Option2 != 0)
					ChaosCfg.Upgrade15Success += 25;

			if(gObj->pChaosBox[pChaosNum].m_NewOption != 0)
					ChaosCfg.Upgrade15Success += 10;

			if(Role(100) <= ChaosCfg.Upgrade15Success)
			{	
				
				gObjItemStruct CBItem;

				CBItem = gObj->pChaosBox[pChaosNum];
				CBItem.m_Level		= 15;
				//Durability + Level*2+17 = Durability
				float NewDurability = (CBItem.m_Durability-39) +((CBItem.m_Level*2)+17);
				CBItem.m_Durability = NewDurability;
				
				ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_UPGRADE_15);
				gObj->Money = gObj->Money - ChaosCfg.Upgrade15Price;
				GCMoneySend(aIndex, gObj->Money);
			}
			else
				ChaosboxFailure(aIndex, CHAOS_TYPE_UPGRADE_15);
		}
		break;
		//NEW
		case CHAOS_TYPE_SILVER_BOX:
			{
				if(!ChaosboxCanExecute(aIndex, CHAOS_TYPE_SILVER_BOX))
				{
					ChaosboxFailure(aIndex, CHAOS_TYPE_SILVER_BOX);
					break;
				}
				else
				{
					if(Role(100) <= ChaosCfg.SilverBoxSuccessRate)
					{
						gObjItemStruct CBItem;
						CBItem.m_Type = 0x100C; //TESTING ITEM
						CBItem.m_Durability = 255.0;
						ChaosboxSuccess(&CBItem, aIndex, CHAOS_TYPE_SILVER_BOX);
						gObj->Money = gObj->Money - 1000000;
						GCMoneySend(aIndex, gObj->Money);
					}
					else
						ChaosboxFailure(aIndex,CHAOS_TYPE_SILVER_BOX);
				}
			}break;
		}
}
		


void ChaosboxSuccess(gObjItemStruct *prize, int aIndex, CHAOS_TYPE mixid) 
{	
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	ChaosBoxInit(gObj);

	//ChaosBoxInit(gObj);
	gObj->pChaosBox[0] = *prize;
	GCUserChaosBoxSend(gObj, 0);

	//ItemSerialCreateSend(aIndex, 255, 0, 0, prize->m_Type, prize->m_Level, (int)prize->m_Durability, prize->m_Option1, prize->m_Option2, prize->m_Option3, -1, 0, 0);
	
	//LogFile.outFile("[%s][%s] CBMix success (%d).", gObj->AccountID, gObj->Name, mixid);
}

void ChaosboxFailure(int aIndex, CHAOS_TYPE mixid) 
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	ChaosBoxInit(gObj);
	GCUserChaosBoxSend(gObj, 0);
	PMSG_CHAOSBOX_RESULT Msg = {0xC1, 0x0A, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	DataSend(aIndex, (unsigned char*)&Msg, 10);
	
	//LogFile.outFile("[%s][%s] CBMix failure (%d).", gObj->AccountID, gObj->Name, mixid);
}

bool ChaosboxCanExecute(int aIndex, CHAOS_TYPE mixid) 
{
	GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);

	if(mixid == CHAOS_TYPE_IMPERIAL_BOOK)
	{
		/* have all substracts */
		if(gObjGetItemCountInChaosbox(aIndex, 0x1C67) > 0 && gObjGetItemCountInChaosbox(aIndex, 0x1C68) > 0 && gObjGetItemCountInChaosbox(aIndex, 0x1C69) > 0 && gObjGetItemCountInChaosbox(aIndex, 0x1C6A) > 0 && gObjGetItemCountInChaosbox(aIndex, 0x1C6B) > 0 && gObjGetItemCountInChaosbox(aIndex, 0x1C6C) > 0)
		{
			/* have required sum of zens */
			if(gObj->Money >= ChaosCfg.DimensionBookPrice)
				return true;
		}
		return false;
	}
	
	if(mixid == CHAOS_TYPE_UPGRADE_14)
	{
		/* have all substracts */
		if(gObjGetItemCountInChaosbox(aIndex, 0x1C0E) == 5 && gObjGetItemCountInChaosbox(aIndex, 0x1C0D) == 5 && gObjGetItemCountInChaosbox(aIndex, 0x180F) > 0)
		{
			/* have required sum of zens */
			if(gObj->Money >= ChaosCfg.Upgrade14Price)
				return true;
		}
		return false;
	}

	if(mixid == CHAOS_TYPE_UPGRADE_15)
	{
		/* have all substracts */
		if(gObjGetItemCountInChaosbox(aIndex, 0x1C0E) == 6 && gObjGetItemCountInChaosbox(aIndex, 0x1C0D) == 6 && gObjGetItemCountInChaosbox(aIndex, 0x180F) > 0)
		{
			/* have required sum of zens */
			if(gObj->Money >= ChaosCfg.Upgrade15Price)
				return true;
		}
		return false;
	}

	if (mixid == CHAOS_TYPE_SILVER_BOX)
	{
		if (gObjGetItemCountInChaosbox(aIndex,0x1C70) > 0 && gObjGetItemCountInChaosbox(aIndex,0x1C7A) > 0)
		{
			if(gObj->Money >= 1000000)
				return true;
		}
	}
// ---------------------------------------------
	if (mixid == CHAOS_TYPE_GOLDEN_BOX)
	{
		if (gObjGetItemCountInChaosbox(aIndex,0x1C71) > 0 && gObjGetItemCountInChaosbox(aIndex,0x1C79) > 0)
		{
			if(gObj->Money >= 1000000)
				return true;
		}
	}
	return false;
}
