/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#ifndef USER_H
	#define USER_H
//#include <windows.h>
//#include "GameServer.h"

#include <vector>
#include "stdafx.h"
#include "items.h"

#define gObjSize 0x2228
#define MIN_PLAYERID 8000
#define MAX_PLAYERID 9000
#define MIN_MONSTERID 0
#define OBJECT_BASE	(*(char**)0x7A5502C)
#define OBJECT_SIZE	0x2228
#define gObjBaseAddr (*(char**)0x7A5502C)
//#define CLASSTYPE_ADR_ALLOW	0x5030DE
//#define CLASSTYPE_ADR_DENY	0x5030E0
#define gObj_INV	0xE7C

#define OBJECT_POINTER(aIndex) ((aIndex * OBJECT_SIZE) + OBJECT_BASE)
#define OBJECT_TABINDEX(lpObj) ((lpObj - OBJECT_BASE) / OBJECT_SIZE)

#define CS_SET_BOOTS3(x) ( ((x) & 0x0F ) << 4 )





struct PMSG_DUEL_FINISH // 0x0C
{
	BYTE hc;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
	BYTE szWinner[10];
	BYTE szLooser[10];
};

struct PMSG_DUEL_SCORE // 0x04
{
	BYTE hc;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
	BYTE NumberH1;	
	BYTE NumberL1;	
	BYTE NumberH2;	
	BYTE NumberL2;	
	BYTE btDuelScore1;	
	BYTE btDuelScore2;	
};


struct ComboSkillData 
{

  /*<thisrel this+0x0>*/ /*|0x4|*/ unsigned long dwTime;
  /*<thisrel this+0x4>*/ /*|0x6|*/ unsigned short Skill[3];
  /*<thisrel this+0xc>*/ /*|0x4|*/ int ProgressIndex;

//  void __thiscall ComboSkillData::Init();

};
// <size 0x10>


class CObjBaseAttack 
{
public:

    CObjBaseAttack(){};
  //int __thiscall CObjBaseAttack::DecreaseArrow(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj);
  //int __thiscall CObjBaseAttack::CheckAttackArea(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj, /*<regrel ebp+0xc>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpTargetObj);
  //int __thiscall CObjBaseAttack::PkCheck(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj, /*<regrel ebp+0xc>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpTargetObj);
  //int __thiscall CObjBaseAttack::ResistanceCheck(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj, /*<regrel ebp+0xc>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpTargetObj, /*<regrel ebp+0x10>*/ /*|0x4|*/ int skill);
  //int __thiscall CObjBaseAttack::MissCheckPvP(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj, /*<regrel ebp+0xc>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpTargetObj, /*<regrel ebp+0x10>*/ /*|0x4|*/ int skill, /*<regrel ebp+0x14>*/ /*|0x4|*/ int skillSuccess, /*<regrel ebp+0x18>*/ /*|0x4|*/ int magicsend, /*<regrel ebp+0x1c>*/ /*|0x4|*/ int& bAllMiss);
  //int __thiscall CObjBaseAttack::GetTargetDefense(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj, /*<regrel ebp+0xc>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpTargetObj, /*<regrel ebp+0x10>*/ /*|0x4|*/ unsigned char& MsgDamage);
  //int __thiscall CObjBaseAttack::GetPartyMemberCount(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj);

  // virtual functions ------------------------------
    virtual ~CObjBaseAttack(){};
//  virtual /*<vtableoff 0x4>*/ int __thiscall CObjBaseAttack::MissCheck(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj, /*<regrel ebp+0xc>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpTargetObj, /*<regrel ebp+0x10>*/ /*|0x4|*/ int skill, /*<regrel ebp+0x14>*/ /*|0x4|*/ int skillSuccess, /*<regrel ebp+0x18>*/ /*|0x4|*/ int magicsend, /*<regrel ebp+0x1c>*/ /*|0x4|*/ int& bAllMiss);
};
// <size 0x4>




struct VIEWPORT_STRUCT 
{

  /*<thisrel this+0x0>*/ /*|0x1|*/ char state;
  /*<thisrel this+0x2>*/ /*|0x2|*/ short number;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char type;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short index;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int dis;

};
// <size 0xc>

struct VIEWPORT_PLAYER_STRUCT 
{

  /*<thisrel this+0x0>*/ /*|0x1|*/ char state;
  /*<thisrel this+0x2>*/ /*|0x2|*/ short number;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char type;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short index;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int dis;
};
// <size 0xc>


