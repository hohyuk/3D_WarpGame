#include "Component.h"

BEGIN(Engine)
CComponent::CComponent() :
	m_isActive(true),
	m_pGameObject(nullptr),
	m_eCompID(ID_STATIC),
	m_bClone(false)
{

}
CComponent::CComponent(const CComponent& component) :
	m_isActive(true),
	m_pGameObject(nullptr),
	m_eCompID(component.m_eCompID),
	m_bClone(true)
{
}
CComponent::~CComponent() {

}
_int CComponent::Update(const _float& fTimeDelta) {
	return 0;
}
CComponent* CComponent::GetComponent(const _tchar* pComponentTag) {
	if (m_pGameObject == nullptr)
		return nullptr;
	return m_pGameObject->GetComponent(pComponentTag);
}

void CComponent::Free(void) {
	//Safe_Release(m_pGameObject);
}

END