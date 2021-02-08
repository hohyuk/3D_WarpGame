#include "CameraManager.h"

USING(Engine)

CCameraManager* CCameraManager::m_pInstance = nullptr;

CCameraManager::CCameraManager(LPDIRECT3DDEVICE9 pGraphicDev) : 
	Engine::CGameObject(pGraphicDev)
{
}

CCameraManager::~CCameraManager()
{
	Free();
}

CCameraManager * CCameraManager::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	if (m_pInstance)
	{
		Engine::Safe_AddRef(m_pInstance);
		return m_pInstance;
	}
	else {
		m_pInstance = new CCameraManager(pGraphicDev);
		return m_pInstance;
	}
}

void CCameraManager::Free()
{
	Engine::CGameObject::Free();
}