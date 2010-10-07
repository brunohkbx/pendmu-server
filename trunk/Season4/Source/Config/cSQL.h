///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Copyright © NetworkDLS 2002, All rights reserved
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SQLCLASS_H
#define _SQLCLASS_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SQL.H>
#include <SqlExt.H>
#include <ODBCSS.h>

#include "CRecordSet.H"
#include "CBoundRecordSet.H"

#define CSQL_THROW_HARD_ERRORS 0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _TAG_SQLCONNECTION {

	char sApplicationName[255];
	char sDriver[255];
	char sServer[255];
	char sDatabase[255];
	char sUID[255];
	char sPwd[255];

	int iPort;

	bool bUseTrustedConnection;
	bool bUseTCPIPConnection;
	bool bUseMARS;

} SQLCONNECTIONSTRING, *LPSQLCONNECTIONSTRING;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSQL{

private:
	typedef int (*ErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber);
	ErrorHandler pErrorHandler;

public:
	void SetErrorHandler(int (*lpHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber));

	bool Connect(const char *sConnectionString, int (*lpErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber));
	bool Connect(LPSQLCONNECTIONSTRING SQLCon);
	bool Connect(LPSQLCONNECTIONSTRING SQLCon, int (*lpErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber));
	bool Connect(const char *sConnectionString);
	bool Connect(const char *sServer, const char *sDatabase, const char *sUser, const char *sPassword);
	bool Connect(const char *sServer, const char *sDatabase);

	void SetTimeOut(DWORD dwCommandTimeout);
	bool GetErrorMessage(int *iOutErr, char *sOutError, const int iErrBufSz, HSTMT hStmt);
	bool ThrowErrorIfSet(HSTMT hStmt);
	bool ThrowError(HSTMT hStmt);
	void Disconnect(void);
	bool Execute(const char *sSQL);
	bool Execute(const char *sSQL, CBoundRecordSet *lpMyRS);
	bool Execute(const char *sSQL, CBoundRecordSet *lpMyRS, bool AutoBindAll);
	bool Execute(const char *sSQL, CRecordSet *lpMyRS);
	bool Execute(const char *sDatabase, const char *sSQL, CBoundRecordSet *lpMyRS);
	bool Execute(const char *sDatabase, const char *sSQL, CBoundRecordSet *lpMyRS, bool AutoBindAll);
	bool Execute(const char *sDatabase, const char *sSQL);

	bool BuildConnectionString(LPSQLCONNECTIONSTRING SQLCon, char *sOut, int iOutSz);
	bool Focus(const char *sDatabaseName);
	int GetFocus(char *sOutDatabaseName, int iOutDatabaseNameSz);
	bool IsConnected(void);

	HDBC ConnectionHandle(void)
	{
		return hSQLConnection;
	}

	HDBC EnvironmentHandle(void)
	{
		return hSQLEnvironment;
	}

	CSQL::CSQL(const char *sConnectionString, int (*lpErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber));
	CSQL::CSQL(LPSQLCONNECTIONSTRING SQLCon);
	CSQL::CSQL(LPSQLCONNECTIONSTRING SQLCon, int (*lpErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber));
	CSQL::CSQL(const char *sConnectionString);
	CSQL::CSQL(const char *sServer, const char *sDatabase, const char *sUser, const char *sPassword);
	CSQL::CSQL(const char *sServer, const char *sDatabase);

	CSQL::CSQL(void);
	CSQL::~CSQL(void);

	bool bThrowErrors;
	bool bUseBulkOperations;

private:
    HENV hSQLEnvironment;
    HDBC hSQLConnection;
    bool bConnected;
	DWORD dwTimeout;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
