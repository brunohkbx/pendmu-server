/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include "Utils.h"
#include "Fixs.h"
#include "ChaosMachine.h"
#include "User.h"
#include "GameServer.h"
char FixFile[] = "..//OptionsData//Fixs.ini";


void __declspec(naked) LevelSmallConvertFix1()
{
	_asm
	{
	//00526333 Hook
	CMP DWORD PTR SS:[EBP+0x8],0x0E //14
	JNZ Item13Check;
	MOV AL,0x6
	mov esi,0x00526389;
	JMP esi;
Item13Check:
	CMP DWORD PTR SS:[EBP+0x8],0x0D //13
	JNZ Check1;
	MOV AL,0x6
	mov esi,0x00526389;
	JMP esi;

Check1:
	CMP DWORD PTR SS:[EBP+0x8],0x0C //12
	JNZ Item11Check;
	MOV AL,0x6
	mov esi,0x00526389;
	JMP esi;
Item11Check:
	CMP DWORD PTR SS:[EBP+0x8],0x0B //11
	JNZ JnzEnd
	MOV AL,0x5
	mov esi,0x00526389;
	JMP esi;

JnzEnd:
	mov edi, 0x00526347;
	jmp edi;
	}
}

void __declspec(naked) LevelSmallConvertFix()
{
	_asm
	{
	//0052629A Hook
	//Original
	CMP DWORD PTR SS:[EBP-0x4],0x0E; //14
	JNZ SHORT Item13;
	MOV AL,0x6;	//Return 6
	
	mov esi, 0x005262F0;
	JMP esi;

Item13:
	CMP DWORD PTR SS:[EBP-0x4],0x0D; //13
	JNZ SHORT Item12;
	MOV AL,0x6;	//Return 6
	
	mov esi, 0x005262F0;
	JMP esi;

Item12:
	CMP DWORD PTR SS:[EBP-0x4],0x0C; //12
	jnz JnzEnd;
	MOV AL,0x6;	//Return 6
	
	mov esi, 0x005262F0;
	JMP esi;

JnzEnd:
	mov edi, 0x005262A4;
	jmp edi;
	}
}

void __declspec(naked) DurabFixBeta()
{	
	_asm
	{
//Original Function
	CMP DWORD PTR SS:[EBP+0xC],0x0D; // +13 Level
	JNZ Item14Level;
	MOV EDX,DWORD PTR SS:[EBP+0x8];
	IMUL EDX,EDX,0x70;
	XOR EAX,EAX;
	MOV AL,BYTE PTR DS:[EDX+0x7B135F0];
	MOV ECX,DWORD PTR SS:[EBP+0xC];
	LEA EDX,DWORD PTR DS:[EAX+ECX*0x2+0x6]; //Durability + Level*2+6 = Durability
	MOV DWORD PTR SS:[EBP-0x4],EDX;

	mov esi, 0x00558C8D;
	jmp esi;

 Item14Level:
	CMP DWORD PTR SS:[EBP+0xC],0x0E; // +14 Level
	JNZ Item15Level;
	MOV EDX,DWORD PTR SS:[EBP+0x8];
	IMUL EDX,EDX,0x70;
	XOR EAX,EAX;
	MOV AL,BYTE PTR DS:[EDX+0x7B135F0];
	MOV ECX,DWORD PTR SS:[EBP+0xC];
	LEA EDX,DWORD PTR DS:[EAX+ECX*0x2+0x0B]; //Durability + Level*2+6 = Durability
	MOV DWORD PTR SS:[EBP-0x4],EDX;
	
	mov esi, 0x00558C8D;
	jmp esi;

 Item15Level:
	CMP DWORD PTR SS:[EBP+0xC],0x0F; // +15 Level
	jnz DurEnd;
	MOV EDX,DWORD PTR SS:[EBP+0x8];
	IMUL EDX,EDX,0x70;
	XOR EAX,EAX;
	MOV AL,BYTE PTR DS:[EDX+0x7B135F0];
	MOV ECX,DWORD PTR SS:[EBP+0xC];
	LEA EDX,DWORD PTR DS:[EAX+ECX*0x2+0x11]; //Durability + Level*2+6 = Durability
	MOV DWORD PTR SS:[EBP-0x4],EDX;
	
	mov esi, 0x00558C8D;
	jmp esi;
	

DurEnd:
	mov edi, 0x00558C75;
	jmp edi;
	}
}

void __declspec(naked) FixNewPetDurabDown()
{
		//005116D2 hook, jmp back 005116E0
		_asm
		{	
			//Angel
			MOV EDX,DWORD PTR SS:[EBP-0xC]
			MOVSX EAX,WORD PTR DS:[EDX+0x6]
			CMP EAX,0x1A00
	        JE CallDurDown
			
			//Panda
			MOV EDX,DWORD PTR SS:[EBP-0xC]
			MOVSX EAX,WORD PTR DS:[EDX+0x6]
			CMP EAX,0x1A50
	        JE CallDurDown

			//Skeleton
			MOV EDX,DWORD PTR SS:[EBP-0xC]
			MOVSX EAX,WORD PTR DS:[EDX+0x6]
			CMP EAX,0x1A7B
	        JE CallDurDown

			mov edi, 0x005116E0;
			jmp edi;
CallDurDown:
			mov edi, 0x005116EF;
			jmp edi;
		}
}