struct HITDAMAGE_STRUCT 
{
  /*<thisrel this+0x0>*/ /*|0x2|*/ short number;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int HitDamage;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long LastHitTime;

};
// <size 0xc>

struct tagInterfaceState 
{

  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long use:2;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long state:4;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long type:0xA;

};
// <size 0x4>


struct tagActionState 
{
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Rest:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Attack:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Move:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Escape:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Emotion:4;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long EmotionCount:8;

};
// <size 0x4>



class TDurMagicKeyChecker 
{
public:
  /*<thisrel this+0x0>*/ /*|0xf0|*/ unsigned long m_dwDurationTime[60];
  /*<thisrel this+0xf0>*/ /*|0x3c|*/ unsigned char m_btValidCount[60];


  //int __thiscall TDurMagicKeyChecker::IsValidDurationTime(/*<regrel ebp+0x8>*/ /*|0x1|*/ unsigned char btMagicKey);
  //int __thiscall TDurMagicKeyChecker::IsValidCount(/*<regrel ebp+0x8>*/ /*|0x1|*/ unsigned char btMagicKey);
  //void __thiscall TDurMagicKeyChecker::SetDurationTime(/*<regrel ebp+0x8>*/ /*|0x1|*/ unsigned char btMagicKey, /*<regrel ebp+0xc>*/ /*|0x4|*/ unsigned long dwCurrentTickCount);
  //unsigned char __thiscall DecValidCount(unsigned char);
  //int __thiscall TDurMagicKeyChecker::GetValidDurationTime(/*<regrel ebp+0x8>*/ /*|0x1|*/ unsigned char btMagicKey);
  //int __thiscall TDurMagicKeyChecker::GetValidCount(/*<regrel ebp+0x8>*/ /*|0x1|*/ unsigned char btMagicKey);

};
// <size 0x12c>



class CSkillDelay 
{
public:
  /*<thisrel this+0x4>*/ /*|0x400|*/ unsigned long LastSkillUseTime[600];

  //void __thiscall CSkillDelay(class CSkillDelay&);
  CSkillDelay(){};
  //void __thiscall CSkillDelay::Init();
  //int __thiscall CSkillDelay::Check(/*<regrel ebp+0x8>*/ /*|0x1|*/ unsigned char skill);
  //class CSkillDelay& __thiscall operator=(class CSkillDelay&);
  //void __thiscall __local_vftable_ctor_closure();

  //// virtual functions ------------------------------
  virtual ~CSkillDelay(){};
  //virtual /*<vtableoff 0x0>*/ void* __thiscall __vecDelDtor(unsigned int);
};
// <size 0x404>


struct ITEMOPTION_FOR380ITEM_EFFECT 
{

  /*<thisrel this+0x0>*/ /*|0x2|*/ short OpAddAttackSuccessRatePVP;
  /*<thisrel this+0x2>*/ /*|0x2|*/ short OpAddDamage;
  /*<thisrel this+0x4>*/ /*|0x2|*/ short OpAddDefenseSuccessRatePvP;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short OpAddDefense;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short OpAddMaxHP;
  /*<thisrel this+0xa>*/ /*|0x2|*/ short OpAddMaxSD;
  /*<thisrel this+0xc>*/ /*|0x2|*/ short OpRefillOn;
  /*<thisrel this+0xe>*/ /*|0x2|*/ short OpAddRefillSD;

};
// <size 0x10>



