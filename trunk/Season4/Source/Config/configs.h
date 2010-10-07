/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/


//Includes & Defines
#include <stdio.h>
#include <vector>
#include "StdAfx.h"

#ifdef GameServer90

#define GS_ITEM_TIME1       (0x004BB23A+1)
#define GS_ITEM_TIME2       (0x004BB3EB+1)
//Wizard Drop
#define GS_WW_ITEM_ID       (0x004834D6+1)
#define GS_WW_ITEM_GROUP      (0x004834D8+1)
#define GS_WW_ITEM_LVL      (0x004834F5+1)
#define GS_WW_ITEM_DUR      (0x004834F3+1)
#define GS_WW_ITEM_SKILL      (0x004834F1+1)
#define GS_WW_ITEM_LUCK      (0x004834EF+1)
#define GS_WW_ITEM_OP      (0x004834ED+1)
#define GS_WW_ITEM_EXC      (0x004834E7+1)
#define GS_WW_ITEM_ANC      (0x004834E5+1)

#define GS_BC_DROP_ID		(0x0058810B+1) //
#define GS_BC_DROP_GROUP	(0x0058810D+1) //
#define GS_BC_DROP_LVL      (0x005881B2+1)
#define GS_BC_DROP_DUR      (0x005881B0+1)
#define GS_BC_DROP_SKILL      (0x005881AE+1)
#define GS_BC_DROP_LUCK      (0x005881AC+1)
#define GS_BC_DROP_OP      (0x005881AA+1)
#define GS_BC_DROP_EXC      (0x005881A4+1)
#define GS_BC_DROP_ANC      (0x005881A2+1)

#define GS_IT_DROP_ID       (0x005E6713+1)
#define GS_IT_DROP_GROUP    (0x005E6715+1)
#define GS_IT_DROP_LVL      (0x005E6732+1)
#define GS_IT_DROP_DUR      (0x005E6730+1)
#define GS_IT_DROP_SKILL      (0x005E672E+1)
#define GS_IT_DROP_LUCK      (0x005E672C+1)
#define GS_IT_DROP_OP      (0x005E672A+1)
#define GS_IT_DROP_EXC      (0x005E6724+1)
#define GS_IT_DROP_ANC      (0x005E6722+1)

//#define GS_Raklion_Delay	(0x0061018B+3)

#define GS_CHAOS_PRICE    (0x5521E1+3)
#define GS_SOUL_PRICE     (0x5521C0+3)
#define GS_BLESS_PRICE    (0x55219E+3)
#define GS_CREATION_PRICE (0x552225+3)
#define GS_LIFE_PRICE     (0x552203+3)
#define GS_GUARDIAN_PRICE (0x5522FF+3)
#define GS_FruitsPrice (0x5522A0+3)
#define GS_BlueFeatherPrice (0x5522DE+3)
#define GS_Clock_Price_Lvl1 (0x55272F+3)
#define GS_Clock_Price_Lvl2 (0x55273F+3)
#define GS_Clock_Price_Lvl3 (0x55274F+3)
#define GS_Clock_Price_Lvl4 (0x55275F+3)
#define GS_Clock_Price_Lvl5 (0x55276F+3)
#define GS_Clock_Price_Lvl6 (0x55277F+3)
#define GS_Clock_Price_Lvl7 (0x55278F+3)

#define GS_SOULNOLUCK_RATE (0x537082+3)
#define GS_SOULLUCK_RATE   (0x5370C3+3)
#define GS_SOULSOCKET_RATE (0x5370B7+3)
#define GS_LIFE_RATE       (0x5378D7+3) 

#define GS_MaxLevel1 (0x4E8432+3)
#define GS_MaxLevel2 (0x4E84B2+3)
//#define GS_MaxLevel3 (0x41F962+1)
#define GS_MaxLevel4 (0x50D1D9+1)
#define GS_MaxLevel5 (0x582C76+1)
#define GS_MaxLevel6 (0x5938F6+1)
#define GS_MaxLevel7 (0x5C27F8+1)
#define GS_MaxLevel8 (0x5E6F80+1)
#define GS_MaxLevel9 (0x0050D6CE+2)
#define GS_MaxLevel10 (0x005830A7+1)
#define GS_MaxLevel11 (0x00593D27+1)
#define GS_MaxLevel12 (0x005C2C29+1)
#define GS_MaxLevel13 (0x005E73B8+2)



#define GS_MAX_LEVEL_NO_EXP (0x56A34F+3)


