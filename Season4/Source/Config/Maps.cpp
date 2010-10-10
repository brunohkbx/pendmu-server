#include "stdafx.h"
#include "Utils.h"
#include "Maps.h"

char MapAttrName[70][24] =
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
	"..\\data\\Terrain33.att",
	"..\\data\\Terrain34.att",
	"..\\data\\Terrain35.att",
	"..\\data\\Terrain36.att",
	"..\\data\\Terrain37.att",
	"..\\data\\Terrain38.att",
	"..\\data\\Terrain39.att",
	"..\\data\\Terrain40.att",
	"..\\data\\Terrain41.att",
	"..\\data\\Terrain42.att",
	"..\\data\\Terrain43.att",
	"..\\data\\Terrain43.att",
	"..\\data\\Terrain43.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain52.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain1.att",
	"..\\data\\Terrain1.att",
	"..\\data\\Terrain57.att",
	"..\\data\\Terrain58.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain63.att",
	"..\\data\\Terrain64.att",
	"..\\data\\Terrain65.att",
	"..\\data\\Terrain66.att",
	"..\\data\\Terrain67.att",
	"..\\data\\Terrain68.att",
	"..\\data\\Terrain69.att",
	"..\\data\\Terrain70.att",
//	"..\\data\\Terrain71.att",
//	"..\\data\\Terrain72.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain73.att",
//	"..\\data\\Terrain80.att",
};

void MapInit()
{
	BYTE NumMaps = 70;

	if(NumMaps > 72)
	{
		SetByte(0x004298DE,0xEB);
		SetByte(0x004298DF,0xBB);
		SetNop(0x004298E0,2);
	}

	SetByte(0x0059F133+2,NumMaps); // MapServ info max map change

	SetByte(0x0050AD29,0xE9);
	SetByte(0x0050AD2A,0xA2);
	SetByte(0x0050AD2B,0x01);
	SetByte(0x0050AD2C,0x00);
	SetByte(0x0050AD2D,0x00);
	SetByte(0x0050AD2E,0x90);

	SetByte(0x005692F3+1,NumMaps);
	SetByte(0x0056935E+1,NumMaps);

	SetByte(0x0056A3BB,0xE9);
	SetByte(0x0056A3BC,0x81);
	SetByte(0x0056A3BD,0x0D);
	SetByte(0x0056A3BE,0x00);
	SetByte(0x0056A3BF,0x00);
	SetByte(0x0056A3C0,0x89);

	SetByte(0x0056B153+3,NumMaps);

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

	*(DWORD*)(0x0056B177+2) = (DWORD)&MapAttrName;

	SetByte(0x0056B174+2,24);
	SetByte(0x00503282+2,NumMaps);
	SetByte(0x004B6C3F+3,NumMaps);
	SetByte(0x0053A0A7+3,NumMaps);
	SetByte(0x0053A0D7+3,NumMaps);
	SetByte(0x0052D011+3,NumMaps);
	SetByte(0x00430529+3,NumMaps);
	SetByte(0x0043D05F+3,NumMaps);

	SetByte(0x0059E6B4+3,NumMaps);
	SetByte(0x00539CA9+3,NumMaps);
	SetByte(0x0049E551+1,NumMaps);
	SetByte(0x00498CD1+1,NumMaps);
	SetByte(0x00501A60+3,NumMaps);

	SetByte(0x0041F6A9,0xEB);
	SetByte(0x0043D073,0xEB);
	SetByte(0x004B7D8D,0xEB);

/*	SetByte(0x0052C01D,0xE9);
	SetByte(0x0052C01D+1,0x38);
	SetByte(0x0052C01D+2,0x10);
	SetByte(0x0052C01D+3,0x00);
	SetByte(0x0052C01D+4,0x00);

	SetByte(0x0052D058,0xCC);
	SetByte(0x0052D059,0xCC);
	SetByte(0x0052D05A,0x83);
	SetByte(0x0052D05A+1,0xF8);
	SetByte(0x0052D05A+2,0x01);
	SetByte(0x0052D05D,0x75);
	SetByte(0x0052D05D+1,0x00);
	SetByte(0x0052D05F,0xE9);
	SetByte(0x0052D05F+1,0xBB);
	SetByte(0x0052D05F+2,0xEF);
	SetByte(0x0052D05F+3,0xFF);
	SetByte(0x0052D05F+4,0xFF);
	SetByte(0x0052D064,0x83);
	SetByte(0x0052D064+1,0xF8);
	SetByte(0x0052D064+3,NumMaps);
	SetByte(0x0052D067,0x75);
	SetByte(0x0052D067+1,0x00);
	SetByte(0x0052D069,0xE9);
	SetByte(0x0052D069+1,0xB1);
	SetByte(0x0052D069+2,0xEF);
	SetByte(0x0052D069+3,0xFF);
	SetByte(0x0052D069+4,0xFF);
	SetByte(0x0052D06E,0x83);
	SetByte(0x0052D06E+1,0xF8);
	SetByte(0x0052D06E+2,0x40);
	SetByte(0x0052D071,0x0F);
	SetByte(0x0052D071+1,0x85);
	SetByte(0x0052D071+2,0xF4);
	SetByte(0x0052D071+3,0xEF);
	SetByte(0x0052D071+4,0xFF);
	SetByte(0x0052D071+5,0xFF);
	SetByte(0x0052D077,0xE9);
	SetByte(0x0052D077+1,0xA3);
	SetByte(0x0052D077+2,0xEF);
	SetByte(0x0052D077+3,0xFF);
	SetByte(0x0052D077+4,0xFF);
	SetByte(0x0052D07C,0xCC);
	SetByte(0x0052D07D,0xCC);
	SetByte(0x0052D07E,0xCC);
	SetByte(0x0052D07F,0xCC);
	SetByte(0x0052D080,0xCC);
	SetByte(0x0052D081,0xCC);*/
}
