#include "stdafx.h"
#include "wzloader.h"

CMemScript::CMemScript()
{
}

CMemScript::~CMemScript()
{
}

bool CMemScript::SetBuffer(char* filename)
{
    if(this->m_file != 0)
	{
	    CloseHandle(this->m_file);
	    GlobalUnlock((HGLOBAL)this->m_buff);
	    GlobalFree((HGLOBAL)this->m_global);
	}
        
    this->m_file = CreateFile(gDirPath.GetNewPath(filename),GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
 
	if(GetLastError() == ERROR_FILE_NOT_FOUND)
	{
	    return 0;
	}

	
	this->m_global = GlobalAlloc(GHND,0xFFFFF);
     
	this->m_buff = (char*)GlobalLock((HGLOBAL)this->m_global);
    
	ReadFile(this->m_file,this->m_buff,0xFFFFE,&this->m_size,NULL);
        
	this->m_count = 0;

    return 1;
}

int CMemScript::GetChar()
{
    if(this->m_count >= (int)this->m_size)
	{
        return -1;
	}
    else
	{
        return this->m_buff[this->m_count++];
	}
}

void CMemScript::UnGetChar(int ch)
{
    if(this->m_count <= 0)
	{
        return;
	}
    else
	{
        this->m_count--;
        this->m_buff[this->m_count] = ch;
	}
}

int CMemScript::GetToken()
{
    char ch;
    char* p;
    char TempString[100];

	this->m_string[0] = 0;
	this->m_number = 0;

    while(true)
	{
	    ch = this->GetChar();

        if(ch == -1)
		{
            return 2;
		}

		if(isspace(ch) != 0)
		{
		    continue;
		}

	    if(ch == '/' && (ch = this->GetChar()) == '/')
		{
            while(true)
			{
		        ch = this->GetChar();

				if(ch == -1)
				{
				    return 2;
				}

			    if(ch == '\n')
				{
			       break;
				}
			}
		}
		else
		{
		    break;
		}
	}

    switch(ch)
	{
        case 0x23:	// #
        case 0x3B:	// ;
	    case 0x2C:	// ,
	    case 0x7B:	// {
        case 0x7D:	// }
		    return ch;
	    case 0x2D:	//-
	    case 0x2E:	//.
	    case 0x30:	//0
	    case 0x31:	//1
	    case 0x32:	//2
	    case 0x33:	//3
	    case 0x34:	//4		
	    case 0x35:	//5
	    case 0x36:	//6
	    case 0x37:	//7
	    case 0x38:	//8
	    case 0x39:	//9
	        this->UnGetChar(ch);
		    p = TempString;
		
		    while(((ch = this->GetChar()) != -1) && (ch == 0x2E) || ((isdigit(ch) != 0) || (ch == 0x2D))) 
			{
			    *p = ch;
			    p++;
			}		
		    *p = 0;
		    this->m_number = (float)atof(TempString);
		    return 1;
	    case 0x22:	// "	
	        p = &this->m_string[0];
		
		    while(((ch = this->GetChar()) != -1) && (ch != 0x22))	
			{
			    *p = ch;
			    p++;
			}
		    if(ch != 0x22 )
			{
			    this->UnGetChar(ch);
			}
		    *p = 0;
		    return 0;
        default:	
		    if(isalpha(ch))
			{
			    p = &this->m_string[0];
			    *p=ch;
			    p++;

			    while(((ch = this->GetChar()) != -1) && ((ch == 0x2E) || (ch == 0x5F) || (isalnum(ch) != 0)))
				{
				    *p=ch;
				    p++;
				
				}

			    this->UnGetChar(ch);
			    *p=0;
			    return 0;
			}
		    else
			{
			    return 0x3C;
			}
		    break;
	}
}

int CMemScript::GetNumber()
{
    return (int)this->m_number;
}

char* CMemScript::GetString()
{
	return &this->m_string[0];
}
