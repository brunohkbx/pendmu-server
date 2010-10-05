/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

//Includes & Defines
#include <stdio.h>
#include "StdAfx.h"
#define CONSOLETITLE "--:: Syrius Servers Season 4 Full::--"
void cWriteLog(char *Buff);

#ifndef LOG_H
	#define LOG_H

class Logger
{
public:
	Logger();
	~Logger();
	void InitCore();
	void ConsoleOutput(const char* Format, ...);
	void ConsoleOutputDT(const char* Format, ...);
	void ConsoleInput(char * Buff);
	void ConsoleCmd(char* Input);
};
extern Logger conLog;



#define LOG_HEADER_INFO "[Information]"
#define LOG_HEADER_DEBUG "[Debug]"
#define LOG_HEADER_ERROR "[Error]"
#define LOG_HEADER_NORMAL ""
#define LOG_HEADER_WARNING "[Warning]"
#define LOG_HEADER_RECV "[Receive]"
#define LOG_HEADER_SEND "[Send]"

enum LOG_COLORS {
	COLOR_BLACK		= 1,
	COLOR_RED		= 2,
	COLOR_GREEN		= 3,
	COLOR_BLUE		= 4,
	COLOR_DRED	= 5,
};

class CLog {
public:
	CLog();
	~CLog();

	void outInfo(const char *format, ...);
	void outDebug(const char *format, ...);
	void outError(const char *format, ...);
	void outNormal(const char *format, ...);
	void outWarning(const char *format, ...);
	void outRecv(const char *format, ...);
	void outSend(const char *format, ...);

	void ActivateDebug() { this->bIsDebugLogActive = true; };
	void DeactivateDebug() { this->bIsDebugLogActive = false; };

private:
	void Log();
	char out[2048];
	char tmp[2048];
	int  LogColor;
	bool bIsDebugLogActive;
};

extern CLog Log;

class CMessages {
public:
	CMessages();
	~CMessages();

	void outNormal(DWORD Index, const char *format, ...);
	void outBlue(DWORD Index, const char *format, ...);
	void outGreen(DWORD Index, const char *format, ...);
	void outOlive(DWORD Index, const char *format, ...);
	void outGolden(DWORD Index, const char *format, ...);
	void outYellow(DWORD Index, const char *format, ...);
	void outBarMsg(DWORD Index, int Color, const char *format, ...); 
	void outToAll(const char *format, ...);
	void MsgSrv(const char *Format,...);
private:
	void Messages(int Type);
	char out[2048];
	char tmp[2048];
	int Type;
	int MsgColor;
	DWORD PlayerIndex;
};

extern CMessages Messages;


#endif // ~LOG_H