#define GS_UDP            (0x56A21F+1) 
//LV up points
#define GS_DL_UP_POINT1    (0x50D3BB+2)
#define GS_MG_UP_POINT1     (0x50D3E3+2)
#define GS_NORMAL_UP_POINT1 (0x50D3FA+2)

#define GS_DL_UP_POINT2    (0x582DF4+2)
#define GS_MG_UP_POINT2    (0x582DF4+2)
#define GS_NORMAL_UP_POINT2 (0x582E25+2)

#define GS_DL_UP_POINT3    (0x593A74+2)
#define GS_MG_UP_POINT3     (0x593A74+2)
#define GS_NORMAL_UP_POINT3 (0x593AA5+2)

#define GS_DL_UP_POINT4    (0x5C2976+2)
#define GS_MG_UP_POINT4     (0x5C2976+2)
#define GS_NORMAL_UP_POINT4 (0x5C29A7+2)

#define GS_DL_UP_POINT5    (0x5E7102+2)
#define GS_MG_UP_POINT5     (0x5E7102+2)
#define GS_NORMAL_UP_POINT5 (0x5E7132+2)

#define GS_MARLON_UP_POINT1 (0x50D41E+2)
#define GS_MARLON_UP_POINT2 (0x582E6E+2)
#define GS_MARLON_UP_POINT3 (0x593AEE+2)
#define GS_MARLON_UP_POINT4 (0x5C29F0+2)
#define GS_MARLON_UP_POINT5 (0x5E717C+2)

#define GS_CC_MINUSER     (0x594890+3)
#define GS_ILLUSION_MINUSER (0x5DE535+6)
#define GS_SUMMON_ORB1 (0x4DA297+1) //Summon orb 1 
#define GS_SUMMON_ORB2 (0x4DA2C8+1) //Summon orb 2 
#define GS_SUMMON_ORB3 (0x4DA2F9+1) //Summon orb 3 
#define GS_SUMMON_ORB4 (0x4DA32A+1) //Summon orb 4 
#define GS_SUMMON_ORB5 (0x4DA35B+1) //Summon orb 5 
#define GS_SUMMON_ORB6 (0x4DA38C+1) //Summon orb 6 
#define GS_SUMMON_ORB7 (0x4DA3C0+1) //Summon orb 7 
#define GS_TRANSFORM_RING1 (0x4DBCA4+3) //Ring of transform 1 
#define GS_TRANSFORM_RING2 (0x4DBCAD+3) //Ring of transform 2 
#define GS_TRANSFORM_RING3 (0x4DBCB6+3) //Ring of transform 3 
#define GS_TRANSFORM_RING4 (0x4DBCBF+3) //Ring of transform 4 
#define GS_TRANSFORM_RING5 (0x4DBCC8+3) //Ring of transform 5 
#define GS_TRANSFORM_RING6 (0x4DBCD1+3) //Ring of transform 6 
//#define GS_BOXKUNDUN_DROPLUCK (0x4A17D0+3)
#define GS_BOXKUNDUN_DROPSKILL (0x4A17D7+3)
#define GS_BOXKUNDUN_DROPLEVEL (0x4A17DE+3)


#define GS_ChaosMix10_NormalItem (0x5EB63F+6 ) //int
#define GS_ChaosMix10_SpecialItem  (0x5EB65B+6)
#define GS_ChaosMix10_SocketItem  (0x5EB678+6)

#define GS_ChaosMix_11_12_NormalItem  (0x5EB6CF+6)
#define GS_ChaosMix_11_12_SpecialItem  (0x5EB6EC+6)
#define GS_ChaosMix_11_12_SocketItem  (0x5EB709+6)

#define GS_ChaosMix13_NormalItem  (0x5EB761+6)
#define GS_ChaosMix13_SpecialItem  (0x5EB77E+6)
#define GS_ChaosMix13_SocketItem (0x5EB79A+6)

#define GS_ChaosMixAddLuck  (0x5EB7D8+2)
#define GS_DefautlMix		(0x005EB7A9+6)
#define GS_ChaosMixMax1_10_13  (0x5EB7E7+6)
#define GS_ChaosMixMax2_10_13  (0x5EB7F3+6)

//MIX Wing

