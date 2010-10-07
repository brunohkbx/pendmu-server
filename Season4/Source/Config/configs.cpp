/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "offsets.h"
#include <string.h>
#include <windows.h>
#include "Global.h"
#include "Log.h"
#include "Structure.h"


////////////////////////////
// Jewel Price
///////////////////////////

bool Jewelops (char *ini)
{
	BYTE jwop ;
	
	jwop = GetPrivateProfileInt("Jewel","SoulNoLuckRate",55,ini);
    *(unsigned char*) GS_SOULNOLUCK_RATE = jwop ;

	jwop = GetPrivateProfileInt("Jewel","SoulLuckRate",70,ini);
    *(unsigned char*) GS_SOULLUCK_RATE = jwop ;

	jwop = GetPrivateProfileInt("Jewel","LifeRate",50,ini);
    *(unsigned char*) GS_LIFE_RATE = 100 - jwop ;

	return 1;

}


bool Server (char*ini) {

	BYTE Options1;
	DWORD Options ;
	
	Options = GetPrivateProfileInt("Server","UDPPort",60006,ini);
    *(unsigned int*) GS_UDP  = Options ;

	Options = GetPrivateProfileInt("Server","Item_Time",120,ini);
    *(unsigned int*) GS_ITEM_TIME1 = Options*1000 ;
	*(unsigned int*) GS_ITEM_TIME2 = Options*1000 ;
	/*
	Options = GetPrivateProfileInt("Server","Raklion_Delay",500,ini);
    *(unsigned int*) GS_Raklion_Delay = Options ;
	*/

	Options1 = GetPrivateProfileInt("Server","CCMinUser",1,ini);
    *(unsigned char*) GS_CC_MINUSER  = Options1 ;

	Options1 = GetPrivateProfileInt("Server","IllusionTempleMinUser",1,ini);
    *(unsigned char*) GS_ILLUSION_MINUSER  = Options1 ;

	
	Options1 = GetPrivateProfileInt("Server","AllianceMembers",14,ini);
    *(unsigned char*) GS_ALLIANCE_REQ  = Options1 ;

	
	Options1 = GetPrivateProfileInt("Server","Dark_Horse_Mix",60,ini);
    *(unsigned char*) GS_DARKHORSE_MIX  = Options1 ;

	Options1 = GetPrivateProfileInt("Server","Dark_Spirit_Mix",60,ini);
    *(unsigned char*) GS_DARKHORSE_MIX  = Options1 ;

	return 1;
}
bool EventConfig (char*ini)
{
	BYTE Event;
	
	//========== White Wizard Corp===============
	Event = GetPrivateProfileInt("Event","WizardDropItemID",13,ini);
    *(unsigned char*) GS_WW_ITEM_ID  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemGroup",14,ini);
    *(unsigned char*) GS_WW_ITEM_GROUP  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemLevel",0,ini);
    *(unsigned char*) GS_WW_ITEM_LVL  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemDuration",0,ini);
    *(unsigned char*) GS_WW_ITEM_DUR  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemSkill",0,ini);
    *(unsigned char*) GS_WW_ITEM_SKILL  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemLuck",0,ini);
    *(unsigned char*) GS_WW_ITEM_LUCK  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemOp",0,ini);
    *(unsigned char*) GS_WW_ITEM_OP  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemExc",0,ini);
    *(unsigned char*) GS_WW_ITEM_EXC  = Event ;

	Event = GetPrivateProfileInt("Event","WizardDropItemAnc",0,ini);
    *(unsigned char*) GS_WW_ITEM_ANC  = Event ;

	//============= BLood Caslte ================

	Event = GetPrivateProfileInt("Event","BCItemRewardID",15,ini);
    *(unsigned char*) GS_BC_DROP_ID  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardGroup",12,ini);
    *(unsigned char*) GS_BC_DROP_GROUP  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardLevel",0,ini);
    *(unsigned char*) GS_BC_DROP_LVL  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardDuration",0,ini);
    *(unsigned char*) GS_BC_DROP_DUR  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardSkill",0,ini);
    *(unsigned char*) GS_BC_DROP_SKILL  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardLuck",0,ini);
    *(unsigned char*) GS_BC_DROP_LUCK  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardOp",0,ini);
    *(unsigned char*) GS_BC_DROP_OP  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardExc",0,ini);
    *(unsigned char*) GS_BC_DROP_EXC  = Event;

	Event = GetPrivateProfileInt("Event","BCItemRewardAnc",0,ini);
    *(unsigned char*) GS_BC_DROP_ANC  = Event;

	//============== Illusion Temple ===============

	Event = GetPrivateProfileInt("Event","ITItemRewardID",15,ini);
    *(unsigned char*) GS_IT_DROP_ID  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardGroup",12,ini);
    *(unsigned char*) GS_IT_DROP_GROUP  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardLevel",0,ini);
    *(unsigned char*) GS_IT_DROP_LVL  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardDuration",0,ini);
    *(unsigned char*) GS_IT_DROP_DUR  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardSkill",0,ini);
    *(unsigned char*) GS_IT_DROP_SKILL  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardLuck",0,ini);
    *(unsigned char*) GS_IT_DROP_LUCK  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardOp",0,ini);
    *(unsigned char*) GS_IT_DROP_OP  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardExc",0,ini);
    *(unsigned char*) GS_IT_DROP_EXC  = Event;

	Event = GetPrivateProfileInt("Event","ITItemRewardAnc",0,ini);
    *(unsigned char*) GS_IT_DROP_ANC  = Event;
	
	
	return 1;

}


