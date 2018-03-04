#pragma once

const float OUTLINE_WIDTH = 3;
const float LINE_WIDTH = 1;

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

enum EntityFlags : int
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8)
};

class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	int       command_number;     // For matching server and client commands for debugging
	int       tick_count;         // The tick the client created this command
	QAngle    viewangles;         // Player instantaneous view angles.
	Vector    aimdirection;       // 
	float     forwardmove;        // Forward velocity
	float     sidemove;           // Sideways velocity
	float     upmove;             // Upward velocity
	int       buttons;            // Attack button states
	byte      impulse;            // Impulse command issued.
	int       weaponselect;       // Current weapon id
	int       weaponsubtype;      // 
	int       random_seed;        // For shared random functions
	short     mousedx;            // Mouse accum in x from create move
	short     mousedy;            // Mouse accum in y from create move
	bool      hasbeenpredicted;   // Client only, tracks whether we've predicted this command at least once
	char      pad_0x4C[0x18];
};