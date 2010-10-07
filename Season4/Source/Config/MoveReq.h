#include <windows.h>

typedef struct MoveReq
{
	int Index;
	int Zen;
	int Level;
	int Gate;
}MOVEREQ;

//Structures
extern MOVEREQ MoveReqInfo[255]; 
extern int MoveReqCount;

//Defines
bool MoveReqLoad(char *FileName);