bool Characterops (char*ini) {

	BYTE ConfigChar1;
	DWORD ConfigChar ;
	BYTE PKFIX;
	
	ConfigChar = GetPrivateProfileInt("Character","MaxLevel",400,ini);
    *(unsigned int*) GS_MaxLevel1  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel2  = ConfigChar ;
	//*(unsigned int*) GS_MaxLevel3  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel4  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel5  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel6  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel7  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel8  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel9  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel10  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel11  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel12  = ConfigChar ;
	*(unsigned int*) GS_MaxLevel13  = ConfigChar ;
	Config.MaxLevel = ConfigChar;
	ConfigChar = GetPrivateProfileInt("Character","MaxLevelNoExp",401,ini);
    *(unsigned int*) GS_MAX_LEVEL_NO_EXP  = ConfigChar ; 

	ConfigChar1 = GetPrivateProfileInt("Character","MG_DL_UpPoints",7,ini);
    *(unsigned char*) GS_MG_UP_POINT1  = ConfigChar1 ;
	*(unsigned char*) GS_DL_UP_POINT1  = ConfigChar1 ;
	*(unsigned char*) GS_MG_UP_POINT2  = ConfigChar1 ;
	*(unsigned char*) GS_DL_UP_POINT2  = ConfigChar1 ;
	*(unsigned char*) GS_MG_UP_POINT3  = ConfigChar1 ;
	*(unsigned char*) GS_DL_UP_POINT3  = ConfigChar1 ;
	*(unsigned char*) GS_MG_UP_POINT4  = ConfigChar1 ;
	*(unsigned char*) GS_DL_UP_POINT4  = ConfigChar1 ;
	*(unsigned char*) GS_MG_UP_POINT5  = ConfigChar1 ;
	*(unsigned char*) GS_DL_UP_POINT5  = ConfigChar1 ;
	

	ConfigChar1 = GetPrivateProfileInt("Character","NormalCharacterUpPoints",5,ini);
    *(unsigned char*) GS_NORMAL_UP_POINT1  = ConfigChar1 ;
	*(unsigned char*) GS_NORMAL_UP_POINT2  = ConfigChar1 ;
	*(unsigned char*) GS_NORMAL_UP_POINT3  = ConfigChar1 ;
	*(unsigned char*) GS_NORMAL_UP_POINT4  = ConfigChar1 ;
	*(unsigned char*) GS_NORMAL_UP_POINT5  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","MarlonUpPoints",1,ini);
    *(unsigned char*) GS_MARLON_UP_POINT1  = ConfigChar1 ;
	*(unsigned char*) GS_MARLON_UP_POINT2  = ConfigChar1 ;
	*(unsigned char*) GS_MARLON_UP_POINT3  = ConfigChar1 ;
	*(unsigned char*) GS_MARLON_UP_POINT4  = ConfigChar1 ;
	*(unsigned char*) GS_MARLON_UP_POINT5  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon1",26,ini);
    *(unsigned char*) GS_SUMMON_ORB1  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon2",32,ini);
    *(unsigned char*) GS_SUMMON_ORB2  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon3",21,ini);
    *(unsigned char*) GS_SUMMON_ORB3  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon4",20,ini);
    *(unsigned char*) GS_SUMMON_ORB4  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon5",10,ini);
    *(unsigned char*) GS_SUMMON_ORB5  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon6",150,ini);
    *(unsigned char*) GS_SUMMON_ORB6  = ConfigChar1 ;

	ConfigChar1 = GetPrivateProfileInt("Character","OrbOfSummon7",151,ini);
    *(unsigned char*) GS_SUMMON_ORB7  = ConfigChar1 ;

	ConfigChar = GetPrivateProfileInt("Character","RingOfTransform1",2,ini);
    *(unsigned int*) GS_TRANSFORM_RING1  = ConfigChar ;

	ConfigChar = GetPrivateProfileInt("Character","RingOfTransform2",7,ini);
    *(unsigned int*) GS_TRANSFORM_RING2  = ConfigChar ;

	ConfigChar = GetPrivateProfileInt("Character","RingOfTransform3",14,ini);
    *(unsigned int*) GS_TRANSFORM_RING3  = ConfigChar ;

	ConfigChar = GetPrivateProfileInt("Character","RingOfTransform4",8,ini);
    *(unsigned int*) GS_TRANSFORM_RING4  = ConfigChar ;

	ConfigChar = GetPrivateProfileInt("Character","RingOfTransform5",9,ini);
    *(unsigned int*) GS_TRANSFORM_RING5  = ConfigChar ;

	ConfigChar = GetPrivateProfileInt("Character","RingOfTransform6",41,ini);
    *(unsigned int*) GS_TRANSFORM_RING6  = ConfigChar ;

	PKFIX = GetPrivateProfileInt("Character","PkLimit",3, ini) ;
    *(unsigned char *) GS_PKBugLimitFixOffset1 = PKFIX ;
    *(unsigned char *) GS_PKBugLimitFixOffset2 = PKFIX ;
    *(unsigned char *) GS_PKBugLimitFixOffset3 = PKFIX ;
       
 
return 1;

}