#define GS_MIX_WING1_1 (0x5E90E8+6)
#define GS_MIX_WING1_2 (0x5E90F4+6)
#define GS_MIX_WING2_1 (0x5ED2EA+6)
#define GS_MIX_WING2_2 (0x5ED2F6+6)
#define GS_MIX_CONDOR_1 (0x5F27B0+6)
#define GS_MIX_CONDOR_2 (0x5F27BC+6)
#define GS_MIX_WING3_1 (0x5F2EB2+6)
#define GS_MIX_WING3_2 (0x5F2EBE+6)

#define TWISTING_SLASH_LEVEL (0x004A806B+7)
#define RAGEFUL_BLOW_LEVEL (0x004A8084+7)
#define DEATH_STAB_LEVEL (0x004A809D+7)
#define IMPALE_LEVEL (0x004A80B6+7)
#define INNER_LEVEL (0x004A80CF+7)
#define PENETRATION_LEVEL (0x004A80E8+7) 

//PK Bug Fix Limit
#define GS_PKBugLimitFixOffset1 (0x004D69F9+2)
#define GS_PKBugLimitFixOffset2 (0x004D6DD8+2) 
#define GS_PKBugLimitFixOffset3 (0x004D6E66+2)
//#define GS_PKBugLimitFixOffset1 (0x004D69BF+2)
//#define GS_PKBugLimitFixOffset2 (0x004D6D9E+2)
//#define GS_PKBugLimitFixOffset3 (0x004D6E2F+2)


#define GS_DROPPING_BUNDLE_OF_ZEN_COUNT (0x00552666+3) //Dropping Bundle Of Zen Count

#define GS_MAXZEN1 (0x0053F2F7+3) //Inventory
#define GS_MAXZEN2 (0x00452F23+3) //Vault
#define GS_MAXZEN3 (0x00453019+3) //Vault
#define GS_MAXZEN4 (0x00452F4F+2) //Vault

//Drop Rates:

#define GS_ITEM_EXC_DROP_RATE (0x41F0E1+1)//0x41F0E1+1
#define GS_EXC_SKILL_RATE (0x41F4EA+6)
#define GS_EXC_LUCK_RATE (0x41F4F4+6)
#define GS_SKILL_RATE (0x41F543+6)
#define GS_LUCK_RATE (0x41F54D+6) 
#define GS_KUNDUN_DROP_ITEM (0x0041DFFA+6)
#define GS_KUNDUN_DROP_ANC (0x0041E1BE+1)
//#define GS_KUNDUN_DROP_ANC1 (0x0041E004+6)


//Party
#define GS_SetExpParty3 (0x00516FE8+3)
#define GS_SetExpParty4 (0x00516FF7+3)
#define GS_SetExpParty5 (0x00517006+3)
#define GS_NormalExpParty2 (0x0051701E+3)
#define GS_NormalExpParty3 (0x0051702D+3)
#define GS_NormalExpParty4 (0x0051703C+3)
#define GS_NormalExpParty5 (0x0051704B+3)


//Skill buff

//#define GS_ManaShieldAgi (0x004FAA9A+1)
//#define GS_ManaShieldEne (0x004FAABA+1)
#define GS_ManaShieldAgi (0x004DB03D+1)
#define GS_ManaShieldAgiMaster (0x004FAA9A+1)
#define GS_ManaShieldEne (0x004DB05D+1)
#define GS_ManaShieldEneMaster (0x004FAABA+1)
#define GS_ManaShieldDiv (0x004DB082+1) 
#define GS_ManaShieldDivMaster (0x004FAB15+1)
//#define GS_ManaShieldMax (0x004DB0D6+1)

#define GS_BKBuffLifeVit (0x004DAD67+1)
#define GS_BKBuffLifeEne (0x004DAD87+1)
//Mix trainer NPC
#define GS_DARKHORSE_MIX (0x005EE59D+6)
#define GS_DARKSPIRIT_MIX (0x005EDE9C+6)
#define GS_ALLIANCE_REQ     (0x00467E0D+2)

//For GS_CS
#else
#define GS_CHAOS_PRICE    (0x565201+3)
#define GS_SOUL_PRICE     (0x5651E0+3)
#define GS_BLESS_PRICE    (0x5651BE+3)
#define GS_CREATION_PRICE (0x565245+3)
#define GS_LIFE_PRICE     (0x565223+3)
#define GS_GUARDIAN_PRICE (0x5653F1+3)
#define GS_FruitsPrice (0x5652C0+3)
#define GS_BlueFeatherPrice (0x5652FE+3)
#define GS_Clock_Price_Lvl1 (0x56574F+3)
#define GS_Clock_Price_Lvl2 (0x56575F+3)
#define GS_Clock_Price_Lvl3 (0x56576F+3)
#define GS_Clock_Price_Lvl4 (0x56577F+3)
#define GS_Clock_Price_Lvl5 (0x56578F+3)
#define GS_Clock_Price_Lvl6 (0x56579F+3)
#define GS_Clock_Price_Lvl7 (0x5657AF+3)

