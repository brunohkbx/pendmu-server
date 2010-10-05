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
#include <SQL.H>
#include <SqlExt.H>

#include "CSQL.H"
#include "CRecordSet.H"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CRecordSet::ReplaceSingleQuotes(char *sData, int iDataSz)
{
    int iRPos = 0;

    while(iRPos < iDataSz)
    {
        if(sData[iRPos] == '\'')
		{
            sData[iRPos] = '`';
		}
        iRPos++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CRecordSet::RTrim(char *sData, int iDataSz)
{
    int iPos = iDataSz;

    if(iDataSz == 0)
        return iDataSz;//Return the new data length.

    if(sData[iDataSz-1] != ' ')
        return iDataSz;//Return the new data length.

    iPos--;

    while(iPos != 0 && sData[iPos] == ' ')
        iPos--;

    if(sData[iPos] != ' ')
        iPos++;

    sData[iPos] = '\0';

    return iPos; //Return the new data length.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::Reset(void)
{
	bool bResult = false;

	bResult = (SQLFreeStmt(this->hSTMT, SQL_UNBIND) == SQL_SUCCESS);
	bResult = (SQLFreeStmt(this->hSTMT, SQL_RESET_PARAMS) == SQL_SUCCESS);

	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::Close(void)
{
	bool bResult = (SQLFreeHandle(SQL_HANDLE_STMT, this->hSTMT) == SQL_SUCCESS);

	this->RowCount = 0;
	this->ColumnCount = 0;
	this->hSTMT = NULL;

	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::Fetch(int *iErrorCode)
{
	if(SQL_SUCCEEDED((*iErrorCode = SQLFetch(this->hSTMT))))
	{
        return true;
	}
	else {
		char *sErrorType = NULL;

		if(*iErrorCode == SQL_SUCCESS){
			sErrorType = "SQL_SUCCESS";
		}
		else if(*iErrorCode == SQL_SUCCESS_WITH_INFO){
			sErrorType = "SQL_SUCCESS_WITH_INFO";
		}
		else if(*iErrorCode == SQL_NO_DATA){
			sErrorType = "SQL_NO_DATA";
			return false;
		}
		else if(*iErrorCode == SQL_STILL_EXECUTING){
			sErrorType = "SQL_STILL_EXECUTING";
		}
		else if(*iErrorCode == SQL_ERROR){
			sErrorType = "SQL_ERROR";
		}
		else if(*iErrorCode == SQL_INVALID_HANDLE){
			sErrorType = "SQL_INVALID_HANDLE";
		}
		else{
			sErrorType = "OTHER";
		}

		this->ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::Fetch(void)
{
	int iErrorCode = 0;
	return this->Fetch(&iErrorCode);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::GetData(const SQLUSMALLINT iCol, SQLSMALLINT iType, SQLPOINTER pvBuf, SQLINTEGER iBufSz, SQLINTEGER *piOutBufSz)
{
    if(SQL_SUCCEEDED(SQLGetData(this->hSTMT, iCol, iType, pvBuf, iBufSz, piOutBufSz)))
	{
		return true;
	}
	else {
		ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::GetColumnInfo(const int iCol, char *sOutName, int iSzOfOutName, int *iOutColNameLen,
							int *ioutDataType, int *iOutColSize, int *iNumOfDeciPlaces, int *iColNullable)
{
	if(SQL_SUCCEEDED(SQLDescribeColA(this->hSTMT, iCol, (SQLCHAR *)sOutName, (SQLSMALLINT)iSzOfOutName,
		(SQLSMALLINT *)iOutColNameLen, (SQLSMALLINT *)ioutDataType, (SQLUINTEGER *)iOutColSize,
		(SQLSMALLINT *)iNumOfDeciPlaces, (SQLSMALLINT *)iColNullable)))
	{
		return true;
	}
	else return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::sColumnEx(const int iCol, char *sBuf, const int iBufSz, int *iOutLen)
{
	int iLen = 0;

	if(SQL_SUCCEEDED(SQLGetData(this->hSTMT, iCol, SQL_C_CHAR, sBuf, iBufSz, (SQLINTEGER *)&iLen)))
	{
		if(iLen > iBufSz)
		{
			iLen = iBufSz;
		}

		if(bReplaceSingleQuotes)
		{
			this->ReplaceSingleQuotes(sBuf, iLen);
		}

		if(bTrimCharData)
		{
			iLen = RTrim(sBuf, iLen);
		}

		if(iOutLen)
		{
			*iOutLen = iLen;
		}
		
		return true;
	}
	else {
		this->ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::lColumnEx(const int iCol, long *plOutVal)
{
	long piOutBufSz = 0;

	if(SQL_SUCCEEDED(SQLGetData(this->hSTMT, iCol, SQL_C_LONG, plOutVal, sizeof(long), &piOutBufSz)))
	{
		return true;
	}
	else {
		this->ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long CRecordSet::lColumn(const int iCol)
{
	long lTemp = 0;

	if(this->lColumnEx(iCol, &lTemp))
	{
	    return lTemp;
	}
	else return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::dColumnEx(const int iCol, double *pdOutVal)
{
	long piOutBufSz = 0;

	if(SQL_SUCCEEDED(SQLGetData(this->hSTMT, iCol, SQL_FLOAT, pdOutVal, sizeof(double), &piOutBufSz)))
	{
		return true;
	}
	else {
		this->ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double CRecordSet::dColumn(const int iCol)
{
	double dTemp = 0;

	if(this->dColumnEx(iCol, &dTemp))
	{
	    return dTemp;
	}
	else return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::fColumnEx(const int iCol, float *pfOutVal)
{
	long piOutBufSz = 0;

	if(SQL_SUCCEEDED(SQLGetData(this->hSTMT, iCol, SQL_FLOAT, pfOutVal, sizeof(float), &piOutBufSz)))
	{
		return true;
	}
	else {
		this->ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float CRecordSet::fColumn(const int iCol)
{
	float fTemp = 0;

	if(this->fColumnEx(iCol, &fTemp))
	{
	    return fTemp;
	}
	else return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::BinColumnEx(const int iCol, char *sBuf, const int iBufSz, int *iOutLen)
{
	SQLLEN iLen = 0;

	if(SQL_SUCCEEDED(SQLGetData(this->hSTMT, iCol, SQL_C_BINARY, sBuf, iBufSz, (SQLLEN *)&iLen)))
	{
		if(iLen > iBufSz)
		{
			iLen = iBufSz;
		}

		if(this->bReplaceSingleQuotes)
		{
			this->ReplaceSingleQuotes(sBuf, iLen);
		}

		if(this->bTrimCharData)
		{
			iLen = RTrim(sBuf, iLen);
		}

		if(iOutLen)
		{
			*iOutLen = iLen;
		}
		
		return true;
	}
	else {
		this->ThrowErrorIfSet();
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordSet::CRecordSet()
{
	this->hSTMT = NULL;
	this->RowCount = 0;
	this->ColumnCount = 0;

	this->bTrimCharData = true;
	this->bReplaceSingleQuotes = true;
	this->bThrowErrors = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordSet::~CRecordSet()
{
	this->hSTMT = NULL;
	this->RowCount = 0;
	this->ColumnCount = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::GetErrorMessage(int *iOutErr, char *sOutError, const int iErrBufSz)
{
	SQLCHAR     sSQLState[20];
	SQLSMALLINT iOutErrorMsgSz;

	return SQL_SUCCEEDED(SQLErrorA(NULL, NULL, this->hSTMT, sSQLState,
		(SQLINTEGER *)iOutErr, (SQLCHAR *)sOutError, iErrBufSz, &iOutErrorMsgSz));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::ThrowErrorIfSet(void)
{
	if(this->bThrowErrors)
	{
		return this->ThrowError();
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRecordSet::ThrowError(void)
{
	char sErrorMsg[2048];
	int iNativeError = 0;

	if(this->GetErrorMessage(&iNativeError, sErrorMsg, sizeof(sErrorMsg)))
	{
		if(this->pErrorHandler)
		{
			this->pErrorHandler("CRecordSet", sErrorMsg, iNativeError);
		}
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CRecordSet::SetErrorHandler(ErrorHandler pHandler)
{
	this->pErrorHandler = pHandler;
}