bool DropRate (char*ini) {
	DWORD Drop ;
	BYTE Drop1;

	Drop = GetPrivateProfileInt("Drop","ExcDropRate",2000,ini);
	*(unsigned int*) GS_ITEM_EXC_DROP_RATE  = Drop ;
	Drop = GetPrivateProfileInt("Drop","ExcSkillRate",64,ini);
	*(unsigned int*) GS_EXC_SKILL_RATE  = Drop ;
	Drop = GetPrivateProfileInt("Drop","ExcLuckRate",10,ini);
	*(unsigned int*) GS_EXC_LUCK_RATE  = Drop ;
	Drop = GetPrivateProfileInt("Drop","SkillRate",70,ini);
	*(unsigned int*) GS_SKILL_RATE  = Drop ;
	Drop = GetPrivateProfileInt("Drop","LuckRate",40,ini);
	*(unsigned int*) GS_LUCK_RATE  = Drop ;
	//Drop1 = GetPrivateProfileInt("Drop","BoxKunDunDropLuck",0,ini);
	//*(unsigned char*) GS_BOXKUNDUN_DROPLUCK  = Drop1 ;
	Drop1 = GetPrivateProfileInt("Drop","KunDunDropNumberOfItem",3,ini);
	*(unsigned char*) GS_KUNDUN_DROP_ITEM = Drop1 ;
	Drop = GetPrivateProfileInt("Drop","KunDunDropAncRate",10000,ini);
	*(unsigned int*) GS_KUNDUN_DROP_ANC  = Drop ;
	//*(unsigned int*) GS_KUNDUN_DROP_ANC1  = Drop ;
	Drop1 = GetPrivateProfileInt("Drop","BoxKunDunDropSkill",1,ini);
	*(unsigned char*) GS_BOXKUNDUN_DROPSKILL  = Drop1 ;
	Drop1 = GetPrivateProfileInt("Drop","BoxKunDunDropLevel",0,ini);
	*(unsigned char*) GS_BOXKUNDUN_DROPLEVEL  = Drop1 ;

	return 1;
}