void Fixs()
{
#ifdef GameServer90

BOOL FixGS = GetPrivateProfileInt("GameServer","GS_Fix",0,FixFile);
BOOL FixSocket = GetPrivateProfileInt("GameServer","IsSocketExc_Item",0,FixFile);
BOOL Maxstats = GetPrivateProfileInt("Character","Is_65k_Maxstats",0,FixFile);
BOOL FixDelete = GetPrivateProfileInt("Character","Fix_ID",0,FixFile);
BOOL FixAcient = GetPrivateProfileInt("GameServer","IsAncientExc_Item",0,FixFile);
BOOL JohOnAnc = GetPrivateProfileInt("GameServer","IsJoHOnAncient_Item",0,FixFile);
BOOL FixGM = GetPrivateProfileInt("Character","FixGM",0,FixFile);
BOOL SaveLogs = GetPrivateProfileInt("GameServer","SaveGS_Log",1,FixFile);

if(FixDelete==TRUE)
{
memset((PBYTE)DELETEGUILD,0x90,6); //DELETE GUILD
memset((PBYTE)LEAVEGUILD1,0x90,2); // FIX LEAVE GUILD
memset((PBYTE)LEAVEGUILD2,0x90,5); // FIX LEAVE GUILD
memset((PBYTE)LEAVEGUILD3,0x90,2); // FIX LEAVE GUILD
memset((PBYTE)DELETECHAR,0x90,5); // fix del char
memset((PBYTE)FIXPOITION1,0x90,15); 
memset((PBYTE)FIXPOITION2,0x90,15); 
memset((PBYTE)FIXPOITION3,0x90,15); 
memset((PBYTE)FIXPOITION4,0x90,15); 
}
//Exc Socket Item
if (FixSocket==TRUE)
{
	SetByte(0x0054F06F,0xEB);
}
//Exc + acient Item
if (FixAcient==TRUE)
{
	SetByte(0x54EFC6,0xEB);
}

if (JohOnAnc==TRUE)
{
	SetByte(0x005C600A,0xEB);
}

if (FixGM==TRUE)
{
	SetByte(0x0050514B,0xEB);
}
if (SaveLogs==FALSE)
{
	//Disable Log Create File
	SetRetn (0x004024E1);
	SetNop (0x004024E2,4);

	//Disable Log Datechange Create File
	SetRetn (0x004076D0);
	SetNop (0x004076D1,4);
	//Disable write Log Normal
	SetNop (0x004C0F2E,2);

	//Disable write Log Color
	SetNop (0x004C1020,2);

	//Disable write Log DateTime
	SetNop (0x004C11B0,2);

}



if(FixGS==TRUE)
{
	//GM Move , WARNING, disable /move string int int int 
/*	
	SetByte(0x005609DB,0xE9); 
	SetByte(0x005609DC,0xF5); 
	SetByte(0x005609DD,0x00); 
	SetByte(0x005609E0,0x00); 
	SetByte(0x005609E1,0x00);
	SetByte(0x005609E2,0x90);
	*/
	// [Fix] Party PK IN Shop
	SetByte(0x004450EE, 0xEB);
	// [Fix] Marder Move;
	//SetByte(0x00560C90, 0x06); 
	
	
	SetByte(0x004369B7,0xEB);  //Socket Serial fix
	SetNop(0x004A17D0,7);		// Drop W/ luck Fix
	SetNop(0x004A23BA,7); // Selupan Drop Luck Fix
	SetNop(0x0053F5CE,7); //Kun Dun Drop ANC + Luck Fix
	//SetNop(0x004A1FA9,7); //Kun Dun Drop EXC + Luck Fix
	SetNop(0x0049E008,7); // Fix Maya Hand Drop Luck
	SetNop(0x0049E378,7); // Fix NightMare Drop Luck
	SetNop(0x0049DC81,7); // Fix Boss Crywolf Drop Luck
	SetNop(0x0049D881,7); // Fix Dark Elf Crywolf Drop Luck
	
	//SetNop(0x0049A5C7,7); // Fix Red Ribbon Box Drop Luck
	SetNop(0x0049AA55,7); // Fix Green Ribbon Box Drop Luck
	SetNop(0x0049AF25,7); // Fix Blue Ribbon Box Drop Luck

	SetNop(0x0049B875,7); // Red Chocolate Box Drop Luck Fix
	SetNop(0x0049BD45,7); // Blue Chocolate Box Drop Luck Fix

	SetNop(0x0049C695,7); // Vermilion Box Drop Luck Fix
	SetNop(0x0049CB65,7); // Deep Blue Box Drop Luck Fix
	SetNop(0x004A00A1,7); // GM Box Drop Luck Fix

	SetNop(0x004A054D,7); // Green Chaos Box Drop Luck Fix
	SetNop(0x004A09DD,7); // Red Chaos Box Drop Luck Fix
	SetNop(0x004A0E6D,7); // Puple Chaos Box Drop Luck Fix

	//SetNop(0x004A12FD,7); // Illusion Fix Drop Luck

	//Fix Golden Invasion Message
	BYTE FixGoldenInvMsg[3] = { 0xEB, 0x51, 0x90 };
	memcpy((int*)0x0048018A,FixGoldenInvMsg,sizeof(FixGoldenInvMsg));                                    

	BYTE FixGoldenInvMsg1[15] = { 0x00, 0x00, 0x83, 0xC4, 0x08, 0x50, 0xE8, 0xED, 0x3F, 0xF8, 0xFF, 0xEB, 0xA5, 0x00, 0x00 };
	memcpy((int*)0x004801DB,FixGoldenInvMsg1,sizeof(FixGoldenInvMsg1));

	// Raklion Fix
	BYTE RaklionFix[3] = {0x81,0x51,0x01};
	memcpy((int*)0x0061018E,RaklionFix,sizeof(RaklionFix));

	
	

	//SetByte(0x004D6A05,0xEB);	// PK Kill
	//SetByte(0x004D6DE4,0xEB);	//
	//SetByte(0x004D6E72,0xEB);	//
	//PK Kill
	//SetNop(0x004D69DB,2);
	//SetNop(0x004D6DBA,2);
	//SetNop(0x004D6E4B,2);
	SetByte(0x004D69C1,0x7);
	SetByte(0x004D6DA0,0x7);
	SetByte(0x004D6E31,0x7);
	//Arena can't PVP
	SetByte(0x004D6B46,0x3F);
	
	//Party Move
	BYTE ppm[2] = {0xEB, 0x0C};
	memcpy((int*)0x00560C69,ppm,sizeof(ppm)); 


	//Party Kill
	BYTE ppk[6] = {0xE9, 0x1D, 0x01, 0x00, 0x00, 0x90};
    memcpy((int*)0x004D6D56,ppk,sizeof(ppk));





//Fix Golden Monster Box Luck + 5 = Box Kundun 1

//Fix tantalos from drop +3, back to +5 
    BYTE FixGoldenTantalosDrop[7]={0xC7, 0x45, 0xEC, 0x0C, 0x00, 0x00, 0x00}; 
    memcpy((int*)0x0041EB27,FixGoldenTantalosDrop,sizeof(FixGoldenTantalosDrop)); 

    //Delete drop from Golden Wheel 
    SetNop(0x0041EAC7,2); 
	//Delete Drop From Golden Vepar
	SetNop(0x0041E9F7,2);
	//Fix Golden Budge Dragon Drop Box Luck :|
	BYTE FixGoldenBudgeDragonDrop[7]={0xC7, 0x45, 0xEC, 0x00, 0x00, 0x00, 0x00}; 
    memcpy((int*)0x0041E8A6,FixGoldenBudgeDragonDrop,sizeof(FixGoldenBudgeDragonDrop)); 

    //Fix Titan, +2BOK 
    BYTE FixGoldenTitanDrop[7]={0xC7, 0x45, 0xEC, 0x09, 0x00, 0x00, 0x00}; 
    memcpy((int*)0x0041E962,FixGoldenTitanDrop,sizeof(FixGoldenTitanDrop)); 

    //Fix randomizer on +3BOK 
    BYTE FixGoldenDerconDrop[7]={0xBA, 0x0A, 0x00, 0x00, 0x00, 0x90, 0x90}; 
    memcpy((int*)0x0041EDF5,FixGoldenDerconDrop,sizeof(FixGoldenDerconDrop)); 

    //Fix looping from 5 rep. to 1 
    BYTE FixGoldenDerconDropLOOP[7]={0x83, 0xBD, 0xF8, 0xFE, 0xFF, 0xFF, 0x01}; 
    memcpy((int*)0x0041ED91,FixGoldenDerconDropLOOP,sizeof(FixGoldenDerconDropLOOP)); 

    //Fix Lizard King 
    BYTE FixGoldenLizardDrop[7]={0xC7, 0x45, 0xEC, 0x0B, 0x00, 0x00, 0x00}; 
    memcpy((int*)0x0041EA44,FixGoldenLizardDrop,sizeof(FixGoldenLizardDrop)); 

	//Fix Summoner Berserker 65k+ Damage
	BYTE FixBerserker[] = { 0x68, 0xBC, 0x02, 0x00, 0x00 };
	memcpy((int*)0x004E5B45,FixBerserker,sizeof(FixBerserker));

	//Fix Mana Shield 32k+ Stats
	BYTE FixMShield1[] = { 0xB9, 0xBC, 0x02, 0x00, 0x00 };
	memcpy((int*)0x004DB03D,FixMShield1,sizeof(FixMShield1));
	memcpy((int*)0x004FAA9A,FixMShield1,sizeof(FixMShield1));	

	BYTE FixMShield2[] = { 0xBE, 0x20, 0x03, 0x00, 0x00 };
	memcpy((int*)0x004DB05D,FixMShield2,sizeof(FixMShield2));
	memcpy((int*)0x004FAABA,FixMShield2,sizeof(FixMShield2));


// Fix Crash Dump Create File
	SetByte(0x004C7041,0xE9);	//C
	SetByte(0x004C7042,0x2E);	//R
	SetByte(0x004C7043,0x01);	//A
	SetByte(0x004C7044,0x00);	//S
	SetByte(0x004C7045,0x00);	//H
	SetByte(0x004C7046,0x90);	//Dmp 
	
/*
	// Battle Soccer Fix
	SetByte(0x00560E5F,0x45);
	SetByte(0x00560E60,0x10);
	SetByte(0x00560F18,0x8C);
	SetByte(0x00560F19,0x0F);
	*/
	
	SetByte(0x004369B7,0xEB);	// Socket Serial
	
	SetByte(0x0043880E,0x90);	// Hack reporting FIX
	SetByte(0x0043880F,0x90);	//
	SetByte(0x00438830,0xE9);	//
	SetByte(0x00438831,0x74);	//
	SetByte(0x00438832,0x01);	//
	SetByte(0x00438833,0x00);	//
	SetByte(0x00438835,0x90);	//
	

	SetNop(0x00458612,27);		// Protocol Error FIX
	SetNop(0x004B33DE,6);		// error-L2 : Index(%d) %x %x %x FIX
	SetByte(0x004B409F,0x90);	// Invalid Socket FIX
	SetByte(0x004B40A0,0x90);	//
	SetByte(0x004B41CF,0xEB);	//
	//Disabled if don't work

		//ChaosBox new mix
		BYTE ChaosBox[] = { 0xFF, 0x25, 0x90, 0x00, 0x80, 0x00, 0x90, 0x90 };
		memcpy((int*)0x0051F86C,ChaosBox,sizeof(ChaosBox));
		//Hook ChaosBox new mix
		*(unsigned int*)0x00800090  = (unsigned int)ChaosboxItemsRegardingEx;
		
		//ChaosBoxInit Fix (maybe unexpected consequences)
		BYTE ChaosBoxInitHook[] = { 0xC3, 0x90, 0x90 };
		memcpy((int*)0x005E84FE,ChaosBoxInitHook,sizeof(ChaosBoxInitHook));


		//Serial0Fix
		SetByte(0x004403C2,0xEB); // Item drop
		//SetByte(0x00446676,0xEB); // Sell item
		//SetByte(0x0044A55A,0xEB); // Pshop
		//SetByte(0x0044C494,0xEB); // Pshop Buy
		//SetByte(0x0045A3B2,0xEB); // Use Item
		SetByte(0x00520085,0xEB); // Move item
		SetByte(0x00523844,0xEB); // Trade 1 
		SetByte(0x00524168,0xEB); // Trade 2
		SetByte(0x0054AFD6,0xEB); // Mix Jawel
		SetByte(0x0054B966,0xEB); // Unmix Jawel


		BYTE SERIAL_0[9] = {0xE9,0x90,0x00,0x00,0x00,0x90,0x90,0x90,0x90};
		memcpy((int*)0x00542BD0,SERIAL_0,sizeof(SERIAL_0));
		//Serial 0 when use item
		BYTE Serial0UseItem[6] = {0xE9,0xAD,0x00,0x00,0x00,0x90};
		memcpy ((int*)0x0045A3B2, Serial0UseItem, sizeof(Serial0UseItem));
		
		//Serial 0 when sell item
		BYTE Serial0SelItem[6] = {0xE9,0x81,0x00,0x00,0x00,0x90};
		memcpy ((int*)0x00446676, Serial0SelItem, sizeof(Serial0SelItem));
		
		
		//Serial 0 Personal Shop
		BYTE Serial0PSHop[6] = {0xE9,0xB0,0x00,0x00,0x00,0x90};
		memcpy ((int*)0x0044A55A, Serial0PSHop, sizeof(Serial0PSHop));

		//Serial 0 Buy in Personal Shop
		BYTE Serial0BPSHop[6] = {0xE9,0xAE,0x00,0x00,0x00,0x90};
		memcpy ((int*)0x0044C494, Serial0BPSHop, sizeof(Serial0BPSHop));
		

//Fix BC 8

		BYTE cFixBCMoveMaster[3] = {0x33,0xC0,0x90}; // xor eax,eax
		memcpy((int*)0x0057FE6D,cFixBCMoveMaster,sizeof(cFixBCMoveMaster));
		memcpy((int*)0x0057FDB3,cFixBCMoveMaster,sizeof(cFixBCMoveMaster));

		// Fix DS 7:
		SetByte (0x460396,0xEB);
		SetByte(0x005D9771,0xEB);	// Illusion Temple enter
	
//Fix Life 28 op
SetNop(0x0042F2F4,2);    //Fix Life 28 op
SetNop(0x00501F4C,2);    //Fix Life 28 op
SetNop(0x005573C4,2);    //Fix Life 28 op

SetByte(0x00501F89,0x7); //Fix Life 28 op
SetByte(0x005378D0,0x7); //Fix Life 28 op


//Error 0x0000
SetRetn(0x4069AB);
SetNop(0x4069AC,4);
//HackTool DC
SetRetn(0x00404584);
SetNop(0x00404585,4);
//DestroyGiocp
SetRetn(0x403233);
SetNop(0x403234,4);
/*
//Fix IsSetItem Check error: (itemnum:-1)
SetRetn(0x405551);
SetNop(0x405552,4);
*/
//Packet Per second
BYTE cFixPacketPerSecond[6] = {0xE9,0x42,0x01,0x00,0x00,0x90};
memcpy((int*)0x004B10FB,cFixPacketPerSecond,sizeof(cFixPacketPerSecond));
//Monster AI Element Fix
SetByte (0x5B0319+3,0xFF);
}

//MaxStat 65k
if (Maxstats==TRUE)
{
SetByte(0x004567F3+1,0xB7);
SetByte(0x004592A2+1,0xB7);
SetByte(0x0045CBB1+1,0xB7);
SetByte(0x004AD9A7+1,0xB7);
SetByte(0x004CF77C+1,0xB7);
SetByte(0x004CFD34+1,0xB7);
SetByte(0x004CFD9C+1,0xB7);
SetByte(0x004CFE05+1,0xB7);
SetByte(0x004CFE5A+1,0xB7);
SetByte(0x004D27D6+1,0xB7);
SetByte(0x004D43E4+1,0xB7);
SetByte(0x004D4485+1,0xB7);
SetByte(0x004D44FF+1,0xB7);
SetByte(0x004D4FCB+1,0xB7);
SetByte(0x004D62FF+1,0xB7);
SetByte(0x004D633A+1,0xB7);
SetByte(0x004D7536+1,0xB7);
SetByte(0x004D75C9+1,0xB7);
SetByte(0x004E8F32+1,0xB7);
SetByte(0x004E8FC4+1,0xB7);
SetByte(0x004EE5D2+1,0xB7);
SetByte(0x004EEF9C+1,0xB7);
SetByte(0x004EF1C3+1,0xB7);
SetByte(0x004F0A8E+1,0xB7);
SetByte(0x004F9680+1,0xB7);
SetByte(0x00502B48+1,0xB7);
SetByte(0x00506051+1,0xB7);
SetByte(0x0051CB84+1,0xB7);
SetByte(0x0053AEFB+1,0xB7);
SetByte(0x0053B1E0+1,0xB7);
SetByte(0x0053B440+1,0xB7);
SetByte(0x0053CB58+1,0xB7);
SetByte(0x0053D760+1,0xB7);
SetByte(0x0053D90B+1,0xB7);
SetByte(0x00547BA7+1,0xB7);
SetByte(0x005650B7+1,0xB7);
SetByte(0x0058E7C9+1,0xB7);
SetByte(0x0058EA18+1,0xB7);
SetByte(0x0058ECB7+1,0xB7);
SetByte(0x005D473C+1,0xB7);
//
SetByte(0x0045680D+1,0xB7);
SetByte(0x0045CC3A+1,0xB7);
SetByte(0x004CF795+1,0xB7);
SetByte(0x004CFABA+1,0xB7);
SetByte(0x004CFD48+1,0xB7);
SetByte(0x004CFDB0+1,0xB7);
SetByte(0x004CFE19+1,0xB7);
SetByte(0x004CFE6E+1,0xB7);
SetByte(0x004D6315+1,0xB7);
SetByte(0x004D6350+1,0xB7);
SetByte(0x004D7516+1,0xB7);
SetByte(0x004D75A9+1,0xB7);
SetByte(0x004D79AC+1,0xB7);
SetByte(0x004D79E8+1,0xB7);
SetByte(0x004D7A1A+1,0xB7);
SetByte(0x004D7A56+1,0xB7);
SetByte(0x004D7A8E+1,0xB7);
SetByte(0x004D7ABD+1,0xB7);
SetByte(0x004D7B07+1,0xB7);
SetByte(0x004D7B3B+1,0xB7);
SetByte(0x004D7B6F+1,0xB7);
SetByte(0x004D7BA6+1,0xB7);
SetByte(0x004D7BDA+1,0xB7);
SetByte(0x004D7C0F+1,0xB7);
SetByte(0x004DB029+1,0xB7);
SetByte(0x004E4AF6+1,0xB7);
SetByte(0x004E8F4B+1,0xB7);
SetByte(0x004E8FAE+1,0xB7);
SetByte(0x004EE59C+1,0xB7);
SetByte(0x004EE63E+1,0xB7);
SetByte(0x004EEFE1+1,0xB7);
SetByte(0x004EF1D9+1,0xB7);
SetByte(0x004F0AA7+1,0xB7);
SetByte(0x004F279C+1,0xB7);
SetByte(0x004F27D8+1,0xB7);
SetByte(0x004F280A+1,0xB7);
SetByte(0x004F2846+1,0xB7);
SetByte(0x004F287E+1,0xB7);
SetByte(0x004F28AD+1,0xB7);
SetByte(0x004F28F7+1,0xB7);
SetByte(0x004F292B+1,0xB7);
SetByte(0x004F295F+1,0xB7);
SetByte(0x004F2996+1,0xB7);
SetByte(0x004F29CA+1,0xB7);
SetByte(0x004F29FF+1,0xB7);
SetByte(0x004F96A5+1,0xB7);
SetByte(0x004FAA86+1,0xB7);
SetByte(0x00502B7B+1,0xB7);
SetByte(0x00506046+1,0xB7);
SetByte(0x00502B7B+1,0xB7);
SetByte(0x00506046+1,0xB7);
SetByte(0x0051CBBC+1,0xB7);
SetByte(0x0053AF05+1,0xB7);
SetByte(0x0053B1EA+1,0xB7);
SetByte(0x0053B44A+1,0xB7);
SetByte(0x0053CB0F+1,0xB7);
SetByte(0x0053D78C+1,0xB7);
SetByte(0x0053D8CD+1,0xB7);
SetByte(0x00547BEF+1,0xB7);
SetByte(0x005650A0+1,0xB7);
SetByte(0x0058E7AE+1,0xB7);
SetByte(0x0058E9FD+1,0xB7);
SetByte(0x0058EC9C+1,0xB7);
SetByte(0x005D4724+1,0xB7);
//
SetByte(0x004CF7AE+1,0xB7);
SetByte(0x004CFD5C+1,0xB7);
SetByte(0x004CFDC4+1,0xB7);
SetByte(0x004CFE2D+1,0xB7);
SetByte(0x004CFE82+1,0xB7);
SetByte(0x004DAD53+1,0xB7);
SetByte(0x004E8F64+1,0xB7);
SetByte(0x004E9031+1,0xB7);
SetByte(0x004EE674+1,0xB7);
SetByte(0x004EF0D9+1,0xB7);
SetByte(0x004EF1F1+1,0xB7);
SetByte(0x004F0AC0+1,0xB7);
SetByte(0x004F8142+1,0xB7);
SetByte(0x004FB3F1+1,0xB7);
SetByte(0x00502BAD+1,0xB7);
SetByte(0x00504249+1,0xB7);
SetByte(0x0050603B+1,0xB7);
SetByte(0x0051CC2B+1,0xB7);
SetByte(0x0053AF11+1,0xB7);
SetByte(0x0053B1F6+1,0xB7);
SetByte(0x0053B456+1,0xB7);
SetByte(0x0053CAC6+1,0xB7);
SetByte(0x0053D7B5+1,0xB7);
SetByte(0x0053D88C+1,0xB7);
SetByte(0x0053E628+1,0xB7);
SetByte(0x0053E644+1,0xB7);
SetByte(0x0053E660+1,0xB7);
SetByte(0x0053E67C+1,0xB7);
SetByte(0x00547C37+1,0xB7); 
SetByte(0x00565089+1,0xB7);
SetByte(0x0058E793+1,0xB7);
SetByte(0x0058E9E2+1,0xB7);
SetByte(0x0058EC81+1,0xB7); 
SetByte(0x005D470C+1,0xB7);
//
SetByte(0x004567D9+1,0xB7);
SetByte(0x004CF7C7+1,0xB7);
SetByte(0x004CFD70+1,0xB7);
SetByte(0x004CFDD8+1,0xB7);
SetByte(0x004CFE41+1,0xB7);
SetByte(0x004CFE96+1,0xB7);
SetByte(0x004D0BE5+1,0xB7);
SetByte(0x004D0CD0+1,0xB7);
SetByte(0x004D0D37+1,0xB7);
SetByte(0x004D0ED1+1,0xB7);
SetByte(0x004D0F10+1,0xB7);
SetByte(0x004D0F8F+1,0xB7);
SetByte(0x004D0FD0+1,0xB7);
SetByte(0x004D10BD+1,0xB7);
SetByte(0x004D10FC+1,0xB7);
SetByte(0x004D1170+1,0xB7);
SetByte(0x004D118C+1,0xB7);
SetByte(0x004D11A7+1,0xB7);
SetByte(0x004D11F5+1,0xB7);
SetByte(0x004D1210+1,0xB7);
SetByte(0x004D122B+1,0xB7);
SetByte(0x004D133B+1,0xB7);
SetByte(0x004D137A+1,0xB7);
SetByte(0x004D13EE+1,0xB7);
SetByte(0x004D140A+1,0xB7);
SetByte(0x004D1425+1,0xB7);
SetByte(0x004D1473+1,0xB7);
SetByte(0x004D148E+1,0xB7);
SetByte(0x004D14A9+1,0xB7);
SetByte(0x004D17DF+1,0xB7);
SetByte(0x004D1818+1,0xB7);
SetByte(0x004D18BC+1,0xB7);
SetByte(0x004D44A5+1,0xB7);
SetByte(0x004D451F+1,0xB7);
SetByte(0x004D5B70+1,0xB7);
SetByte(0x004D5BA7+1,0xB7);
SetByte(0x004D5D17+1,0xB7);
SetByte(0x004D5D4A+1,0xB7);
SetByte(0x004DAD73+1,0xB7);
SetByte(0x004DAD9D+1,0xB7);
SetByte(0x004DB049+1,0xB7);
SetByte(0x004DB06E+1,0xB7);
SetByte(0x004DB218+1,0xB7);
SetByte(0x004DB519+1,0xB7);
SetByte(0x004DC333+1,0xB7);
SetByte(0x004DC477+1,0xB7);
SetByte(0x004DFA4F+1,0xB7);
SetByte(0x004DFA72+1,0xB7);
SetByte(0x004E430B+1,0xB7);
SetByte(0x004E4323+1,0xB7);
SetByte(0x004E44BD+1,0xB7);
SetByte(0x004E44D5+1,0xB7);
SetByte(0x004E4ABB+1,0xB7);
SetByte(0x004E4B10+1,0xB7);
SetByte(0x004E4D7C+1,0xB7);
SetByte(0x004E4DB5+1,0xB7);
SetByte(0x004E4E0C+1,0xB7);
SetByte(0x004E5AFE+1,0xB7);
SetByte(0x004E5B16+1,0xB7);
SetByte(0x004E5B2B+1,0xB7);
SetByte(0x004E6F71+1,0xB7);
SetByte(0x004E70BF+1,0xB7);
SetByte(0x004E7229+1,0xB7);
SetByte(0x004E8F7D+1,0xB7);
SetByte(0x004E901B+1,0xB7);
SetByte(0x004EE608+1,0xB7);
SetByte(0x004EF026+1,0xB7);
SetByte(0x004EF209+1,0xB7);
SetByte(0x004F0AD9+1,0xB7);
SetByte(0x004F8214+1,0xB7);
SetByte(0x004FA007+1,0xB7);
SetByte(0x004FAAA6+1,0xB7);
SetByte(0x004FAB01+1,0xB7);
SetByte(0x004FAC94+1,0xB7);
SetByte(0x004FAE11+1,0xB7);
SetByte(0x004FB411+1,0xB7);
SetByte(0x004FB43E+1,0xB7);
SetByte(0x004FCF73+1,0xB7);
SetByte(0x004FD2A7+1,0xB7);
SetByte(0x00502BDF+1,0xB7);
SetByte(0x005042F3+1,0xB7);
SetByte(0x00506030+1,0xB7);
SetByte(0x0051CC55+1,0xB7);
SetByte(0x00535B4D+1,0xB7);
SetByte(0x00536074+1,0xB7);
SetByte(0x005366A3+1,0xB7);
SetByte(0x0053AF1D+1,0xB7);
SetByte(0x0053B202+1,0xB7);
SetByte(0x0053B462+1,0xB7);
SetByte(0x0053CA7D+1,0xB7);
SetByte(0x0053D7DE+1,0xB7);
SetByte(0x0053D84B+1,0xB7);
SetByte(0x00547C7C+1,0xB7);
SetByte(0x00565072+1,0xB7);
SetByte(0x0058E778+1,0xB7);
SetByte(0x0058E9C7+1,0xB7);
SetByte(0x0058EC66+1,0xB7);
SetByte(0x005D46F4+1,0xB7);
}


	//With this we can fix all visual bugs in game =) I think :D
	//Hook gObjViewportPatchExecute
/*	BYTE ViewPortPatch[] = { 0xFF, 0x75, 0xF8, 0xFF, 0x15, 0x50, 0xB0, 0x71, 0x00, 0x5F, 0x5E, 0x5B, 0x8B, 0xE5, 0x5D, 0xC3 };
	memcpy((int*)0x00527237,ViewPortPatch,sizeof(ViewPortPatch));
		*(unsigned int*)0x0071B050  = (unsigned int)gObjViewportPatchExecute;
		*/
	//Hook JGPGetCharInfoEx
	BYTE CharWingsEx1[] = { 0x0F, 0x8D, 0xA3, 0x1D };
	BYTE CharWingsEx2[] = { 0xD5, 0x1D, 0x00, 0x00 };
	BYTE CharWingsEx3[] = { 0xE9, 0xA5, 0x1E, 0x00 };
	BYTE CharWingsEx[] = {	0x8D, 0xBD, 0xEC, 0xFE, 0xFF, 0xFF, 0x57, 0xFF, 0x75, 0x08, 0xFF, 0xB5, 0x94, 0xFE, 0xFF,
		    0xFF, 0xFF, 0x15, 0x00, 0xB2, 0x71, 0x00, 0xE9, 0x37, 0xE2, 0xFF, 0xFF, 0x8A, 0x8D, 0xE8,
		    0xFE, 0xFF, 0xFF, 0x88, 0x8D, 0xD5, 0xFE, 0xFF, 0xFF, 0x6A, 0x07, 0x8D, 0x95, 0xD4, 0xFE,
		    0xFF, 0xFF, 0x52, 0x8D, 0x85, 0xEC, 0xFE, 0xFF, 0xFF, 0x50, 0xE8, 0x3C, 0xA1, 0x1E, 0x00,
		    0x83, 0xC4, 0x0C, 0x8B, 0x8D, 0xE8, 0xFE, 0xFF, 0xFF, 0x51, 0x8D, 0x95, 0xEC, 0xFE, 0xFF,
		    0xFF, 0x52, 0x8B, 0x85, 0xE0, 0xFE, 0xFF, 0xFF, 0x50, 0xE8, 0xDE, 0x86, 0xFD, 0xFF, 0x83,
		    0xC4, 0x0C, 0x5F, 0x5E, 0x5B, 0x8B, 0xE5, 0x5D, 0xC3 };

	memcpy((int*)0x0042CE88,CharWingsEx,sizeof(CharWingsEx));
	memcpy((int*)0x0042B0FA,CharWingsEx1,sizeof(CharWingsEx1));
	memcpy((int*)0x0042B0CA,CharWingsEx2,sizeof(CharWingsEx1));
	memcpy((int*)0x0042B032,CharWingsEx3,sizeof(CharWingsEx1));
		*(unsigned int*)0x0071B200  = (unsigned int)JGPGetCharInfoEx;

	//Fix Item Level Max to +15
	BYTE FixItemLevelMax1[] = { 0x83, 0xFA, 0x0F };
	memcpy((int*)0x0042F290,FixItemLevelMax1,sizeof(FixItemLevelMax1));

	BYTE FixItemLevelMax2[] = { 0x83, 0xF9, 0x0F };
	memcpy((int*)0x00501EE2,FixItemLevelMax2,sizeof(FixItemLevelMax2));

	BYTE FixItemLevelMax3[] = { 0x83, 0x7D, 0xFC, 0x0F};
	memcpy((int*)0x00526290,FixItemLevelMax3,sizeof(FixItemLevelMax3));

	BYTE FixItemLevelMax4[] = { 0x83, 0x7D, 0x08, 0x0F};
	memcpy((int*)0x00526329,FixItemLevelMax4,sizeof(FixItemLevelMax4));

	BYTE DurabFixBetaHook[] = { 0xFF, 0x25, 0x00, 0xB3, 0x71, 0x00, 0x90, 0x90, 0x90, 0x90 };
	memcpy((int*)0x00558C55,DurabFixBetaHook,sizeof(DurabFixBetaHook));
		*(unsigned int*)0x0071B300  = (unsigned int)DurabFixBeta;
	
	BYTE LevelSmallConvertHook[] = { 0xFF, 0x25, 0x00, 0xB4, 0x71, 0x00, 0x90, 0x90, 0x90, 0x90 };
	memcpy((int*)0x0052629A,LevelSmallConvertHook,sizeof(LevelSmallConvertHook));
		*(unsigned int*)0x0071B400  = (unsigned int)LevelSmallConvertFix;
	
	BYTE LevelSmallConvertHook1[] = { 0xFF, 0x25, 0x50, 0xB4, 0x71, 0x00, 0x90, 0x90, 0x90, 0x90 };
	memcpy((int*)0x00526333,LevelSmallConvertHook1,sizeof(LevelSmallConvertHook1));
		*(unsigned int*)0x0071B450  = (unsigned int)LevelSmallConvertFix1;



//Checksum
BOOL CheckSum = GetPrivateProfileInt("Server", "CheckSumMain",0,"..//OptionsData//Options.ini");
if (CheckSum==TRUE)
{
	//"error-L1 : [%s][%s] CheckSum-Exe error "
	SetByte(0x438D3A,0x74);
}

#endif
}