struct JEWELOFHARMONY_ITEM_EFFECT 
{
  /*<thisrel this+0x0>*/ /*|0x2|*/ short HJOpAddMinAttackDamage;
  /*<thisrel this+0x2>*/ /*|0x2|*/ short HJOpAddMaxAttackDamage;
  /*<thisrel this+0x4>*/ /*|0x2|*/ short HJOpRequireStr;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short HJOpRequireDex;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short HJOpAddAttackDamage;
  /*<thisrel this+0xa>*/ /*|0x2|*/ short HJOpAddCriticalDamage;
  /*<thisrel this+0xc>*/ /*|0x2|*/ short HJOpAddSkillAttack;
  /*<thisrel this+0xe>*/ /*|0x2|*/ short HJOpAddAttackSuccessRatePVP;
  /*<thisrel this+0x10>*/ /*|0x2|*/ short HJOpDecreaseSDRate;
  /*<thisrel this+0x12>*/ /*|0x2|*/ short HJOpAddIgnoreSDRate;
  /*<thisrel this+0x14>*/ /*|0x2|*/ short HJOpAddMagicPower;
  /*<thisrel this+0x16>*/ /*|0x2|*/ short HJOpAddDefense;
  /*<thisrel this+0x18>*/ /*|0x2|*/ short HJOpAddMaxAG;
  /*<thisrel this+0x1a>*/ /*|0x2|*/ short HJOpAddMaxHP;
  /*<thisrel this+0x1c>*/ /*|0x2|*/ short HJOpAddRefillHP;
  /*<thisrel this+0x1e>*/ /*|0x2|*/ short HJOpAddRefillMP;
  /*<thisrel this+0x20>*/ /*|0x2|*/ short HJOpAddDefenseSuccessRatePvP;
  /*<thisrel this+0x22>*/ /*|0x2|*/ short HJOpAddDamageDecrease;
  /*<thisrel this+0x24>*/ /*|0x2|*/ short HJOpAddSDRate;
};
// <size 0x26>



class TMonsterAIAgroInfo 
{

  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iUserIndex;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iAgroValue;


  //void __thiscall TMonsterAIAgroInfo::TMonsterAIAgroInfo();
  //void __thiscall TMonsterAIAgroInfo::Reset();
  //int __thiscall TMonsterAIAgroInfo::GetUserIndex();
  //int __thiscall TMonsterAIAgroInfo::GetAgroValue();
  //void __thiscall TMonsterAIAgroInfo::SetAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iTargetIndex, /*<regrel ebp+0xc>*/ /*|0x4|*/ int iValue);
  //int __thiscall TMonsterAIAgroInfo::IncAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iIncValue);
  //int __thiscall TMonsterAIAgroInfo::DecAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iDecValue);

};
// <size 0x8>



class TMonsterAIAgro 
{
public:
  /*<thisrel this+0x4>*/ /*|0x320|*/ class TMonsterAIAgroInfo m_Agro[100];

  //void __thiscall TMonsterAIAgro(class TMonsterAIAgro&);
  TMonsterAIAgro(){};
  //void __thiscall TMonsterAIAgro::ResetAll();
  //int __thiscall TMonsterAIAgro::SetAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iTargetIndex, /*<regrel ebp+0xc>*/ /*|0x4|*/ int iValue);
  //int __thiscall TMonsterAIAgro::DelAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iTargetIndex);
  //int __thiscall TMonsterAIAgro::GetAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iTargetIndex);
  //int __thiscall TMonsterAIAgro::IncAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iTargetIndex, /*<regrel ebp+0xc>*/ /*|0x4|*/ int iIncValue);
  //int __thiscall TMonsterAIAgro::DecAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iTargetIndex, /*<regrel ebp+0xc>*/ /*|0x4|*/ int iDecValue);
  //void __thiscall TMonsterAIAgro::DecAllAgro(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iDecValue);
  //int __thiscall TMonsterAIAgro::GetMaxAgroUserIndex(/*<regrel ebp+0x8>*/ /*|0x4|*/ int iMonsterIndex);
  //class TMonsterAIAgro& __thiscall operator=(class TMonsterAIAgro&);
  //void __thiscall __local_vftable_ctor_closure();

  virtual ~TMonsterAIAgro(){};
  //virtual /*<vtableoff 0x0>*/ void* __thiscall __vecDelDtor(unsigned int);
};
// <size 0x324>



class TMonsterAIMovePathInfo 
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iType;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iMapNumber;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int m_iPathX;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_iPathY;

  TMonsterAIMovePathInfo(){};
};
// <size 0x10>



class TMonsterAIMovePath 
{
public:
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_bDataLoad;
  /*<thisrel this+0x8>*/ /*|0x12c0|*/ class TMonsterAIMovePathInfo m_MovePathInfo[300];
  /*<thisrel this+0x12c8>*/ /*|0x4|*/ int m_iMovePathSpotCount;

  TMonsterAIMovePath(){};

  virtual ~TMonsterAIMovePath(){};
};
// <size 0x12cc>


