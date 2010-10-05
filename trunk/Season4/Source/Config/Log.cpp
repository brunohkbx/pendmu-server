/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "Log.h"
#include "Gameserver.h"
#include "Utils.h"
#include <stdlib.h>
#include <windows.h>

//Console Logger
Logger conLog;
DWORD PiD;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void LoggerCore(PVOID pVoid)
{
	
	AllocConsole();
	SetConsoleTitleA(CONSOLETITLE);
	conLog.ConsoleOutput(" ");
conLog.ConsoleOutput("[System] Console Initialized!!");
conLog.ConsoleOutput("[System] Syrius Project V1.9");
conLog.ConsoleOutput("[System] Loading Data");
conLog.ConsoleOutput("[Version]CustomQuest & More!!");
conLog.ConsoleOutput("License to: %s",MACADDR);
conLog.ConsoleOutputDT("GameServer Starting...");
conLog.ConsoleOutputDT("File Ini Read ...");
conLog.ConsoleOutputDT("GameServer Ready!");

int ProtocolUse = GetPrivateProfileInt("Protocol","GSProtocol",1,"..//OptionsData//Options.ini");

switch(ProtocolUse)
{
case 0:
	conLog.ConsoleOutputDT("Protocol is Korean!");
	break;
case 1:
	conLog.ConsoleOutputDT("Protocol is Japanese!");
	break;
case 2:
	conLog.ConsoleOutputDT("Protocol is Vietnamese!");
	break;
case 3:
	conLog.ConsoleOutputDT("Protocol is English!");
	break;
case 4:
	conLog.ConsoleOutputDT("Protocol is Chinese!");
	break;
default:
	conLog.ConsoleOutputDT("Protocol is Japanese!");
	break;
}
	
	char temp[255];
	while(true)
	{
		conLog.ConsoleInput(temp);
		Sleep(100);
	}
	_endthread();
}


void Logger::InitCore()
{
	_beginthread( LoggerCore, 0, NULL  ); 
	Sleep(10);


}

void Logger::ConsoleOutput(const char* Format, ...)
{
	char Message[255];
	DWORD dwBytesWritten;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message,Format, pArguments);
	va_end(pArguments);
	char outputmsg[1024];
	sprintf(outputmsg,"%s \n", Message);
	WriteFile(Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
}

void Logger::ConsoleOutputDT(const char* Format, ...)
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	char Message[255];
	DWORD dwBytesWritten;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message,Format, pArguments);
	va_end(pArguments);
	char currdate[11] = {0};
	sprintf(currdate, "%02d:%02d:%02d", t.wHour, t.wMinute, t.wSecond);
	char outputmsg[1024];
	sprintf(outputmsg,"[%s]: %s \n", currdate,Message);
	WriteFile(Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
	
}

void Logger::ConsoleInput(char * Buff)
{
	char Text[100] = {0};
	DWORD dwBytesRead=0x64;
	strcpy(Text,Buff);
	HANDLE Handle = GetStdHandle(STD_INPUT_HANDLE);
	ReadFile(Handle, Text, sizeof(Text), &dwBytesRead, NULL);
	this->ConsoleCmd(Text);
}
void Logger::ConsoleCmd(char* Input)
{
	//char Text[1024] = {0};
	if(!strncmp(Input,"/clrscr",7))
	{
		system("cls");
		return;
	}
	else if(!strncmp(Input,"/exit",5))
	{
		::ExitProcess(0);
	}
	else if(!strncmp(Input,"/all ",5))
    {
        char * pText =(char *) ((&Input[5]));
		for (int i=8000;i<9000;i++)
		{
			if(gObjIsConnected(i)==true)
			{
				GCServerMsgStringSend(pText,i,0);
			}
		}
		this->ConsoleOutput("Messenger Sended.");
		return;
    }
	else if(!strncmp(Input,"/firework ",10))
    {
        char * pText =(char *) ((&Input[10]));
			
		FireWorksSendAll(atoi(pText));
	
		this->ConsoleOutput("FireWork All Server OK [Type: %d].",atoi(pText));
		return;
    }
	else if(!strncmp(Input,"/online",7))
	{
		int players=0;
		int gms=0;
		for (int i=8000;i<9000;i++)
		{
			if(gObjIsConnected(i)==true)
			{
				if(VerifyGM(i)==true)
					gms++;
				else
					players++;
			}
		}
		this->ConsoleOutput("Total %d GameMasters and %d Players Online",gms,players);
		return;
	}

	else if(!strncmp(Input,"/?",2))
	{
		this->ConsoleOutput("\nCommands Info: \n");
		this->ConsoleOutput("/exit              Exit GameServer.");
		this->ConsoleOutput("/clrscr            Clear Screen.");
		this->ConsoleOutput("/all               Send Messenger to Server.");
		this->ConsoleOutput("/online            Get Total People Online.");
		this->ConsoleOutput("/firework <type>   Make FireWork to All Players.");
		return;
	}
}

extern Logger conLog;



//Log GS
CLog Log;

CLog::CLog() {
	this->bIsDebugLogActive = true;
}

CLog::~CLog() {
}

void CLog::outDebug(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	va_end(argv);

	sprintf_s(this->out, "%s%s", LOG_HEADER_DEBUG, tmp);

	if(this->bIsDebugLogActive)
	{
		LogColor = COLOR_BLUE;
		this->Log();
	}
}

void CLog::outSend(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	va_end(argv);

	sprintf_s(this->out, "%s%s", LOG_HEADER_SEND, tmp);

	if(this->bIsDebugLogActive)
	{
		LogColor = COLOR_BLUE;
		this->Log();
	}
}

