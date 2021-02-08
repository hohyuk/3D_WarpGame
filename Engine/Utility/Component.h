#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class ENGINE_DLL CComponent abstract : public CBase {
protected:
	explicit CComponent();
	explicit CComponent(const CComponent& component);
	virtual ~CComponent();
public:
	virtual _int Update(const _float& fTimeDelta);
	CGameObject* GetGameObject() { return m_pGameObject; }
	CTransform*  GetTransform() { return m_pGameObject->GetTransform(); }
	CComponent*  GetComponent(const _tchar* pComponentTag);
	template <class T>
	T* GetComponent() {
		return dynamic_cast<T*>(GetComponent(T::GetComponentTag()));
	}
	_bool GetActive() { return m_isActive; }
	void  SetActive(_bool _active) { m_isActive = _active; }
	virtual void SetOwner(CGameObject* pOwner) { m_pGameObject = pOwner; }
public:
	virtual CComponent* Clone(void) PURE;
	virtual void Free(void);

protected:
	COMPONENTID		m_eCompID;
	CGameObject*	m_pGameObject;
	_bool			m_isActive;
	_bool			m_bClone;
};
END