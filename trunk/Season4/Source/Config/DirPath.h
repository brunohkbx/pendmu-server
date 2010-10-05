#ifndef _DIR_PATH_H
#define _DIR_PATH_H

#define FIRST_PATH "..\\Data\\"

class CDirPath
{
public:
    CDirPath();
	virtual ~CDirPath();
	void SetFirstPath(char* path);
	char* GetNewPath(char* file);
private:
	char m_FirstPath[256];
	char m_NewPath[256];
};

extern CDirPath gDirPath;

#endif
