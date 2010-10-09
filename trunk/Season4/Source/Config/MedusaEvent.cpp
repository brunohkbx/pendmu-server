//============================================================//
//    Swamp Of Calmness Event Coded By M.E.S       //
//                                                              //
//============================================================//

#include "StdAfx.h"
#include "MedusaEvent.h"
#include "GameServer.h"
#include "Log.h"
#include "User.h"
#include "Utils.h"

int iSwampItemBugCount;
SwampPeace Swamp;
SwampBag g_SwampItemBag[255];
// -------------------------------------------------------------
SwampPeace::SwampPeace()
{
    // ----
}
// -------------------------------------------------------------
SwampPeace::~SwampPeace()
{
    // ----
}
// -------------------------------------------------------------
void SwampPeace::LoadSwampConfig()
{
	char EventFile[] = "..//OptionsData//Events//Event_Medusa.ini";
    Swamp.SwampEnabled                    = GetPrivateProfileInt("SwampOfPeace","SwampOfPeaceEventEnabled",1,EventFile);
    Swamp.SwampMinutes                    = GetPrivateProfileInt("SwampOfPeace","SwampOfPeaceEventDuration",10,EventFile)*60;
    if (Swamp.SwampEnabled == 1)
    {
        Swamp.LoadSwampEventItemBag();
    }
}
// -------------------------------------------------------------
void SwampPeace::LoadSwampEventItemBag()
{
	char SwampEventItemBag[] = "..//Data//EventItemBag99.txt";
    FILE * FilePath;
    char cLineText[255] = {0};
    int  iIndex         = 0;
    int  iNumber[9]     = {0};
    // ----

    fopen_s(&FilePath,SwampEventItemBag,"r");
    // ----
    while(fgets (cLineText , 255 , FilePath) != NULL)
    {
        if(cLineText[0] != '/' && cLineText[1] != '/' && strlen(cLineText) > 3)
        {
            sscanf_s(cLineText , "%d %d %d %d %d %d %d %d %d", &iNumber[0], &iNumber[1], &iNumber[2],&iNumber[3], &iNumber[4], &iNumber[5], &iNumber[6], &iNumber[7], &iNumber[8]);
            // ----
            g_SwampItemBag[iIndex].iType    = iNumber[0];
            g_SwampItemBag[iIndex].iIndex   = iNumber[1];
            g_SwampItemBag[iIndex].iLevel   = iNumber[2];
            g_SwampItemBag[iIndex].iDur        = iNumber[3];
            g_SwampItemBag[iIndex].iLuck    = iNumber[4];
            g_SwampItemBag[iIndex].iSkill   = iNumber[5];
            g_SwampItemBag[iIndex].iOption  = iNumber[6];
            g_SwampItemBag[iIndex].iExc    = iNumber[7];
            g_SwampItemBag[iIndex].iAnc    = iNumber[8];
            // ----
            iSwampItemBugCount++;
            iIndex++;
          }
    }
    // ---
    fclose(FilePath);
}
// -------------------------------------------------------------
void SwampPeace::SwampMonsterManager(int aIndex,int MobIndex)
{
    if (Swamp.SwampEnabled == 1 && Swamp.SwampIsRunning == 1)
    {
        GOBJSTRUCT *gObj = (GOBJSTRUCT*)OBJECT_POINTER(aIndex);
        GOBJSTRUCT *gObjMob = (GOBJSTRUCT*)OBJECT_POINTER(MobIndex);
        // ----
        if (MobIndex == Swamp.SwampBossIndex && Swamp.SwampBossKilled == 0)
        {
            int Random = rand()%iSwampItemBugCount;
            int RewardItem = ((g_SwampItemBag[Random].iType*512)+g_SwampItemBag[Random].iIndex);
            ItemSerialCreateSend(aIndex,gObjMob->MapNumber,gObjMob->X,gObjMob->Y,RewardItem,g_SwampItemBag[Random].iLevel,g_SwampItemBag[Random].iDur,g_SwampItemBag[Random].iLuck,g_SwampItemBag[Random].iSkill,g_SwampItemBag[Random].iOption,aIndex,g_SwampItemBag[Random].iExc,g_SwampItemBag[Random].iAnc);
            Swamp.SwampBossKilled = 1;
        }
    }
}
// -------------------------------------------------------------
void SwampPeace::SwampAddMonster()
{
    int RandomMapSwamp = rand()%4;
    if (RandomMapSwamp == 0)
    {
        Swamp.SwampBossIndex = MonsterAddAndSpawn(561,56,96,167);
    }
    else if (RandomMapSwamp == 1)
    {
        Swamp.SwampBossIndex = MonsterAddAndSpawn(561,56,60,77);
    }
    else if (RandomMapSwamp == 2)
    {
        Swamp.SwampBossIndex = MonsterAddAndSpawn(561,56,140,48);
    }
    else if (RandomMapSwamp == 3)
    {
        Swamp.SwampBossIndex = MonsterAddAndSpawn(561,56,204,114);
    }
    else
    {
        Swamp.SwampBossIndex = MonsterAddAndSpawn(561,56,96,167);
    }
}
// -------------------------------------------------------------
void SwampPeace::SwampOfPeaceStart()
{
    if (Swamp.SwampEnabled == 1 && Swamp.SwampIsRunning == 0)
    {
        Messages.outToAll("[Swamp of Peace] Medusa has corrupted Swamp. Find her!!");
        Swamp.SwampTimer = Swamp.SwampMinutes;
        Swamp.SwampIsRunning = 1;
        Swamp.SwampBossKilled = 0;
        Swamp.SwampAddMonster();
        _beginthread(SwampOfPeaceTimer,0,NULL);
    }
}
// -------------------------------------------------------------
void SwampOfPeaceTimer(void * lpParam)
{
    while (true)
    {
        if (Swamp.SwampTimer == 0)
        {
			//CMessages.outToAll
            Messages.outToAll("[Swamp of Peace] Medusa has taken Swamp");
            gObjDel(Swamp.SwampBossIndex);
            Swamp.SwampIsRunning = 0;
            _endthread();
        }
        if (Swamp.SwampBossKilled == 1)
        {
            Messages.outToAll("[Swamp of Peace] Medusa has been defeated. Peace has returned");
            gObjDel(Swamp.SwampBossIndex);
            Swamp.SwampIsRunning = 0;
            _endthread();
        }
        Swamp.SwampTimer = Swamp.SwampTimer - 1;
        Sleep(1000);
    }
}
// -------------------------------------------------------------