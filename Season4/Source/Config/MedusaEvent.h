//============================================================//
//    Swamp Of Calmness Event Coded By M.E.S       //
//                                                              //
//============================================================//

struct SwampBag
{
    int iType;
    int iIndex;
    int iLevel;
    int iDur;
    int iLuck;
    int iSkill;
    int iOption;
    int iExc;
    int iAnc;
};

class SwampPeace
{
public:
    SwampPeace();
    ~SwampPeace();
    // ----
    void LoadSwampConfig();
    void LoadSwampEventItemBag();
    void SwampMonsterManager(int aIndex,int MobIndex);
    void SwampRewardItem(int aIndex);
    void SwampAddMonster();
    void SwampOfPeaceStart();
    // ----
    int SwampEnabled;
    int SwampIsRunning;
    int SwampMinutes;
    int SwampTimer;
    int SwampBossKilled;
    int SwampBossIndex;
    // ----
}; extern SwampPeace Swamp;

void SwampOfPeaceTimer(void * lpParam);