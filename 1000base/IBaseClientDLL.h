#pragma once
#include "IEntity.h"

class IPanel;
class CViewSetup
{
public:
	__int32   x;
	__int32   x_old;
	__int32   y;
	__int32   y_old;
	__int32   width;
	__int32   width_old;
	__int32   height;
	__int32   height_old;
	char      pad_0x0020[0x90];
	float     fov;
	float     viewmodel_fov;
	Vector    origin;
	Vector    angles;
	char      pad_0x00D0[0x7C];
};
class ClientClass
{
public:
	BYTE _chPadding[8];
	char* szName;
	RecvTable* rtTable;
	ClientClass* pNextClass;
	int iClassID;
};

class IBaseClientDLL
{
public:
	ClientClass * GetAllClasses()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return g_Utils->get_vfunc<GetAllClassesFn>(this, 8)(this);
	}
};

class IGlobalVars
{
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     absoluteframestarttimestddev;
	float     curtime;
	float     frametime;
	int       maxClients;
	int       tickcount;
	float     intervalPerTick;
	float     interpolationAmount;
	int       simTicksThisFrame;
	int       networkProtocol;
	void*     pSaveData;
	bool      bClient;
	bool      bRemoteClient;

private:
	int       nTimestampNetworkingBase;
	int       nTimestampRandomizeWindow;
};

class IClientMode
{
public:
	virtual             ~IClientMode() {}
	virtual int         ClientModeCSNormal(void *) = 0;
	virtual void        Init() = 0;
	virtual void        InitViewport() = 0;
	virtual void        Shutdown() = 0;
	virtual void        Enable() = 0;
	virtual void        Disable() = 0;
	virtual void        Layout() = 0;
	virtual IPanel*     GetViewport() = 0;
	virtual void*       GetViewportAnimationController() = 0;
	virtual void        ProcessInput(bool bActive) = 0;
	virtual bool        ShouldDrawDetailObjects() = 0;
	virtual bool        ShouldDrawEntity(C_BaseEntity *pEnt) = 0;
	virtual bool        ShouldDrawLocalPlayer(C_BaseEntity *pPlayer) = 0;
	virtual bool        ShouldDrawParticles() = 0;
	virtual bool        ShouldDrawFog(void) = 0;
	virtual void        OverrideView(CViewSetup *pSetup) = 0; // 19
	virtual int         KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0; // 20
	virtual void        StartMessageMode(int iMessageModeType) = 0; //21
	virtual IPanel*     GetMessagePanel() = 0; //22
	virtual void        OverrideMouseInput(float *x, float *y) = 0; //23
	virtual bool        CreateMove(float flSampleFrametime, void* pCmd) = 0; // 24
	virtual void        LevelInit(const char *newmap) = 0;
	virtual void        LevelShutdown(void) = 0;
};