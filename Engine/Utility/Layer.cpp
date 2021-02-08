#include "Layer.h"

USING(Engine)

CLayer::CLayer() : m_bIsActive(true) {

}

CLayer::~CLayer() {

}

HRESULT CLayer::Ready() {
	return S_OK;
}

_int CLayer::Update(const _float& fTimeDelta) {
	_int iExit = 0;

	//for (auto& iter : m_mapObject) {
	//	iExit = iter.second->Update(fTimeDelta);

	//	if (iExit & 0x80000000) {
	//		MSG_BOX("GameObject Problem");
	//		return iExit;
	//	}
	//}

	//for (auto& iter : m_ObjectsList) {
	//	iExit = iter->Update(fTimeDelta);

	//	if (iExit & 0x80000000) {
	//		MSG_BOX("GameObject Problem");
	//		return iExit;
	//	}
	//}

	for (auto iter = m_mapObject.begin(); iter != m_mapObject.end(); ) {
		iExit = iter->second->Update(fTimeDelta);
		if (iExit == 1) {
			Safe_Release(iter->second);
			iter = m_mapObject.erase(iter);
		}
		else {
			iter++;
		}
		if (iExit & 0x80000000) {
			MSG_BOX("GameObject Problem");
			return iExit;
		}
	}

	for (auto iter = m_ObjectsList.begin(); iter != m_ObjectsList.end(); ) {

		iExit = (*iter)->Update(fTimeDelta);
		if (iExit == 1) {
			Safe_Release(*iter);
			iter = m_ObjectsList.erase(iter);
		}
		else {
			iter++;
		}

		if (iExit & 0x80000000) {
			MSG_BOX("GameObject Problem");
			return iExit;
		}
	}

	return iExit;
}

void CLayer::Render() {
	//for (auto& iter : m_mapObject)
	//	iter.second->Render();

	//for (auto& iter : m_ObjectsList) {
	//	iter->Render();
	//}
}

CGameObject* CLayer::Find(const _tchar* gameObjectTag) {
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(gameObjectTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second;
}

HRESULT CLayer::Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject) {
	if (nullptr == pGameObject)
		return E_FAIL;

	pGameObject->SetLayer(this);
	m_mapObject.emplace(pObjTag, pGameObject);

	return S_OK;
}

HRESULT CLayer::Add_GameObject(CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	pGameObject->SetLayer(this);
	m_ObjectsList.emplace_back(pGameObject);

	return S_OK;
}

CLayer* CLayer::Create(void) {

	CLayer* pInstance = new CLayer;

	if (FAILED(pInstance->Ready()))
		Safe_Release(pInstance);

	return pInstance;
}

void CLayer::Free(void) {
	for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();
	for_each(m_ObjectsList.begin(), m_ObjectsList.end(), CDeleteObj());
	m_ObjectsList.clear();
}