bool Zen (char*ini) {
	DWORD Max;
	BYTE Bundle;
	Max = GetPrivateProfileInt("Zen","MaxZenInventory",2000000000,ini);
	*(unsigned long*) GS_MAXZEN1  = Max ;
	Max = GetPrivateProfileInt("Zen","MaxZenVault",1000000000,ini);
	*(unsigned long*) GS_MAXZEN2  = Max ;
	*(unsigned long*) GS_MAXZEN3  = Max ;
	*(unsigned long*) GS_MAXZEN4  = Max ;
	Bundle = GetPrivateProfileInt("Zen","DroppingBundleOfZenCount",6,ini);
	*(unsigned char*) GS_DROPPING_BUNDLE_OF_ZEN_COUNT  = Bundle ;

	return 1;
}


bool Skill (char*ini) {
		DWORD SkillLv;
		DWORD MNS;
		BYTE Skill1;
		SkillLv = GetPrivateProfileInt("Skill","TwishtingSlashLv",80,ini);
		*(unsigned int*) TWISTING_SLASH_LEVEL = SkillLv;
		SkillLv = GetPrivateProfileInt("Skill","RageFulBlowLv",170,ini);
		*(unsigned int*) RAGEFUL_BLOW_LEVEL = SkillLv;
		SkillLv = GetPrivateProfileInt("Skill","DeathStabLv",160,ini);
		*(unsigned int*) DEATH_STAB_LEVEL = SkillLv;
		SkillLv = GetPrivateProfileInt("Skill","ImpaleLv",28,ini);
		*(unsigned int*) IMPALE_LEVEL = SkillLv;
		SkillLv = GetPrivateProfileInt("Skill","InnerLv",120,ini);
		*(unsigned int*) INNER_LEVEL = SkillLv;
		SkillLv = GetPrivateProfileInt("Skill","PenetrationLv",130,ini);
		*(unsigned int*) PENETRATION_LEVEL = SkillLv;
		MNS = GetPrivateProfileInt("Skill","ManaShieldAgi",50,ini);
		*(unsigned int*) GS_ManaShieldAgi = MNS;
		*(unsigned int*) GS_ManaShieldAgiMaster = MNS;
		MNS = GetPrivateProfileInt("Skill","ManaShieldEne",200,ini);
		*(unsigned int*) GS_ManaShieldEne = MNS;
		*(unsigned int*) GS_ManaShieldEneMaster = MNS;
		MNS = GetPrivateProfileInt("Skill","ManaShieldDiv",40,ini);
		*(unsigned int*) GS_ManaShieldDiv = MNS;
		*(unsigned int*) GS_ManaShieldDivMaster = MNS;
		Skill1 = GetPrivateProfileInt("Skill","BK_BuffLifeVit",100,ini);
		*(unsigned char*) GS_BKBuffLifeVit = Skill1;
		Skill1 = GetPrivateProfileInt("Skill","BK_BuffLifeEne",20,ini);
		*(unsigned char*) GS_BKBuffLifeEne = Skill1;

		return 1;
}

