/********************************************
* Syrius DLL Season 4 FULL + MOD
* Code By: Mr.Lai
* Year: 2009
* Support: All Protocol
* Credit goes to lots of people
*********************************************/

#include "StdAfx.h"
#include "Maps.h"
#include "Utils.h"


CHAR MapBuff[65][24]=
{
    "..\\data\\Terrain1.att",
	"..\\data\\Terrain2.att",
	"..\\data\\Terrain3.att",
	"..\\data\\Terrain4.att",
	"..\\data\\Terrain5.att",
	"..\\data\\Terrain6.att",
	"..\\data\\Terrain7.att",
	"..\\data\\Terrain8.att",
	"..\\data\\Terrain9.att",
	"..\\data\\Terrain10.att",
	"..\\data\\Terrain11.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain31.att",
	"..\\data\\Terrain32.att",
	"..\\data\\Terrain10.att", //DS 6 7 8 (33)
	"..\\data\\Terrain34.att",
	"..\\data\\Terrain35.att",
	"..\\data\\TerrNull.att", //NUll (No Map)
	"..\\data\\Terrain25.att", //Klima 7 (37)
	"..\\data\\Terrain38.att",
	"..\\data\\Terrain39.att",
	"..\\data\\Terrain40.att",
	"..\\data\\Terrain41.att",
	"..\\data\\Terrain42.att",
	"..\\data\\Terrain43.att",
	"..\\data\\TerrNull.att", //NUll (No Map) (44)
	"..\\data\\TerrNull.att", //NUll (No Map) (45)	
	"..\\data\\Terrain47.att", //Illusion Temple 1->6 (46 or 47 I don't know :-??) 
	"..\\data\\Terrain47.att",
	"..\\data\\Terrain47.att",
	"..\\data\\Terrain47.att",
	"..\\data\\Terrain47.att",
	"..\\data\\Terrain47.att", 
	"..\\data\\Terrain52.att", //Elbeland (52)
	"..\\data\\Terrain12.att", //BC 8 (53)
	"..\\data\\Terrain19.att", //CC 7 (54)
	"..\\data\\TerrNull.att", //No Map (55)
	"..\\data\\TerrNull.att", //No Map (59)
	"..\\data\\Terrain57.att", //Swap Of Calmness (57)
	"..\\data\\Terrain58.att",
	"..\\data\\Terrain59.att",
	"..\\data\\TerrNull.att", //No Map (60)
	"..\\data\\TerrNull.att", //No Map (61)
	"..\\data\\TerrNull.att", //No Map (62)
	"..\\data\\Terrain63.att", //Santa Town (63)
	"..\\data\\Terrain64.att", //Vulcanus (64)
	"..\\data\\Terrain65.att", //Duel Map (65)
};


void MapInit()
{
	
	
	SetByte(0x0050AD29,0xE9);
	SetByte(0x0050AD2A,0xA2);
	SetByte(0x0050AD2B,0x01);
	SetByte(0x0050AD2C,0x00);
	SetByte(0x0050AD2D,0x00);
	SetByte(0x0050AD2E,0x90);
	

	SetByte(0x0056A3BB,0xE9);
	SetByte(0x0056A3BC,0x81);
	SetByte(0x0056A3BD,0x0D);
	SetByte(0x0056A3BE,0x00);
	SetByte(0x0056A3BF,0x00);
	SetByte(0x0056A3C0,0x89);



	SetByte(0x0056B177,0x81);
	SetByte(0x0056B178,0xC2);
	SetByte(0x0056B179,0x24);
	SetByte(0x0056B17A,0x28);
	SetByte(0x0056B17B,0x78);
	SetByte(0x0056B17C,0x00);
	SetByte(0x0056B17D,0x90);
	SetByte(0x0056B17E,0x90);
	SetByte(0x0056B17F,0x90);
	SetByte(0x0056B180,0x90);
	SetByte(0x0056B181,0x90);
	SetByte(0x0056B182,0x90);
	SetByte(0x0056B183,0x90);
	SetByte(0x0056B184,0x90);
	SetByte(0x0056B185,0x90);
	SetByte(0x0056B186,0x90);
	SetByte(0x0056B187,0x90);
	SetByte(0x0056B188,0x90);
	SetByte(0x0056B189,0x52);

	SetByte(0x0059F9F9,0xEB);

	*(DWORD*)(0x0056B177+2) = (DWORD)&MapBuff;

	SetByte(0x0056B174+2,24);

	SetByte(0x0040E37D+3,NumMaps);
	SetByte(0x0059F133+2,NumMaps); // MapServ info max map change
	SetByte(0x00430529+3,NumMaps);
	SetByte(0x0043D05F+3,NumMaps);
	SetByte(0x004B6C3F+3,NumMaps);
	SetByte(0x00501A60+3,NumMaps);
	SetByte(0x00503282+2,NumMaps);
	SetByte(0x0050A0B2+2,NumMaps);
	SetByte(0x0050AAE2+3,NumMaps);
	SetByte(0x0050C7EE+2,NumMaps);
	SetByte(0x0050CD5E+2,NumMaps);

	SetByte(0x0052D011+3,NumMaps+1);
	SetByte(0x00539CA9+3,NumMaps+1);
	SetByte(0x0053A0A7+3,NumMaps+1);
	SetByte(0x0053A0D7+3,NumMaps+1);
	SetByte(0x005692F3+1,NumMaps+1);
	SetByte(0x0056935E+1,NumMaps+1);
	SetByte(0x0056B153+3,NumMaps+1);
	//SetByte(0x0057ABE5+3,NumMaps+1);
	SetByte(0x0059E6B4+3,NumMaps+1);

}

/*
	SetByte(0x0040E37D+3,NumMaps);
	SetByte(0x0059F133+2,NumMaps); // MapServ info max map change
	SetByte(0x00430529+3,NumMaps);
	SetByte(0x0043D05F+3,NumMaps);
	SetByte(0x004B6C3F+3,NumMaps);
	SetByte(0x00501A60+3,NumMaps);
	SetByte(0x00503282+2,NumMaps);
	SetByte(0x0050A0B2+2,NumMaps);
	SetByte(0x0050AAE2+3,NumMaps);
	SetByte(0x0050C7EE+2,NumMaps);
	SetByte(0x0050CD5E+2,NumMaps);

	SetByte(0x0052D011+3,NumMaps+1);
	SetByte(0x00539CA9+3,NumMaps+1);
	SetByte(0x0053A0A7+3,NumMaps+1);
	SetByte(0x0053A0D7+3,NumMaps+1);
	SetByte(0x005692F3+1,NumMaps+1);
	SetByte(0x0056935E+1,NumMaps+1);
	SetByte(0x0056B153+3,NumMaps+1);
	//SetByte(0x0057ABE5+3,NumMaps+1);
	SetByte(0x0059E6B4+3,NumMaps+1);
	*/