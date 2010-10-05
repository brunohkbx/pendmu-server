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
#include "CBoundRecordSet.H"
#include "CSQLValue.H"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CSQLValue::RTrim(char *sData, int iDataSz)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSQLValue::ReplaceSingleQuotes(char *sData, int iDataSz)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSQLValue::Initialize(LPRECORDSET_COLUMNINFO lpColumnValue, 
						   bool bTrimCharData, bool bReplaceSingleQuotes, bool bThrowErrors)
{
	this->bcTrimCharData = bTrimCharData;
	this->bcReplaceSingleQuotes = bReplaceSingleQuotes;
	this->bcThrowErrors = bThrowErrors;
	this->lpCValue = lpColumnValue;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQLValue::IsValid(void)
{
	return this->bcIsValid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQLValue::IsNull(void)
{
	return this->lpCValue->Data.IsNull;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CSQLValue::Size(void)
{
	return this->lpCValue->Data.Size;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CSQLValue::ToString(char *sOut, int iMaxSz)
{
	if(this->lpCValue->Data.IsNull)
	{
		sOut[0] = '\0';
		return 0;
	}

	memcpy_s(sOut, iMaxSz, this->ToString(), this->lpCValue->Data.Size);
	sOut[this->lpCValue->Data.Size] = '\0';
	return this->lpCValue->Data.Size;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *CSQLValue::ToString(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return NULL;
	}

	if(this->lpCValue->DataType == SQLTypes::Char || this->lpCValue->DataType == SQLTypes::NChar)
	{
		if(this->bcTrimCharData)
		{
			this->RTrim(((char *)this->lpCValue->Data.Buffer), this->lpCValue->Data.Size);
		}
		if(this->bcReplaceSingleQuotes)
		{
			this->ReplaceSingleQuotes(((char *)this->lpCValue->Data.Buffer), this->lpCValue->Data.Size);
		}
	}
	else if(this->lpCValue->DataType == SQLTypes::VarChar || this->lpCValue->DataType == SQLTypes::NVarChar)
	{
		if(this->bcReplaceSingleQuotes)
		{
			this->ReplaceSingleQuotes(((char *)this->lpCValue->Data.Buffer), this->lpCValue->Data.Size);
		}
	}
	return (char *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CSQLValue::ToBoolean(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(bool *)this->lpCValue->Data.Buffer;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

signed int CSQLValue::ToIntegerS(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(signed int *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int CSQLValue::ToIntegerU(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(unsigned int *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

signed short CSQLValue::ToShortS(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(signed short *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned short CSQLValue::ToShortU(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(unsigned short *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double CSQLValue::ToDouble(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(double *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float CSQLValue::ToFloat(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(float *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned __int64 CSQLValue::ToI64U(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(unsigned __int64 *)this->lpCValue->Data.Buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

signed __int64 CSQLValue::ToI64S(void)
{
	if(this->lpCValue->Data.IsNull)
	{
		return 0;
	}
	return *(signed __int64 *)this->lpCValue->Data.Buffer;
}