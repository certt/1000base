#pragma once

class C_BaseCombatWeapon;

class C_BaseEntity
{
private:
	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
public:
	bool GetLifeState()
	{
		static int m_lifeState = g_pNetvars->GetOffset("DT_BasePlayer", "m_lifeState");
		return GetValue<bool>(m_lifeState);
	}

	int GetHealth()
	{
		static int m_iHealth = g_pNetvars->GetOffset("DT_BasePlayer", "m_iHealth");
		return GetValue<int>(m_iHealth);
	}

	Vector GetOrigin()
	{
		static int m_vecOrigin = g_pNetvars->GetOffset("DT_BaseEntity", "m_vecOrigin");
		return GetValue<Vector>(m_vecOrigin);
	}

	EntityFlags GetFlags()
	{
		static int m_fFlags = g_pNetvars->GetOffset("DT_BasePlayer", "m_fFlags");
		return GetValue<EntityFlags>(m_fFlags);
	}
};


class C_BaseCombatWeapon : public C_BaseEntity
{
private:

public:

};

struct SpatializationInfo_t;
class IClientEntity
{
public:
	virtual void             Release(void) = 0;
	virtual const Vector     GetAbsOrigin(void) const = 0;
	virtual const QAngle     GetAbsAngles(void) const = 0;
	virtual void*            GetMouth(void) = 0;
	virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
	virtual bool             IsBlurred(void) = 0;
};

class IClientEntityList
{
public:
	virtual IClientNetworkable*   GetClientNetworkable(int entnum) = 0;
	virtual void*                 vtablepad0x1(void) = 0;
	virtual void*                 vtablepad0x2(void) = 0;
	virtual C_BaseEntity*         GetClientEntity(int entNum) = 0;
	virtual IClientEntity*        GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
	virtual void                  SetMaxEntities(int maxEnts) = 0;
	virtual int                   GetMaxEntities() = 0;
};