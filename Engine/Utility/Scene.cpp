#include "Scene.h"

BEGIN(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev) 
	: m_pGraphicDev(pGraphicDev)
	, m_bIsActive(false) 
{
	Safe_AddRef(m_pGraphicDev);
}

CScene::~CScene() 
{
}

CComponent* CScene::Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID) {
	auto	iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		return nullptr;

	return iter->second->Find(pObjTag)->GetComponent(pComponentTag);
}

CGameObject* CScene::Get_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag) {
	auto	iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		return nullptr;

	return iter->second->Find(pObjTag);
}
CLayer* CScene::Get_Layer(const _tchar* pLayerTag) {
	auto	iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		return nullptr;

	return iter->second;
}

HRESULT CScene::Ready() {
	return S_OK;
}

_int CScene::Update(const _float& fTimeDelta) {

	_int iExit = 0;

	for (auto& iter : m_mapLayer) {
		iExit = iter.second->Update(fTimeDelta);

		if (iExit & 0x80000000) {
			MSG_BOX("Layer Problem");
			return iExit;
		}
	}

	return iExit;
}

void CScene::Render() 
{

}

void CScene::Free(void) {
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();
	Safe_Release(m_pGraphicDev);
}

END 