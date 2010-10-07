///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Copyright © NetworkDLS 2002, All rights reserved
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CRECORDSET_H
#define _CRECORDSET_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SQL.H>
#include <SQLExt.H>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CRecordSet{
	
private:
	typedef int (*ErrorHandler)(const char *sSource, const char *sErrorMsg, const int iErrorNumber);
	ErrorHandler pErrorHandler;

public:
	void SetErrorHandler(ErrorHandler pHandler);

	bool Close(void);
	bool Fetch(void);
	bool Fetch(int *iErrorCode);
	bool Reset(void);

	bool GetData(const SQLUSMALLINT iCol, SQLSMALLINT iType, SQLPOINTER pvBuf, SQLINTEGER iBufSz, SQLINTEGER *piOutBufSz);
	bool GetColumnInfo(const int iCol, char *sOutName, int iSzOfOutName, int *iOutColNameLen, int *ioutDataType, int *iOutColSize, int *iNumOfDeciPlaces, int *iColNullable);
	bool BinColumnEx(const int iCol, char *sBuf, const int iBufSz, int *iOutLen);
	bool sColumnEx(const int iCol, char *sBuf, const int iBufSz, int *iOutLen);
	bool lColumnEx(const int iCol, long *plOutVal);
	long lColumn(const int iCol);
	bool dColumnEx(const int iCol, double *pdOutVal);
	double dColumn(const int iCol);
	bool fColumnEx(const int iCol, float *pfOutVal);
	float fColumn(const int iCol);
	bool GetErrorMessage(int *iOutErr, char *sOutError, const int iErrBufSz);
	bool ThrowErrorIfSet(void);
	bool ThrowError(void);

	int RTrim(char *sData, int iDataSz);
	void ReplaceSingleQuotes(char *sData, int iDataSz);

	HSTMT hSTMT;
	long RowCount;
	long ColumnCount;

	bool bTrimCharData;
	bool bReplaceSingleQuotes;
	bool bThrowErrors;

    CRecordSet();
    ~CRecordSet();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
