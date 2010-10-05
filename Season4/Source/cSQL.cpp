///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Copyright © NetworkDLS 2002, All rights reserved
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <Stdio.H>
#include <stdlib.h>

#include "CSQL.H"
#include "CBoundRecordSet.H"
#include "CRecordSet.H"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DefaultSQLErrorHandler(const char *sSource, const char *sErrorMsg, const int iErrorNumber)
{
	MessageBoxA(GetActiveWindow(), sErrorMsg, sSource, MB_ICONERROR);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(const char *sConnectionString, ErrorHandler pHandler)
{
	this->Connect(sConnectionString, pHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(LPSQLCONNECTIONSTRING SQLCon)
{
	this->Connect(SQLCon);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(LPSQLCONNECTIONSTRING SQLCon, ErrorHandler pHandler)
{
	this->Connect(SQLCon, pHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(const char *sConnectionString)
{
	this->Connect(sConnectionString);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(const char *sServer, const char *sDatabase)
{
	this->Connect(sServer, sDatabase);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(const char *sServer, const char *sDatabase, const char *sUser, const char *sPassword)
{
	this->Connect(sServer, sDatabase, sUser, sPassword);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::CSQL(void)
{
	this->bConnected = false;
	this->Disconnect();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSQL::~CSQL(void)
{
    this->Disconnect();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSQL::SetTimeOut(DWORD dwCommandTimeout)
{
	this->dwTimeout = dwCommandTimeout;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::IsConnected(void)
{
	return this->bConnected;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Connect(const char *sServer, const char *sDatabase)
{
	SQLCONNECTIONSTRING CS;
	memset(&CS, 0, sizeof(CS));

	CS.bUseTrustedConnection = true;
	strcpy_s(CS.sDriver, sizeof(CS.sDriver), "{SQL Server}");
	strcpy_s(CS.sDatabase, sizeof(CS.sDatabase), sDatabase);
	strcpy_s(CS.sServer, sizeof(CS.sServer), sServer);

	return this->Connect(&CS, &DefaultSQLErrorHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Connect(const char *sServer, const char *sDatabase, const char *sUser, const char *sPassword)
{
	SQLCONNECTIONSTRING CS;
	memset(&CS, 0, sizeof(CS));

	CS.bUseTrustedConnection = false;
	//strcpy_s(CS.sDriver, sizeof(CS.sDriver), "{SQL Server}");
	strcpy_s(CS.sDriver, sizeof(CS.sDriver), "{SQL Native Client}");
	strcpy_s(CS.sDatabase, sizeof(CS.sDatabase), sDatabase);
	strcpy_s(CS.sServer, sizeof(CS.sServer), sServer);
	strcpy_s(CS.sUID, sizeof(CS.sUID), sUser);
	strcpy_s(CS.sPwd, sizeof(CS.sPwd), sPassword);

	return this->Connect(&CS, &DefaultSQLErrorHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Connect(const char *sConnectionString)
{
	return this->Connect(sConnectionString, &DefaultSQLErrorHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Connect(LPSQLCONNECTIONSTRING SQLCon, ErrorHandler pHandler)
{
    char sConnectionString[1024];

	if(!this->BuildConnectionString(SQLCon, sConnectionString, sizeof(sConnectionString)))
	{
		return false;
	}

	return this->Connect(sConnectionString, pHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Connect(LPSQLCONNECTIONSTRING SQLCon)
{
	return this->Connect(SQLCon, &DefaultSQLErrorHandler);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Connect(const char *sConnectionString, ErrorHandler pHandler)
{
    SQLRETURN Result;
    SQLCHAR sConStrOut[1024];
    SQLSMALLINT iConStrOutSz = 0;

	this->SetErrorHandler(pHandler);

	this->bConnected = false;
	this->Disconnect();

    // Allocate the environment handle
    Result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->hSQLEnvironment);
    if(!SQL_SUCCEEDED(Result))
    {
        ThrowErrorIfSet(NULL);
		return false;
    }

    // Set the environment attributes
	Result = SQLSetEnvAttr(this->hSQLEnvironment, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    if(!SQL_SUCCEEDED(Result))
    {
        ThrowErrorIfSet(NULL);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
        return false;
    }

    // Allocate the connection handle
    Result = SQLAllocHandle(SQL_HANDLE_DBC, this->hSQLEnvironment, &this->hSQLConnection);
    if(!SQL_SUCCEEDED(Result))
    {
        ThrowErrorIfSet(NULL);
        SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
        return false;
    }

	// Set login timeout to 5 seconds.
    if(!SQL_SUCCEEDED(SQLSetConnectOption(this->hSQLConnection, SQL_LOGIN_TIMEOUT, 5)))
    {
        ThrowErrorIfSet(NULL);
        SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
        return false;
    }
    if(!SQL_SUCCEEDED(SQLSetConnectOption(this->hSQLConnection, SQL_CURSOR_TYPE, SQL_CURSOR_STATIC)))
    {
        ThrowErrorIfSet(NULL);
        SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
        return false;
    }
    if(!SQL_SUCCEEDED(SQLSetConnectOption(this->hSQLConnection, SQL_CONCURRENCY, SQL_CONCUR_READ_ONLY)))
    {
        ThrowErrorIfSet(NULL);
        SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
        return false;
    }

	if(bUseBulkOperations)
	{
		if(!SQL_SUCCEEDED(SQLSetConnectAttr(this->hSQLConnection,
			SQL_COPT_SS_BCP, (void *)SQL_BCP_ON, SQL_IS_INTEGER)))
		{
			ThrowErrorIfSet(NULL);
			SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
			SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
			return false;
		}
	}

	// Connect
    Result = SQLDriverConnectA(
        this->hSQLConnection,         // Connection handle.
        NULL,                         // Window handle.
        (SQLCHAR *)sConnectionString, // Input connect string.
        SQL_NTS,                      // Null-terminated string.
        sConStrOut,                   // Address of output buffer.
        sizeof(sConStrOut),           // Size of output buffer.
        &iConStrOutSz,                // Address of output length.
        SQL_DRIVER_NOPROMPT
    );

    if(!SQL_SUCCEEDED(Result))
    {
        ThrowErrorIfSet(NULL);
        SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
        return false;
    }

    this->bConnected = true;

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::BuildConnectionString(LPSQLCONNECTIONSTRING SQLCon, char *sOut, int iOutSz)
{
    char sTemp[1024];

	//-----------------------------------------------------------------------------------------------
	// Important note!
	//-----------------------------------------------------------------------------------------------
	//		When connecting through the SQLOLEDB provider use the syntax Network Library=dbmssocn
	//			and when connecting through MSDASQL provider use the syntax Network=dbmssocn
	//-----------------------------------------------------------------------------------------------

	//Driver: {SQL Server}

	sprintf_s(sOut, iOutSz, "DRIVER=%s;SERVER=%s;", SQLCon->sDriver, SQLCon->sServer);

	if(strlen(SQLCon->sDatabase) > 0)
	{
		sprintf_s(sTemp, sizeof(sTemp), "DATABASE=%s;", SQLCon->sDatabase);
		strcat_s(sOut, iOutSz, sTemp);
	}

	if(strlen(SQLCon->sApplicationName) > 0)
	{
		sprintf_s(sTemp, sizeof(sTemp), "APP=%s;", SQLCon->sApplicationName);
		strcat_s(sOut, iOutSz, sTemp);
	}

	if(SQLCon->bUseTCPIPConnection)
	{
		sprintf_s(sTemp, sizeof(sTemp), "NETWORK=DBMSSOCN;ADDRESS=%s,%d;", SQLCon->sServer, SQLCon->iPort);
		strcat_s(sOut, iOutSz, sTemp);
	}

	if(SQLCon->bUseMARS)
	{
		strcat_s(sOut, iOutSz, "MARS_Connection=yes;");
	}

	if(SQLCon->bUseTrustedConnection)
	{
		strcat_s(sOut, iOutSz, "TRUSTED_CONNECTION=yes;");
	}
	else{
		sprintf_s(sTemp, sizeof(sTemp), "UID=%s;PWD=%s;TRUSTED_CONNECTION=no;", SQLCon->sUID, SQLCon->sPwd);
		strcat_s(sOut, iOutSz, sTemp);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::GetErrorMessage(int *iOutErr, char *sOutError, const int iErrBufSz, HSTMT hStmt)
{
	SQLCHAR     sSQLState[20];
	SQLSMALLINT iOutErrorMsgSz;

	return SQL_SUCCEEDED(SQLErrorA(this->hSQLEnvironment, this->hSQLConnection,
		hStmt, sSQLState, (SQLINTEGER *)iOutErr, (SQLCHAR *)sOutError, iErrBufSz, &iOutErrorMsgSz));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::ThrowErrorIfSet(HSTMT hStmt)
{
	if(this->bThrowErrors)
	{
		return this->ThrowError(hStmt);
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::ThrowError(HSTMT hStmt)
{
	char sErrorMsg[2048];
	int iNativeError = 0;

	if(GetErrorMessage(&iNativeError, sErrorMsg, sizeof(sErrorMsg), hStmt))
	{
		if(this->pErrorHandler)
		{
			this->pErrorHandler("CSQL", sErrorMsg, iNativeError);
			#ifdef CSQL_THROW_HARD_ERRORS
				__debugbreak();
			#endif
		}
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSQL::Disconnect(void)
{
    if(this->bConnected)
    {
        SQLDisconnect(this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_DBC, this->hSQLConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, this->hSQLEnvironment);
    }

    this->hSQLConnection = NULL;
    this->hSQLEnvironment = NULL;

    this->bConnected = false;
    this->bThrowErrors = true;
	this->bUseBulkOperations = false;
	this->dwTimeout = 30;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sDatabase, const char *sSQL)
{
	char sOldDatabase[1024];
	this->GetFocus(sOldDatabase, sizeof(sOldDatabase));

	if(_strcmpi(sOldDatabase, sDatabase) != 0)
	{
		this->Focus(sDatabase);
	}

	bool bResult = this->Execute(sSQL);

	if(_strcmpi(sOldDatabase, sDatabase) != 0)
	{
		this->Focus(sOldDatabase);
	}

	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sSQL)
{
    if(!bConnected)
	{
        return false;
	}

    SQLRETURN Result = 0;

	bool bResult = false;

    HSTMT stmtHandle = NULL;

	Result = SQLAllocHandle(SQL_HANDLE_STMT, this->hSQLConnection, &stmtHandle);
    if(SQL_SUCCEEDED(Result))
    {
		SQLSetStmtOption(stmtHandle, SQL_RETRIEVE_DATA, SQL_RD_OFF);
		SQLSetStmtOption(stmtHandle, SQL_ATTR_QUERY_TIMEOUT, this->dwTimeout);

		Result = SQLExecDirectA(stmtHandle, (unsigned char *)sSQL, strlen(sSQL));
        if(SQL_SUCCEEDED(Result) || Result == SQL_NO_DATA)
        {
            if(Result == SQL_SUCCESS || Result == SQL_SUCCESS_WITH_INFO || Result == SQL_NO_DATA)
            {
                bResult = true;
            } else this->ThrowErrorIfSet(stmtHandle);
        } else this->ThrowErrorIfSet(stmtHandle);
    } else this->ThrowErrorIfSet(stmtHandle);

	SQLFreeStmt(stmtHandle, SQL_CLOSE);
	SQLFreeHandle(SQL_HANDLE_STMT, stmtHandle);

	stmtHandle = NULL;
    
	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sSQL, CRecordSet *lpMyRS)
{
	if(!this->bConnected)
	{
        return false;
	}

	lpMyRS->SetErrorHandler(this->pErrorHandler);

	SQLRETURN Result = 0;

    Result = SQLAllocHandle(SQL_HANDLE_STMT, this->hSQLConnection, &lpMyRS->hSTMT);
    if(SQL_SUCCEEDED(Result))
    {
		SQLSetStmtOption(lpMyRS->hSTMT, SQL_ATTR_QUERY_TIMEOUT, this->dwTimeout);
		SQLSetStmtOption(lpMyRS->hSTMT, SQL_CONCURRENCY, SQL_CONCUR_READ_ONLY);
		SQLSetStmtOption(lpMyRS->hSTMT, SQL_CURSOR_TYPE, SQL_CURSOR_STATIC);

		Result = SQLPrepareA(lpMyRS->hSTMT, (unsigned char *)sSQL, strlen(sSQL));
        if(SQL_SUCCEEDED(Result))
        {
			Result = SQLExecute(lpMyRS->hSTMT);
            if(Result == SQL_SUCCESS || Result == SQL_SUCCESS_WITH_INFO || Result == SQL_NO_DATA)
            {
				if(SQLRowCount(lpMyRS->hSTMT, &lpMyRS->RowCount) != SQL_SUCCESS)
				{
					lpMyRS->RowCount = 0;
				}

				if(SQLNumResultCols(lpMyRS->hSTMT, (SQLSMALLINT *) &lpMyRS->ColumnCount) != SQL_SUCCESS)
				{
					lpMyRS->ColumnCount = 0;
				}

				return true;

            } else this->ThrowErrorIfSet(lpMyRS->hSTMT);
        } else this->ThrowErrorIfSet(lpMyRS->hSTMT);
    } else this->ThrowErrorIfSet(lpMyRS->hSTMT);

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sSQL, CBoundRecordSet *lpMyRS)
{
	return this->Execute(sSQL, lpMyRS, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sSQL, CBoundRecordSet *lpMyRS, bool AutoBindAll)
{
	if(!this->bConnected)
	{
        return false;
	}

	lpMyRS->SetErrorHandler(this->pErrorHandler);

	SQLRETURN Result = 0;

    Result = SQLAllocHandle(SQL_HANDLE_STMT, this->hSQLConnection, &lpMyRS->hSTMT);
    if(SQL_SUCCEEDED(Result))
    {
		SQLSetStmtOption(lpMyRS->hSTMT, SQL_ATTR_QUERY_TIMEOUT, this->dwTimeout);
		SQLSetStmtOption(lpMyRS->hSTMT, SQL_CONCURRENCY, SQL_CONCUR_READ_ONLY);
		SQLSetStmtOption(lpMyRS->hSTMT, SQL_CURSOR_TYPE, SQL_CURSOR_STATIC);
		
		Result = SQLPrepareA(lpMyRS->hSTMT, (unsigned char *)sSQL, strlen(sSQL));
		if(SQL_SUCCEEDED(Result))
        {
			Result = SQLExecute(lpMyRS->hSTMT);
            if(Result == SQL_SUCCESS || Result == SQL_SUCCESS_WITH_INFO || Result == SQL_NO_DATA)
            {
				if(SQLRowCount(lpMyRS->hSTMT, &lpMyRS->RowCount) != SQL_SUCCESS)
				{
					lpMyRS->RowCount = 0;
				}

				if(SQLNumResultCols(lpMyRS->hSTMT, (SQLSMALLINT *) &lpMyRS->Columns.Count) != SQL_SUCCESS)
				{
					lpMyRS->Columns.Count = 0;
				}

				if(lpMyRS->Columns.Count > 0) //Fill in the column info for the RecordSet.
				{
					#ifdef _USE_GLOBAL_MEMPOOL
						lpMyRS->Columns.Column = (LPRECORDSET_COLUMNINFO)
							pMem->Allocate(lpMyRS->Columns.Count, sizeof(RECORDSET_COLUMNINFO));
					#else
						lpMyRS->Columns.Column = (LPRECORDSET_COLUMNINFO)
							calloc(lpMyRS->Columns.Count, sizeof(RECORDSET_COLUMNINFO));
					#endif

					for(int iCol = 1; iCol < (lpMyRS->Columns.Count + 1); iCol++)
					{
						LPRECORDSET_COLUMNINFO Pointer = &lpMyRS->Columns.Column[iCol-1];
						memset(&Pointer, sizeof(RECORDSET_COLUMNINFO), 0);

						int iColumnNameLength = 0;
						int iIsNullable = 0;
						int iDataType = 0;

						lpMyRS->GetColumnInfo(iCol, Pointer->Name, sizeof(Pointer->Name),
							&iColumnNameLength, &iDataType, &Pointer->MaxSize,
							&Pointer->DecimalPlaces, &iIsNullable);

						Pointer->DataType = (SQLTypes::SQLType)iDataType;
						Pointer->Name[iColumnNameLength] = '\0';
						Pointer->IsNullable = (iIsNullable > 0);
						Pointer->Ordinal = iCol;
						Pointer->IsBound = false;
						if(AutoBindAll)
						{
							lpMyRS->Bind(iCol-1, lpMyRS->GetDefaultConversion(Pointer->DataType));
						}
					}
				}

				return true;

            } else this->ThrowErrorIfSet(lpMyRS->hSTMT);
        } else this->ThrowErrorIfSet(lpMyRS->hSTMT);
    } else this->ThrowErrorIfSet(lpMyRS->hSTMT);

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sDatabase, const char *sSQL, CBoundRecordSet *lpMyRS)
{
	return this->Execute(sDatabase, sSQL, lpMyRS, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Execute(const char *sDatabase, const char *sSQL, CBoundRecordSet *lpMyRS, bool AutoBindAll)
{
	char sOldDatabase[1024];
	this->GetFocus(sOldDatabase, sizeof(sOldDatabase));

	if(_strcmpi(sOldDatabase, sDatabase) != 0)
	{
		this->Focus(sDatabase);
	}

	bool bResult = Execute(sSQL, lpMyRS, AutoBindAll);

	if(_strcmpi(sOldDatabase, sDatabase) != 0)
	{
		this->Focus(sOldDatabase);
	}

	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CSQL::GetFocus(char *sOutDatabaseName, int iOutDatabaseNameSz)
{
    if(!bConnected)
        return -1;

	int iResult = 0;

	CRecordSet rsTemp;

	if(this->Execute("SELECT db_name()", &rsTemp))
	{
		if(rsTemp.Fetch())
		{
			int iLength = 0;
			if(rsTemp.sColumnEx(1, sOutDatabaseName, iOutDatabaseNameSz, &iLength))
			{
				iResult = iLength;
			}
			else iResult = -4;
		}
		else iResult = -3;

		rsTemp.Close();
	}
	else iResult = -2;

	return iResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQL::Focus(const char *sDatabaseName)
{
    if(!this->bConnected)
        return false;

	char sSQL[1024];
	sprintf_s(sSQL, sizeof(sSQL), "USE [%s]", sDatabaseName);

	return this->Execute(sSQL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSQL::SetErrorHandler(ErrorHandler pHandler)
{
	this->pErrorHandler = pHandler;
}