void CLog::outRecv(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	va_end(argv);

	sprintf_s(this->out, "%s%s", LOG_HEADER_RECV, tmp);

	if(this->bIsDebugLogActive)
	{
		LogColor = COLOR_GREEN;
		this->Log();
	}
}

void CLog::outError(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	va_end(argv);

	sprintf_s(this->out, "%s%s", LOG_HEADER_ERROR, tmp);
	LogColor = COLOR_RED;
	this->Log();
}

void CLog::outInfo(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	va_end(argv);

	sprintf_s(this->out, "%s%s", LOG_HEADER_INFO, tmp);
	LogColor = COLOR_GREEN;
	this->Log();
}

void CLog::outNormal(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);

	LogColor = COLOR_BLACK;
	this->Log();
}

void CLog::outWarning(const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	va_end(argv);

	sprintf_s(this->out, "%s%s", LOG_HEADER_WARNING, tmp);
	LogColor = COLOR_DRED;
	this->Log();
}

void CLog::Log() {
	SYSTEMTIME t;
	GetLocalTime(&t);

	char currdate[11] = {0};
	sprintf_s(currdate, "%02d:%02d:%02d ", t.wHour, t.wMinute, t.wSecond);
	char tofile[2048] = {0};
	sprintf_s(tofile, "%s%s", currdate, this->out);
	LogAddFuncColor(this->LogColor, tofile);

	ZeroMemory(&tofile, sizeof(tofile));
	ZeroMemory(&tmp, sizeof(tmp));
	ZeroMemory(&out, sizeof(out));
}


void cWriteLog(char *Buff)
{
	

	/*
	fflush(stdin);
	fflush(stdout);
	FILE *fp;

	
	fp=fopen (FileName,"a+b");
	if (fp==NULL)
	{
		MessageBoxA(NULL,"Khong the doc hoac ghi File","--::Syrius DLL::--",MB_OK);
		::ExitProcess(0);
	}
	
	fwrite (&Log,sizeof(char),1,fp);
	fprintf(fp,"%s",Log);
	fclose (fp);
	*/
	SYSTEMTIME t;
	GetLocalTime(&t);
	char FileName[31]={0};
	char Mess[255]={0};
	sprintf_s(FileName,"./POST_LOG/%d-%d-%d.log",t.wDay,t.wMonth,t.wYear);
	sprintf_s(Mess,"[%02d:%02d:%02d]: %s \n",t.wDay,t.wMonth,t.wYear,Buff);
	FILE *fp;
	fp=fopen (FileName,"a");
	if (fp==NULL)
	{
		MessageBoxA(0, "Can Write File Check POST_LOG Folder.", "--::Syrius DLL::--", MB_OK | MB_ICONSTOP);
		::ExitProcess(0);

	}
	fprintf(fp,"%s",Mess);
	fclose (fp);

}

//Message
CMessages Messages;

CMessages::CMessages() {
	//this->bIsDebugLogActive = true;
}

CMessages::~CMessages() {
}

void CMessages::outNormal(DWORD Index,const char *format, ...) {
	Type = 0;
	
	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;
	
	sprintf_s(this->out, "%s", tmp);

	this->Messages(Type);
}

void CMessages::outBlue(DWORD Index,const char *format,...){
	Type = 1;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;

	sprintf_s(this->out, "~%s", tmp);

	this->Messages(Type);
}

void CMessages::outGreen(DWORD Index,const char *format,...){
	Type = 1;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;

	sprintf_s(this->out, "@%s", tmp);

	this->Messages(Type);
}

void CMessages::outOlive(DWORD Index,const char *format,...){
	Type = 1;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;

	sprintf_s(this->out, "@@%s", tmp);

	this->Messages(Type);
}

void CMessages::outGolden(DWORD Index,const char *format,...){
	Type = 2;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;

	sprintf_s(this->out, "%s", tmp);

	this->Messages(Type);
}

void CMessages::outYellow(DWORD Index,const char *format,...){
	Type = 3;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;

	sprintf_s(this->out, "%s", tmp);

	this->Messages(Type);
}

void CMessages::outBarMsg(DWORD Index,int Color,const char *format,...){
	Type = 4;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	PlayerIndex = Index;
	MsgColor = Color;

	sprintf_s(this->out, "%s", tmp);

	this->Messages(Type);
}

void CMessages::outToAll(const char *format,...){
	Type = 5;

	va_list argv;
	va_start(argv, format);

	vsprintf_s(this->tmp, format, argv);
	memcpy(this->out, tmp, strlen(tmp));
	va_end(argv);
	
	sprintf_s(this->out, "%s", tmp);

	this->Messages(Type);
}

void CMessages::Messages(int Type) {

	if(Type==0){
		GCServerMsgStringSend(tmp,PlayerIndex,1);}
	else if(Type==1){
		GCServerMsgSend(tmp,PlayerIndex,1);}
	else if(Type==2){
		GCServerMsgStringSend(tmp,PlayerIndex,0);}
	else if(Type==3){
		GCServerMsgSend(tmp,PlayerIndex,2);}
	else if(Type==4){
		SendBarMessage(PlayerIndex,MsgColor,tmp);}
	else if(Type==5){
		AllServerMsgSend(tmp);}
	else{
		GCServerMsgStringSend(tmp,PlayerIndex,1);}

	ZeroMemory(&tmp, sizeof(tmp));
	ZeroMemory(&out, sizeof(out));
}
void CMessages::MsgSrv(const char *Format,...)
{
	char Message[1024];
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message,sizeof(Message), Format, pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSendAll(Packet, Len);
	free (Packet);
}