BOOL FixPartyZen = GetPrivateProfileInt("GameServer","PartyZen_Fix",1,FixFile);

bool PartyZenBugFix ()
{
	if (FixPartyZen==TRUE)
	{
#ifdef GameServer90
		BYTE cFixPartyZen[31] = {0x8B,0x4D,0xE4,0x8B,0x55,0x0C,0x03,0xC9,0x03,0xC9,
		0x03,0xC9,0x03,0xC9,0x81,0xC1,0x00,0x24,0x00,0x00, 0x89,
		0x8A,0xD8,0x00,0x00,0x00,0xE9,0x83,0xFC,0xFF,0xFF} ;
		memcpy((int*)0x005174E7,cFixPartyZen,sizeof(cFixPartyZen));

		BYTE cFixPartyZen2[12] = {0xE9,0x65,0x03,0x00,0x00,0x90,0x90,0x90,0x90,0x90 ,0x90,0x90};
		memcpy((int*)0x0051717D,cFixPartyZen2,sizeof(cFixPartyZen2));


#else if
		
		/*
		//GSCS 64C4CC
		005296D0     8B4D 0C        MOV ECX,DWORD PTR SS:[EBP+C]
		005296D3     33C0           XOR EAX,EAX
		005296D5     8A41 68        MOV AL,BYTE PTR DS:[ECX+68]
		005296D8     83F8 02        CMP EAX,2
		005296DB     74 05          JE SHORT GameServ.005296E2
		005296DD     83F8 03        CMP EAX,3
		005296E0     75 20          JNZ SHORT GameServ.00529702
		005296E2     8B91 D8000000  MOV EDX,DWORD PTR DS:[ECX+D8]
		005296E8     8955 F8        MOV DWORD PTR SS:[EBP-8],EDX
		005296EB     DB45 F8        FILD DWORD PTR SS:[EBP-8]
		005296EE     D80D C0128000  FMUL DWORD PTR DS:[8012C0]
		005296F4     E8 D32D1200    CALL GameServ.0064C4CC
		005296F9     8B4D 0C        MOV ECX,DWORD PTR SS:[EBP+C]
		005296FC     8981 D8000000  MOV DWORD PTR DS:[ECX+D8],EAX
		00529702     5F             POP EDI
		00529703     5E             POP ESI
		00529704     5B             POP EBX
		00529705     8BE5           MOV ESP,EBP
		00529707     5D             POP EBP
		00529708     C3             RETN
		*/
		unsigned char PartyFix[] = {
		0x8B,0x4D,0x0C,0x33,0xC0,0x8A,0x410x68,0x83,0xF8,0x02,0x74,0x05,0x83,0xF8,0x03,0x75,0x20,0x8B,0x91,0xD8, 
		0x00,0x00,0x00,0x89,0x55,0xF8,0xDB,0x45,0xF8,0xD8,0x0D,0xC0,0x12,0x80,0x00,0xE8,0xD3,0x2D,0x12,0x00,0x8B, 
		0x4D,0x0C,0x89,0x81,0xD8,0x00,0x00,0x00,0x5F,0x5E,0x5B,0x8B,0xE5,0x5D,0xC3 };
		
		memcpy ( (int *) 0x005296D0 , PartyFix , sizeof(PartyFix) );


#endif

	}
	return 1;

}
