#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

#define MAX_MOVES 255
#define MAX_GATES 300

struct MOVEINFODATA
{
	int iIndex;
	char szMoveKor[40];
	char szMoveEng[40];
	int iMoney;
	int iLevel;
	int iGate;
};

struct GATEINFODATA
{
	int iIndex;
	int iType;
	int iMapNum;
	int iX1;
	int iY1;
	int iX2;
	int iY2;
	int iTarget;
	int iDir;
	int iLevel;
};

class CMoveSystem
{
public:
void Init();
void LoadFile(char *filename);
void Insert(int iIndex,char *szMoveKor,char *szMoveEng, int iMoney,int iLevel,int iGate);
MOVEINFODATA m_MoveData[MAX_MOVES];

void InitGate();
void LoadGate(char *filename);
void InsertGate(int iIndex,int iType,int iMapNum, int iX1,int iY1,int iX2,int iY2, int iTarget, int iDir,int iLevel);
GATEINFODATA m_GateData[MAX_GATES];

void MoveTeleport(int aIndex,char *szMoveEng);
void Teleport(int aIndex, int MovNum);
}; extern CMoveSystem g_MoveReq;

