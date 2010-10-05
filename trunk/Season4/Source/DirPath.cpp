#include "stdafx.h"
#include "DirPath.h"

CDirPath gDirPath;

CDirPath::CDirPath()
{
}

CDirPath::~CDirPath()
{
}

void CDirPath::SetFirstPath(char* path)
{
    strcpy(this->m_FirstPath,path);
}

char* CDirPath::GetNewPath(char* file)
{
	strcpy(this->m_NewPath,this->m_FirstPath);
	strcat(this->m_NewPath,file);

	return this->m_NewPath;
}
