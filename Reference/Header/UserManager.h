#pragma once

#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL CUserManager
{
	DECLARE_SINGLETON(CUserManager)
private:
	explicit CUserManager();
	~CUserManager();

public:
	enum ID { STATICMESH_COLLIDER, DYNAMIC_COLLIDER, NAVIDRAW, DEBUG_TEXT, GAME_OVER, RENDER_TARGET, END_ID };
public:
	void KeyInputDebug();

public:
	_bool IsStaticMeshColliderShowOn() const { return m_bIsMode[STATICMESH_COLLIDER]; }
	_bool IsDynamicMeshColliderShowOn() const { return m_bIsMode[DYNAMIC_COLLIDER]; }
	_bool IsNaviMeshDrawOn() const { return m_bIsMode[NAVIDRAW]; }
	_bool IsRenderTargetOn()const { return m_bIsMode[RENDER_TARGET]; }
	_bool IsDebugTextOn()const { return m_bIsMode[DEBUG_TEXT]; }

	void SetDynamicMeshColliderShowOn(_bool pFlag = true) { m_bIsMode[DYNAMIC_COLLIDER] = pFlag; }
	void SetRenderTarget(_bool pFlag = true) { m_bIsMode[RENDER_TARGET] = pFlag; }

	void SetDebugText(_bool pFlag = true) { m_bIsMode[DEBUG_TEXT] = pFlag; }

	void SetTestIntValue(const _int& value) { m_iTestValue = value; }
	_int GetTestIntValue()const { return m_iTestValue; }

	_bool IsClientModeOn()const { return m_bIsClientMode; }
	void SetClientModeOn(const _bool& ClientMode =true) { m_bIsClientMode = ClientMode; }
private:
	_bool m_bIsMode[END_ID]{ false };
	_bool m_bIsClientMode{ false };		// false -> MFC
	_int m_iTestValue{};
};

END