class TMonsterSkillElementInfo 
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iSkillElementDefense;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iSkillElementDefenseTime;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int m_iSkillElementAttack;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_iSkillElementAttackTime;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int m_iSkillElementAutoHP;
  /*<thisrel this+0x14>*/ /*|0x4|*/ int m_iSkillElementAutoHPCycle;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_iSkillElementAutoHPTime;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_iSkillElementAutoMP;
  /*<thisrel this+0x20>*/ /*|0x4|*/ int m_iSkillElementAutoMPCycle;
  /*<thisrel this+0x24>*/ /*|0x4|*/ int m_iSkillElementAutoMPTime;
  /*<thisrel this+0x28>*/ /*|0x4|*/ int m_iSkillElementAutoAG;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ int m_iSkillElementAutoAGCycle;
  /*<thisrel this+0x30>*/ /*|0x4|*/ int m_iSkillElementAutoAGTime;
  /*<thisrel this+0x34>*/ /*|0x4|*/ int m_iSkillElementImmuneNumber;
  /*<thisrel this+0x38>*/ /*|0x4|*/ int m_iSkillElementImmuneTime;
  /*<thisrel this+0x3c>*/ /*|0x4|*/ int m_iSkillElementResistNumber;
  /*<thisrel this+0x40>*/ /*|0x4|*/ int m_iSkillElementResistTime;
  /*<thisrel this+0x44>*/ /*|0x4|*/ int m_iSkillElementModifyStat;
  /*<thisrel this+0x48>*/ /*|0x4|*/ int m_iSkillElementModifyStatType;
  /*<thisrel this+0x4c>*/ /*|0x4|*/ int m_iSkillElementModifyStatTime;


  //// static functions -------------------------------
  //static void __cdecl TMonsterSkillElementInfo::CheckSkillElementInfoProc(/*<regrel ebp+0x8>*/ /*|0x4|*/ struct OBJECTSTRUCT* lpObj);

  //// non-virtual functions --------------------------
  TMonsterSkillElementInfo(){};
  //void __thiscall TMonsterSkillElementInfo::Reset();
  //void __thiscall TMonsterSkillElementInfo::ResetDefense();
  //void __thiscall TMonsterSkillElementInfo::ResetAttack();
  //void __thiscall TMonsterSkillElementInfo::ResetAutoHP();
  //void __thiscall TMonsterSkillElementInfo::ResetAutoMP();
  //void __thiscall TMonsterSkillElementInfo::ResetAutoAG();
  //void __thiscall TMonsterSkillElementInfo::ResetImmune();
  //void __thiscall TMonsterSkillElementInfo::ResetResist();
  //void __thiscall TMonsterSkillElementInfo::ResetModifyStat();
  //int __thiscall TMonsterSkillElementInfo::CheckDefenseTime();
  //int __thiscall TMonsterSkillElementInfo::CheckAttackTime();
  //int __thiscall TMonsterSkillElementInfo::CheckAutoHPTime();
  //int __thiscall TMonsterSkillElementInfo::CheckAutoMPTime();
  //int __thiscall TMonsterSkillElementInfo::CheckAutoAGTime();
  //int __thiscall TMonsterSkillElementInfo::CheckImmuneTime();
  //int __thiscall TMonsterSkillElementInfo::CheckResistTime();
  //int __thiscall TMonsterSkillElementInfo::CheckModifyStatTime();
  //int __thiscall TMonsterSkillElementInfo::DecDefenseTime();
  //int __thiscall TMonsterSkillElementInfo::DecAttackTime();
  //int __thiscall TMonsterSkillElementInfo::DecAutoHPTime();
  //int __thiscall TMonsterSkillElementInfo::DecAutoMPTime();
  //int __thiscall TMonsterSkillElementInfo::DecAutoAGTime();
  //int __thiscall TMonsterSkillElementInfo::DecImmuneTime();
  //int __thiscall TMonsterSkillElementInfo::DecResistTime();
  //int __thiscall TMonsterSkillElementInfo::DecModifyStatTime();

};
// <size 0x50>


// new
struct MONSTERKILLINFO
{
    int MonIndex;
    int KillCount;
};
/////////////////////////

void FireWorksSend(UINT MapNumber, BYTE X, BYTE Y,int Cant);
void FireWorksSendAll(int Cant);
void __stdcall JGPGetCharInfoEx(int Loop, unsigned char *DSPacket, unsigned char *toClientPacket);
void __stdcall gObjViewportPatchExecute(GOBJSTRUCT *lpObj);
void gObjCharacterWingsSetPreview(short ItemType, unsigned char *CharSet);

BOOL __cdecl gObjGameClose_Func(int aIndex);
//extern OBJECTSTRUCT *ObjTab;

#endif //~USER_H 


