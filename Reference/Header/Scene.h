#pragma once
#include "Layer.h"

BEGIN(Engine)
class ENGINE_DLL CScene abstract : public CBase  {
public:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene();
public:
	CComponent* Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);
	CGameObject* Get_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag);
	CLayer* Get_Layer(const _tchar* pLayerTag);

public:
	virtual HRESULT Ready();
	virtual _int Update(const _float& fTimeDelta);
	virtual void Render();

	bool GetActive() { return m_bIsActive; };
	void SetActive(_bool _active) { m_bIsActive = _active; };

public:
	virtual void		Free(void);

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;
	map<const _tchar*, CLayer*>			m_mapLayer;

private:
	_bool m_bIsActive;
};

END