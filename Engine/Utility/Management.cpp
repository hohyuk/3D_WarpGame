#include "Export_Utility.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement(void) : m_pScene(nullptr) {
}

CManagement::~CManagement(void) {
	Free();
}


Engine::CComponent* Engine::CManagement::Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID) 
{
	if (nullptr == m_pScene)
		return nullptr;

	return m_pScene->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}

CGameObject* CManagement::Get_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag) 
{
	if (nullptr == m_pScene)
		return nullptr;

	return m_pScene->Get_GameObject(pLayerTag, pObjTag);
}

CLayer* CManagement::Get_Layer(const _tchar* pLayerTag) 
{
	return m_pScene->Get_Layer(pLayerTag);
}

HRESULT Engine::CManagement::SetUp_Scene(CScene* pScene) 
{
	Safe_Release(m_pScene); 

	m_pScene = pScene;

	return S_OK;
}

Engine::_int Engine::CManagement::Update_Scene(const _float& fTimeDelta) 
{
	if (nullptr == m_pScene)
		return -1;

	m_pScene->Update(fTimeDelta);

	return 0;
}

void Engine::CManagement::Render_Scene(LPDIRECT3DDEVICE9 & pGraphicDev) 
{
	//Get_Renderer()->Render_GameObject(pGraphicDev);

	if (nullptr == m_pScene)
		return;

	m_pScene->Render();
}

void Engine::CManagement::Free(void) 
{
	Safe_Release(m_pScene);
}