bool ChaosMix (char*ini) {
		BYTE CMix;
		
		CMix = GetPrivateProfileInt("ChaosMix", "CM_Default_Rate",45,ini);
		*(unsigned char*) GS_ChaosMix10_NormalItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_10_Normal",50,ini);
		*(unsigned char*) GS_ChaosMix10_NormalItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_10_Special",50,ini);
		*(unsigned char*) GS_ChaosMix10_SpecialItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_10_Socket",50,ini);
		*(unsigned char*) GS_ChaosMix10_SocketItem = CMix;

		CMix = GetPrivateProfileInt("ChaosMix", "CM_11_12_Normal",45,ini);
		*(unsigned char*) GS_ChaosMix_11_12_NormalItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_11_12_Special",45,ini);
		*(unsigned char*) GS_ChaosMix_11_12_SpecialItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_11_12_Socket",45,ini);
		*(unsigned char*) GS_ChaosMix_11_12_SocketItem = CMix;

		
		CMix = GetPrivateProfileInt("ChaosMix", "CM_13_Normal",40,ini);
		*(unsigned char*) GS_ChaosMix13_NormalItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_13_Special",40,ini);
		*(unsigned char*) GS_ChaosMix13_SpecialItem = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_13_Socket",40,ini);
		*(unsigned char*) GS_ChaosMix13_SocketItem = CMix;

		CMix = GetPrivateProfileInt("ChaosMix", "CM_AddLuck_Normal",40,ini);
		*(unsigned char*) GS_ChaosMixAddLuck = CMix;
		CMix = GetPrivateProfileInt("ChaosMix", "CM_Max_10_13",75,ini);
		*(unsigned char*) GS_ChaosMixMax1_10_13 = CMix;
		*(unsigned char*) GS_ChaosMixMax2_10_13 = CMix;
		
		CMix = GetPrivateProfileInt("ChaosMix", "Wing_1_Mix",100,ini);
		*(unsigned char*) GS_MIX_WING1_1 = CMix;
		*(unsigned char*) GS_MIX_WING1_2 = CMix;

		CMix = GetPrivateProfileInt("ChaosMix", "Wing_2_Mix",90,ini);
		*(unsigned char*) GS_MIX_WING2_1 = CMix;
		*(unsigned char*) GS_MIX_WING2_2 = CMix;

		CMix = GetPrivateProfileInt("ChaosMix", "CondorMix",60,ini);
		*(unsigned char*) GS_MIX_CONDOR_1 = CMix;
		*(unsigned char*) GS_MIX_CONDOR_2 = CMix;

		CMix = GetPrivateProfileInt("ChaosMix", "Wing_3_Mix",40,ini);
		*(unsigned char*) GS_MIX_WING3_1 = CMix;
		*(unsigned char*) GS_MIX_WING3_2 = CMix;


		return 1;
}

