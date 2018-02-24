#pragma once

#include "VMatrix.h"
#include "Color.h"

class Globals
{
public:
	HWND CSGOWindow;
	bool RenderInit;

private:
}; extern Globals* g_Globals;

typedef void* (*CreateInterfaceFn) (const char *pName, int *pReturnCode);
typedef void (*pfnDemoCustomDataCallback) (unsigned char *pData, size_t iSize);

typedef struct PlayerInfo_s
{
	__int64         unknown;            //0x0000 
	union
	{
		__int64       steamID64;          //0x0008 - SteamID64
		struct
		{
			__int32     xuidLow;
			__int32     xuidHigh;
		};
	};
	char            szName[128];        //0x0010 - Player Name
	int             userId;             //0x0090 - Unique Server Identifier
	char            szSteamID[20];      //0x0094 - STEAM_X:Y:Z
	char            pad_0x00A8[0x10];   //0x00A8
	unsigned long   iSteamID;           //0x00B8 - SteamID 
	char            szFriendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customFiles[4];
	unsigned char   filesDownloaded;
} PlayerInfo_t;

struct cplane_t
{
	Vector	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];

};