#define GS_SOULNOLUCK_RATE (0x54A023+3)
#define GS_SOULLUCK_RATE   (0x549F7C+2)
#define GS_SOUL_SOCKET_RATE (0x54A017+3)
#define GS_LIFE_RATE       (0x54A837+3) 
#define GS_MaxLevel1 (0x004F9FD2+3)
#define GS_MaxLevel2 (0x0051F1E9+1)
#define GS_MaxLevel3 (0x00596096+2)
#define GS_MaxLevel4 (0x005A6D16+1)
#define GS_MaxLevel5 (0x005FA038+2)
#define GS_MAX_LEVEL_NO_EXP (0x0057D2DD+3)
#define GS_UDP            (0x57D1AD+1) 
#define GS_DL_UP_POINT    (0x51F3CB+2)
#define GS_MG_UP_POINT     (0x51F3F3+2)
#define GS_NORMAL_UP_POINT (0x51F40A+2)
#define GS_MARLON_UP_POINT (0x51F42E+2)
#define GS_CC_MINUSER     (0x5A7CB0+3)
#define GS_ILLUSION_MINUSER (0x6132B5+6)
#define GS_BC_DROP_ID (0x59B52B+1) //
#define GS_BC_DROP_GROUP (0x59B52D+1) //
#define GS_SUMMON_ORB1 (0x4EB627+1) //Summon orb 1 
#define GS_SUMMON_ORB2 (0x4EB658+1) //Summon orb 2 
#define GS_SUMMON_ORB3 (0x4EB689+1) //Summon orb 3 
#define GS_SUMMON_ORB4 (0x4EB6BA+1) //Summon orb 4 
#define GS_SUMMON_ORB5 (0x4EB6EB+1) //Summon orb 5 
#define GS_SUMMON_ORB6 (0x4EB71C+1) //Summon orb 6 
#define GS_SUMMON_ORB7 (0x4EB750+1) //Summon orb 7 
#define GS_TRANSFORM_RING1 (0x4ED034+3) //Ring of transform 1 
#define GS_TRANSFORM_RING2 (0x4ED03D+3) //Ring of transform 2 
#define GS_TRANSFORM_RING3 (0x4ED046+3) //Ring of transform 3 
#define GS_TRANSFORM_RING4 (0x4ED04F+3) //Ring of transform 4 
#define GS_TRANSFORM_RING5 (0x4ED058+3) //Ring of transform 5 
#define GS_TRANSFORM_RING6 (0x4ED061+3) //Ring of transform 6 
#define GS_BOXKUNDUN_DROPLUCK (0x4ABD85+3)
#define GS_BOXKUNDUN_DROPSKILL (0x4ABD8C+3)
#define GS_BOXKUNDUN_DROPLEVEL (0x4ABD93+3)

#define CS_ChaosMix10_NormalItem (0x6203AF+6 )
#define GS_ChaosMix10_SpecialItem  (0x6203CB+6)
#define GS_ChaosMix10_SocketItem  (0x6203E8+6)

#define GS_ChaosMix_11_12_NormalItem  (0x62043F+6)
#define GS_ChaosMix_11_12_SpecialItem  (0x62045C+6)
#define GS_ChaosMix_11_12_SocketItem  (0x620479+6)

#define GS_ChaosMix13_NormalItem  (0x6204D1+6)
#define GS_ChaosMix13_SpecialItem  (0x6204EE+6)
#define GS_ChaosMix13_SocketItem  (0x62050A+6)

#define GS_ChaosMixAddLuck  (0x620548+2)
#define GS_DefautlMix		(0x00620519+6)
#define GS_ChaosMixMax1_10_13  (0x620557+6)
#define GS_ChaosMixMax2_10_13  (0x620563+6)

#endif




//#define LogAdd ((void(*) (BYTE,char*,...))0x00403C01)

void LoadIni();
void GS();
bool IniciaIni();
/*int ProcuraArquivo(char* Arquivo)
{
FILE *fp;

  fp= fopen(Arquivo,"rb");
  if (fp==0)
{
return 0;
}
else
fclose(fp)
return 1;
}
}*/


