#include <rpc.h>
#include <rpcdce.h>
#include "Security.h"


#define MacCount 2
bool CheckingMAC(LPCSTR MacID)
{
	char ClientsMacs[MacCount][18] =
	{
		"00-0E-50-F1-6F-FA", //Syrius Server
		"00-1F-D0-9F-F8-C3" //denied
		//"00-13-8F-C0-16-15" // Lordy
	};

	for(int x=0; x<MacCount; x++)
	{
		if(!strcmp(MacID,ClientsMacs[x]))
		{
			return true;
		}
	}
	return false;
}

bool CheckMAC()
{
	unsigned char MACData[6];
	UUID uuid;
	UuidCreateSequential( &uuid ); 

	for (int i=2; i<8; i++) 
		MACData[i - 2] = uuid.Data4[i];

	
	sprintf(MACADDR, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);

	if(CheckingMAC(MACADDR))
	{
		return true;
	}

	else
	{
		MessageBoxA(NULL,"You don't have license to use these files!","Error!",MB_OK);
		::ExitProcess(0);
	}
	return false;
}


	