bool Prices(char*ini) {
	DWORD price;
	
	price = GetPrivateProfileInt("Price","BlessPrice",9000000,ini);
    *(unsigned int*) GS_BLESS_PRICE = price ;
	price = GetPrivateProfileInt("Price","SoulPrice",6000000,ini);
    *(unsigned int*) GS_SOUL_PRICE = price ;
	price = GetPrivateProfileInt("Price","ChaosPrice",810000,ini);
    *(unsigned int*) GS_CHAOS_PRICE = price ;
	price = GetPrivateProfileInt("Price","LifePrice",45000000,ini);
    *(unsigned int*) GS_LIFE_PRICE = price ;
    price = GetPrivateProfileInt("Price","CreationPrice",36000000,ini);
    *(unsigned int*) GS_CREATION_PRICE = price ;
	price = GetPrivateProfileInt("Price","GuardianPrice",60000000,ini);
    *(unsigned int*) GS_GUARDIAN_PRICE = price ;
	price = GetPrivateProfileInt("Price","FruitsPrice",40000000,ini);
    *(unsigned int*) GS_FruitsPrice = price ;
	price = GetPrivateProfileInt("Price","BlueFeatherPrice",180000,ini);
    *(unsigned int*) GS_BlueFeatherPrice = price ;
	price = GetPrivateProfileInt("Price","BCClock_1_Price",15000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl1 = price ;
	price = GetPrivateProfileInt("Price","BCClock_2_Price",75000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl2 = price ;
	price = GetPrivateProfileInt("Price","BCClock_3_Price",150000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl3 = price ;
	price = GetPrivateProfileInt("Price","BCClock_4_Price",450000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl4 = price ;
	price = GetPrivateProfileInt("Price","BCClock_5_Price",750000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl5 = price ;
	price = GetPrivateProfileInt("Price","BCClock_6_Price",1200000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl6 = price ;
	price = GetPrivateProfileInt("Price","BCClock_7_Price",1500000,ini);
    *(unsigned int*) GS_Clock_Price_Lvl7 = price ;

	return 1;
}

bool PartyExp(char*ini) {
	DWORD Exp;
	
	Exp = GetPrivateProfileInt("Party","SetExpParty3",230,ini);
    *(unsigned int*) GS_SetExpParty3 = Exp ;
	Exp = GetPrivateProfileInt("Party","SetExpParty4",270,ini);
    *(unsigned int*) GS_SetExpParty4 = Exp ;
	Exp = GetPrivateProfileInt("Party","SetExpParty5",300,ini);
    *(unsigned int*) GS_SetExpParty5 = Exp ;
	Exp = GetPrivateProfileInt("Party","NormalExpParty2",160,ini);
    *(unsigned int*) GS_NormalExpParty2 = Exp ;
	Exp = GetPrivateProfileInt("Party","NormalExpParty3",180,ini);
    *(unsigned int*) GS_NormalExpParty3 = Exp ;
	Exp = GetPrivateProfileInt("Party","NormalExpParty4",200,ini);
    *(unsigned int*) GS_NormalExpParty4 = Exp ;
	Exp = GetPrivateProfileInt("Party","NormalExpParty5",220,ini);
    *(unsigned int*) GS_NormalExpParty5 = Exp ;

	return 1;
}
bool OtherConfig (char * ini)
{
	int iValue;
	iValue = GetPrivateProfileInt("Server","AllowPK_GoBC",0,ini);
	if (iValue == 1)
	{
		BYTE PKAllowBC[1]={0xEB};
		memcpy((int*)0x0046227F,PKAllowBC,sizeof(PKAllowBC));
		memcpy((int*)0x00460A21,PKAllowBC,sizeof(PKAllowBC));
		memcpy((int*)0x005A5715,PKAllowBC,sizeof(PKAllowBC));
	}
	iValue = GetPrivateProfileInt("Server","AllowPK_GoDevil",0,ini);
	if (iValue == 1)
	{
		BYTE PKAllowDS[1]={0xEB};
		memcpy((int*)0x0045FF1F,PKAllowDS,sizeof(PKAllowDS));
		memcpy((int*)0x00460958,PKAllowDS,sizeof(PKAllowDS));
		memcpy((int*)0x005A444F,PKAllowDS,sizeof(PKAllowDS));
	}
	return 1;
}

	
		
bool IniciaIni()
{
	//char a[255];
	char aini[]= "..//OptionsData//Options.ini";
	bool rResultado;
	rResultado  = Jewelops ( aini );
	rResultado  = Server ( aini );
	rResultado  = EventConfig( aini );
	rResultado  = Characterops ( aini );
	rResultado  = DropRate ( aini );
	//rResultado  = ChaosMix ( aini );
	rResultado  = Skill ( aini );
	rResultado  = Zen ( aini );
	rResultado  = Prices ( aini );
	rResultado  = PartyExp ( aini );
	rResultado  = OtherConfig ( aini);
	return 1;
}
/*void Function()
{
DWORD OldProtect;
LPVOID lpAddress = (LPVOID)0x00401000;
if ( VitualProtect (lpAddress,0x246000,PAGE_EXECUTE_READWRITE,&OldProtect))
{
//sprintf( a, "Load DLL Thanh Cong ^^");
//LogAdd(3 ,a);//
MessageBox(NULL, "LaiPro.dll Succes.", "Success",MB_OK);
if(!ProcuraArquivo(aini))
{
MessageBox(NULL,"Co van de voi File .\n Hay cai dat lai!","Option.ini",NULL)
::ExitProcess(0);
}
bool init;
init= IniciaIni();
}
}*/

char GSIni[] ="..//OptionsData//Options.ini";
char CmdIni[]="..//OptionsData//Commands.ini";
char MsgIni[]="..//OptionsData//Messages.ini";
void LoadIni()
{
	SMDGSfile = fopen(GSIni,"rb");
	if (SMDGSfile!=NULL)
	{
		fclose(SMDGSfile);
		GetPrivateProfileString("GameServerInfo","ConnectNotice1","0o0Mr.LAI0o0",ConnectNotice1,50,GSIni);
		GetPrivateProfileString("GameServerInfo","ConnectNotice2","0o0Mr.LAI0o0",ConnectNotice2,50,GSIni);
		GetPrivateProfileString("GameServerInfo","ConnectNotice3","0o0Mr.LAI0o0",ConnectNotice3,50,GSIni);
		//Other Config
		Config.IsProtocol = GetPrivateProfileInt("Protocol","GSProtocol",1,GSIni);
		Config.IsGADrop = GetPrivateProfileInt("Event","IsGoldenArcherDrop",0,GSIni);
		Config.GANeedRena = GetPrivateProfileInt("Event","GoldenArcherNeedRena",2,GSIni);
		Config.QuestCount = GetPrivateProfileInt("QuestSystem","MaxQuests",1,"..\\OptionsData\\QuestSystemSettings.ini");
			
	}
	SMDMsgfile = fopen(MsgIni,"rb");

	if (SMDMsgfile!=NULL)
	{
		fclose(SMDMsgfile);

		GetPrivateProfileString("Message","MSG_01","[Post System]: This command had been disabled.",MSG01,100,MsgIni);
		GetPrivateProfileString("Message","MSG_02","[Post System]: Command error (eg: /post <mgs>)",MSG02,100,MsgIni);
		GetPrivateProfileString("Message","MSG_03","[Post System]: Syntax error (eg: /post <mgs>)",MSG03,100,MsgIni);
		GetPrivateProfileString("Message","MSG_04","[Post System]: Need %d level to used /post.",MSG04,100,MsgIni);
		GetPrivateProfileString("Message","MSG_05","[POST SYSTEM] Lacking %d Zend.",MSG05,100,MsgIni);
		GetPrivateProfileString("Message","MSG_06","[POST]: %s ",MSG06,100,MsgIni);
		GetPrivateProfileString("Message","MSG_07","[Add]: System disabled.",MSG07,100,MsgIni);
		GetPrivateProfileString("Message","MSG_08","[Add]: Not enought [%d] Level.",MSG08,100,MsgIni);
		GetPrivateProfileString("Message","MSG_09","[Add]: Error.",MSG09,100,MsgIni);
		GetPrivateProfileString("Message","MSG_10","[Add]: Not Enought Points.",MSG10,100,MsgIni);
		GetPrivateProfileString("Message","MSG_11","[Add]: Lacking %d Zen.",MSG11,100,MsgIni);
		GetPrivateProfileString("Message","MSG_12","[Add]: Max : [%d] points per add.",MSG12,100,MsgIni);
		GetPrivateProfileString("Message","MSG_13","[Add]: This command use for DarkLord or LordEmperor.",MSG13,100,MsgIni);
		GetPrivateProfileString("Message","MSG_14","[Add]: Add Successfull. Switch character to update.",MSG14,100,MsgIni);
		GetPrivateProfileString("Message","MSG_15","[Add]: Added [%d] Points. Odd [%d] Points.",MSG15,100,MsgIni);
		GetPrivateProfileString("Message","MSG_16","[Skin]: You not enought %s level.",MSG16,100,MsgIni);
		GetPrivateProfileString("Message","MSG_17","[Time]: Time is %02d : %02d : %02d",MSG17,100,MsgIni);
		GetPrivateProfileString("Message","MSG_18","[DUEL]: This room is full!",MSG18,100,MsgIni);
		GetPrivateProfileString("Message","MSG_19","[DUEL]: You have left DUEL ROOM!",MSG19,100,MsgIni);
		GetPrivateProfileString("Message","MSG_20","[DUEL]: You will be automatically warped in 10 seconds.",MSG20,100,MsgIni);
		GetPrivateProfileString("Message","MSG_21","[Duel System][Room %d] %s defeats %s",MSG21,100,MsgIni);
		GetPrivateProfileString("Message","MSG_22","[Duel System][Room %d] Score %d vs %d",MSG22,100,MsgIni);
		GetPrivateProfileString("Message","MSG_23","[DUEL]: Min Level for Request/Acept Duel is: %d",MSG23,100,MsgIni);
		GetPrivateProfileString("Message","MSG_24","[PCPointShop] Character %s Earned %d Points",MSG24,100,MsgIni);
		GetPrivateProfileString("Message","MSG_25","[PCPointShop] Maximum points ammount reached!",MSG25,100,MsgIni);
		GetPrivateProfileString("Message","MSG_26","~[Quest] : %s for finish this quest, go to devias, to special quest guard",MSG26,100,MsgIni);
		GetPrivateProfileString("Message","MSG_27","~[Quest] : Number: %d ,Name: %s",MSG27,100,MsgIni);
		GetPrivateProfileString("Message","MSG_28","~[Quest] : Info: %s",MSG28,100,MsgIni);
		GetPrivateProfileString("Message","MSG_29","~[Quest] : %s Complete this quest and go to me for reward",MSG29,100,MsgIni);
		GetPrivateProfileString("Message","MSG_30","~[Quest] : to see again quest info - write /questinfo",MSG30,100,MsgIni);
		GetPrivateProfileString("Message","MSG_31","~[Quest] : %s you Finished all quests",MSG31,100,MsgIni);
		GetPrivateProfileString("Message","MSG_32","~[Quest] : Ins't process",MSG32,100,MsgIni);
		GetPrivateProfileString("Message","MSG_33","~[Quest] : QuestName:",MSG33,100,MsgIni);
		GetPrivateProfileString("Message","MSG_34","~[Quest] : %s:",MSG34,100,MsgIni);
		GetPrivateProfileString("Message","MSG_35","~[Quest] : QuestInfo: %s",MSG35,100,MsgIni);
		GetPrivateProfileString("Message","MSG_36","~[QUEST] Quest not finished, please check conditions",MSG36,100,MsgIni);				
		GetPrivateProfileString("Message","MSG_37","Enjoy reward!",MSG37,100,MsgIni);				
			
	}
	SMDCmdfile = fopen(CmdIni,"rb");

	if (SMDCmdfile!=NULL)
	{
		fclose(SMDCmdfile);
		//Command Load Config
		//Add Command
		Config.IsAdd = GetPrivateProfileInt("Add","IsAdd",1,CmdIni);
		Config.AddLevel = GetPrivateProfileInt("Add","AddLevel",100,CmdIni);
		Config.AddMaxPoints = GetPrivateProfileInt("Add","MaxPoint",100,CmdIni);
		Config.AddCost = GetPrivateProfileInt("Post","AddCost",1000,CmdIni);
		
		//Post Command
		Config.IsPost = GetPrivateProfileInt("Post","IsPost",1,CmdIni);
		Config.PostLevel = GetPrivateProfileInt("Post","LevelPost",1,CmdIni);
		Config.PostCost = GetPrivateProfileInt("Post","PostCost",1,CmdIni);

		//Reload Coomand
		Config.IsReload = GetPrivateProfileInt("Reload","IsReload_Cmd",1,CmdIni);

		//Skin Command
		Config.IsSkin = GetPrivateProfileInt("Skin","IsSkin",1,CmdIni);
		Config.IsOnlyGMSkin = GetPrivateProfileInt("Skin","IsSkinOnlyForGM",1,CmdIni);
		Config.SkinLevel = GetPrivateProfileInt("Skin","Level",50,CmdIni);

		

		
	}
	else
	{
		MessageBoxA(0, "Lacking .Ini File. GameServer Shutdown", "--::Syrius DLL::--", MB_OK | MB_ICONSTOP);
		::ExitProcess(0);
	}
}
/*
CONFIGSTRUCT config;

void ReadCommonServerInfoEx(const char *file, CONFIGSTRUCT *buffer) {
	
	buffer->m_RenasCount	= GetPrivateProfileInt("GoldenArcher", "RenasCount", 0, file);


	func::StdOut("[CONFIGURATION] Main configuration has been read.");
	ReadGoldenArcherFile(buffer->v_GABag, "..\\data\\GoldenArcher.txt");
}


void ReadGoldenArcherFile(std::vector<std::string> &buffer, const char *filename) {
	FILE* hFile;
	fopen_s(&hFile, filename, "r");
	char Line[1024];

	if(hFile == 0)
	{
		MessageBox(0, "ReadGoldenArcherFile() - Can't find file.", "Fatal Error", MB_OK | MB_ICONSTOP);
		func::StdOut("Can't open %s file to read golden archer bag definitions.", filename);
		return;
	}

	buffer.clear();
    while(!feof(hFile))
    {
        fgets(Line, 1024, hFile);
		if(strcmp(Line, "end") == 0)
			break;

        if(Line[strlen(Line) - 1] == '\n' || Line[strlen(Line) - 1] == '\r')
        {
            if(Line[0] != '/' || Line[1] != '/')
				buffer.push_back(Line);
        }
    }

    fclose(hFile);
	func::StdOut("[CONFIGURATION] Golden archer bag file has been read.");
}
*/