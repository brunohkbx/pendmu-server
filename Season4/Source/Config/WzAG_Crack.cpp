// ----------------------------------------------------------
// WzAG			: Webzen Authentication GameServer
// Version		: 0.0.1.1
// Made By	    : Deathway
// Edit By		: Mr.Lai (Syrius DLL SS 4 Full)
// Date			: 2007-07-11 16:42 p.m.
// Description	: Emulate Authentication Server From Korea
// ----------------------------------------------------------

#include "stdafx.h"
#include "windows.h"
#include "winbase.h"
#include "stdio.h"
#include "stdafx.h"



// ----------------------------------------------------------
// WzAG.cpp Global Variables
// ----------------------------------------------------------
HANDLE a;	// Handle (Useless)
int gType;	// Data Number Rquest
HANDLE g_hAllocFile;	// Data Buffer Pointer
unsigned long Bytes;	// DataBufferSize	
HANDLE hFile;	// Handlke To File
HANDLE hGA ;	// Global Allocation pointer

#define MAX_FILE_NAME 48

char szFileName[MAX_FILE_NAME][256];
// ----------------------------------------------------------


#define AUTHKEY0	41
#define AUTHKEY1	35
#define AUTHKEY2	-66
#define AUTHKEY3	0x00	/* Unkonw */
#define AUTHKEY4	-31
#define AUTHKEY5	108
#define AUTHKEY6	-42
#define AUTHKEY7	-82
#define AUTHKEY8	82
#define AUTHKEY9	-112
#define AUTHKEY10	73
#define AUTHKEY11	 -15
#define AUTHKEY12	 -15
#define AUTHKEY13	-69
#define AUTHKEY14	-23
#define AUTHKEY15	-21
#define AUTHKEY16	-77
#define AUTHKEY17	-90
#define AUTHKEY18	-37
#define AUTHKEY19	0x00	/* Unkonw */

unsigned char szGSAuthKey[22]={AUTHKEY0,
							   AUTHKEY1,
							   AUTHKEY2,
							   AUTHKEY3,
							   AUTHKEY4,
							   AUTHKEY5,
							   AUTHKEY6,
							   AUTHKEY7,
							   AUTHKEY8,
							   AUTHKEY9,
							   AUTHKEY10,
							   AUTHKEY11,
							   AUTHKEY12,
							   AUTHKEY13,
							   AUTHKEY14,
							   AUTHKEY15,
							   AUTHKEY16,
							   AUTHKEY17,
							   AUTHKEY18,
							   AUTHKEY19};


void MsgBox(const char *szLog, ...)
{
	char szBuffer[512]="";		// Damns shit, 3 month for decode this damn line - by Deathway
	va_list pArguments;
	va_start(pArguments, szLog);
	vsprintf(szBuffer, szLog, pArguments);
	va_end(pArguments);
	MessageBox(NULL, szBuffer, "Error", MB_OK|MB_APPLMODAL|MB_ICONERROR);
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    hModule = a;
	return TRUE;
}

// ----------------------------------------------------------
// Call back Function Pointer
// ----------------------------------------------------------
typedef void (*callfunc)(int,int);
// ----------------------------------------------------------


