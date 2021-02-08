#pragma once

#include "Engine_Define.h"
#include "GameObject.h"

BEGIN(Engine)
class ENGINE_DLL CCameraManager final : public CGameObject
{
private:
	explicit CCameraManager(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCameraManager();

public:
	enum ID { STATICMESH_COLLIDER, DYNAMIC_COLLIDER, NEXT_PORTAL, GAME_STOP, GAME_OVER, END_ID };


public:
	CCameraManager* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free() override;

public:
	static CCameraManager*	GetInstance() { return m_pInstance; }
private:
	static CCameraManager* m_pInstance;
};

END
