#include "StdAfx.h"
#include "MoveReq.h"

//Structures
MOVEREQ MoveReqInfo[255]; 
int MoveReqCount;

//Move Req
bool MoveReqLoad(char *FileName)
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[255] = {0};
	int MoveReqCount = 1;

	fp = fopen(FileName,"r");

	if(!fp)
	{
		MessageBoxA(NULL, "MoveReq Failed!", "Error!", MB_OK);
		::ExitProcess(0);
	}
	
	rewind(fp);
	int leestatus=-1;
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;

		int n[4];

		sscanf(sLineTxt, "%d %*s %*s %d %d %d", &n[0], &n[1], &n[2], &n[3]);

		MoveReqInfo[MoveReqCount].Index	= n[0];
		MoveReqInfo[MoveReqCount].Zen	= n[1];
		MoveReqInfo[MoveReqCount].Level	= n[2];
		MoveReqInfo[MoveReqCount].Gate	= n[3];
		MoveReqCount++;
	}

	rewind(fp);
	fclose(fp);
	
	return TRUE;
}