extern "C" _declspec(dllexport)HANDLE AGSetInfo(int iCountryCode, unsigned char cPartition, unsigned short iServerCode, char* szServerVersion, char* szServerName, int ServerType, callfunc callbackfunc)
{
	
	char * szLanguage;	// Language

	switch(iCountryCode)	// Switch the Language
	{
		case 0:
			szLanguage="Kor";
			break;
		case 1:
			szLanguage="Eng";
			break;
		case 2:
			szLanguage="Jpn";
			break;
		case 3:
			szLanguage="Chs";
			break;
		case 4:
			szLanguage="Tai";
			break;
		case 5:
			szLanguage="Tha";
			break;
		case 6:
			szLanguage="Phi";
			break;
		case 7:
			szLanguage="Vtm";
			break;
		default:
			MessageBox(NULL, "Language Selected is not Supported\nChange Language in CommonServer.cfg","Error",MB_OK|MB_ICONERROR);
			break;
	}

	BOOL bUseMDrive = GetPrivateProfileInt("SETUP", "MDrive", 0, ".\\WzAG.ini");
	BOOL bIsGSServer = GetPrivateProfileInt("SETUP", "IsCastleSiegeGS", 0, ".\\WzAG.ini");

	char msb[256] = {0};

	if ( bIsGSServer == TRUE )
	{
		GetPrivateProfileString("SETUP", "MonsterSetBaseForGSCS", "MonsterSetBase_CS.txt", msb, 40, ".\\WzAG.ini");
	}

	char szTemp[MAX_FILE_NAME][256]={0};

	if ( bUseMDrive == TRUE )
	{
		for ( int j=0;j<MAX_FILE_NAME ; j++)
		{
			strcpy(szFileName[j], "M:\\");
		}
	
	}
	else
	{
		for ( int j=0;j<MAX_FILE_NAME ; j++)
		{
			strcpy(szFileName[j], "..\\data\\");
		}
	}

	strcat(szFileName[0], "lang\\Kor\\Item(Kor).txt");
	strcat(szFileName[2], "lang\\Kor\\Skill(Kor).txt");
	strcat(szFileName[4], "lang\\Kor\\Quest(Kor).txt");
	strcat(szFileName[7], "Monster.txt");
	strcat(szFileName[8], "Gate.txt");

	if ( bIsGSServer == TRUE )
	{
		strcat(szFileName[9], msb);
	}
	else
	{
		strcat(szFileName[9], "MonsterSetBase.txt");
	}


	strcat(szFileName[11], "Shop0.txt");
	strcat(szFileName[12], "Shop1.txt");
	strcat(szFileName[13], "Shop2.txt");
	strcat(szFileName[14], "Shop3.txt");
	strcat(szFileName[15], "Shop4.txt");
	strcat(szFileName[16], "Shop5.txt");
	strcat(szFileName[17], "Shop6.txt");
	strcat(szFileName[18], "Shop7.txt");
	strcat(szFileName[19], "Shop8.txt");
	strcat(szFileName[20], "Shop9.txt");
	strcat(szFileName[21], "Shop10.txt");
	strcat(szFileName[22], "Shop11.txt");
	strcat(szFileName[23], "Shop12.txt");
	strcat(szFileName[30], "Shop13.txt"); //New
	strcat(szFileName[31], "Shop14.txt");
	strcat(szFileName[32], "Shop15.txt");
	strcat(szFileName[33], "Shop16.txt");
	strcat(szFileName[34], "Shop17.txt");
	//strcat(szFileName[35], "Shop18.txt");
	//strcat(szFileName[36], "Shop19.txt");
	//strcat(szFileName[37], "Shop20.txt");
	
	

	if ( iCountryCode != 0 )
	{
		wsprintf(szTemp[1], "lang\\%s\\Item(%s).txt", szLanguage, szLanguage);
		wsprintf(szTemp[3], "lang\\%s\\Skill(%s).txt", szLanguage, szLanguage);
		wsprintf(szTemp[5], "lang\\%s\\Quest(%s).txt", szLanguage, szLanguage);
		wsprintf(szTemp[6], "lang\\%s\\CheckSum.dat", szLanguage);
		wsprintf(szTemp[24], "lang\\%s\\Movereq(%s).txt", szLanguage, szLanguage);
		//wsprintf(szTemp[24], "..\\OptionsData\\Movereq.txt");
		wsprintf(szTemp[26], "lang\\%s\\ItemSetOption(%s).txt", szLanguage, szLanguage);
		wsprintf(szTemp[28], "lang\\%s\\ItemSetType(%s).txt", szLanguage, szLanguage);
		wsprintf(szTemp[MAX_FILE_NAME-1], "lang\\%s\\commonloc.cfg", szLanguage);

		strcat(szFileName[1], szTemp[1]);
		strcat(szFileName[3], szTemp[3]);
		strcat(szFileName[5], szTemp[5]);
		strcat(szFileName[6], szTemp[6]);
		strcat(szFileName[24], szTemp[24]);
		//strcpy(szFileName[24], szTemp[24]); //Fix Move
		strcat(szFileName[26], szTemp[26]);
		strcat(szFileName[28], szTemp[28]);
		strcat(szFileName[MAX_FILE_NAME-1], szTemp[MAX_FILE_NAME-1]);
	}
	else
	{
		strcat(szFileName[MAX_FILE_NAME-1], "lang\\Kor\\commonloc.cfg");
		strcat(szFileName[6], "lang\\Kor\\CheckSum.dat");
		strcat(szFileName[24],"lang\\Kor\\Movereq(Kor).txt");
		//strcpy(szFileName[24], szTemp[24]);
		strcat(szFileName[26],"lang\\Kor\\ItemSetOption(Kor).txt");
		strcat(szFileName[28],"lang\\Kor\\ItemSetType(Kor).txt");
	}

	
	
	return a;
}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)void AGGetClientVersion(HANDLE handle,char* szClientVersion,char* szClientSerial)
{
	GetPrivateProfileString("GameServerInfo","ClientExeVersion","1.04.15",szClientVersion,8,szFileName[MAX_FILE_NAME-1]);
	GetPrivateProfileString("GameServerInfo","ClientExeSerial","ArenaMuserver",szClientSerial,20,szFileName[MAX_FILE_NAME-1]);
}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)void AGSetSubInfo(HANDLE handle,int gServerMaxUser,int gObjTotalUser,int gMonsterHp,int gItemDropPer,int gAddExperience,int GetEventFlag())
{

}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)void AGGetKey(HANDLE handle,char* key,int startindex,int len)
{
	for (int counter=0; counter<len; counter++)
	{
		key[startindex+counter]=szGSAuthKey[startindex+counter];
	}
}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)void AGRequestData(HANDLE handle,int type)
{
	gType=type;	// Set the Data Request Number
}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)int AGGetDataBufferSize(HANDLE handle)
{

	int iFileSize;

	if (hFile != NULL)
	{
		CloseHandle(hFile);
		GlobalUnlock((HGLOBAL)g_hAllocFile);
		GlobalFree((HGLOBAL)hGA);
	}



	hFile=CreateFile(szFileName[gType],GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);

	if ( hFile == NULL )
	{
		MsgBox("Can't Open File %s [%d]", szFileName[gType], GetLastError());
		return 0;
	}

	iFileSize = GetFileSize(hFile, NULL);
	hGA= GlobalAlloc(GHND, iFileSize+1);
	g_hAllocFile = GlobalLock((HGLOBAL)hGA);
	ReadFile(hFile, g_hAllocFile, iFileSize, &Bytes, NULL);
	CloseHandle(hFile);
	hFile = NULL;

	return iFileSize;

}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)char* AGGetDataBuffer(HANDLE handle)
{
	if ( g_hAllocFile == NULL )
	{
		MsgBox("Allocation Failed : Request [%d]", gType);
		return NULL;
	}


	return (char*)g_hAllocFile;
}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)void AGConnectSetFS()
{
	MessageBox(NULL,"Function Not Supported","::WzAG::",MB_OK|MB_ICONERROR);
}
// ----------------------------------------------------------
// ----------------------------------------------------------
extern "C" _declspec(dllexport)void AGReleaseHandle(HANDLE handle)
{
	if (hFile != NULL)
	{
		CloseHandle(hFile);
		hFile = NULL;
		GlobalUnlock((HGLOBAL)g_hAllocFile);
		GlobalFree((HGLOBAL)hGA);
	}
}
// ----------------------------------------------------------
// ----------------------------------------------------------