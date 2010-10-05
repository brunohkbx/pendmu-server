#ifndef _MEM_SCRIPT_H
#define _MEM_SCRIPT_H

class CMemScript
{
public:
    CMemScript();
    virtual ~CMemScript();
    bool SetBuffer(char* filename);
    int GetChar();
    void UnGetChar(int ch);
    int GetToken();
    int GetNumber();
    char* GetString();
private:
	HANDLE m_file;
    HANDLE m_global;
    int m_count;
	char* m_buff;
	DWORD m_size;
    float m_number;
    char m_string[100];
};

#endif