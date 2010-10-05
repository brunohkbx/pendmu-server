///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Copyright © NetworkDLS 2002, All rights reserved
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CBoundRecordSet_H
#define _CBoundRecordSet_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SQL.H>
#include <SQLExt.H>
#include "CSQLValue.H"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBoundRecordSet{

private:
	typedef int (*ErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber);
	ErrorHandler pErrorHandler;

public:
	void SetErrorHandler(ErrorHandler pHandler);

	bool Close(void);
	bool Fetch(void);
	bool Fetch(int *iErrorCode);
	bool Reset(void);

	bool GetColumnInfo(const int iCol, char *sOutName, int iSzOfOutName, int *iOutColNameLen,
		int *ioutDataType, int *iOutColSize, int *iNumOfDeciPlaces, int *iColNullable);

	CSQLValue Values(const char *sColumnName);

	bool GetErrorMessage(int *iOutErr, char *sOutError, const int iErrBufSz);
	bool ThrowErrorIfSet(void);
	bool ThrowError(void);

	int GetColumnIndex(const char *sColumnName);
	int GetColumnOrdinal(const char *sColumnName);
	CTypes::CType GetDefaultConversion(SQLTypes::SQLType DataType);

	LPVOID Bind(int iIndex, CTypes::CType TheConversion);
	LPVOID Bind(const char *sColumnName, CTypes::CType TheConversion);

	char *BindString(const char *sColumnName);
	char *BindBinary(const char *sColumnName);
	signed int &BindSignedInteger(const char *sColumnName);
	unsigned int &BindUnsignedInteger(const char *sColumnName);
	double &BindDouble(const char *sColumnName);
	float &BindFloat(const char *sColumnName);
	unsigned __int64 &BindUnsignedI64(const char *sColumnName);
	signed __int64 &BindSignedI64(const char *sColumnName);

	void ReplaceSingleQuotes(char *sData, int iDataSz);

	RECORDSET_COLUMN Columns;

	HSTMT hSTMT;
	long RowCount;

	bool bTrimCharData;
	bool bReplaceSingleQuotes;
	bool bThrowErrors;

    CBoundRecordSet();
    ~CBoundRecordSet();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
