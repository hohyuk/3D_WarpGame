#pragma once
#include "Engine_Define.h"
#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)
class ENGINE_DLL CLayer : public CBase {
	typedef map<const _tchar*, CGameObject*> LayerMap;
	typedef list<CGameObject*> LayerList;
public:
	explicit CLayer();
	virtual ~CLayer();
public:
	HRESULT		Ready();
	_int		Update(const _float& fTimeDelta);
	void		Render();

	CGameObject* Find(const _tchar* gameObjectTag);
	template<typename T>
	list<T*> Finds(){
		list<T*> listObj;
		for (auto obj : m_ObjectsList) {
			if (typeid(*obj) == typeid(T))
				listObj.emplace_back((T*)obj);
		}
		return listObj;
	}
	LayerMap&	GetLayerMap() { return m_mapObject; }
	LayerList&	GetLayerList() { return m_ObjectsList; }
	HRESULT		Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);
	HRESULT		Add_GameObject(CGameObject* pGameObject);
public:
	static CLayer* Create(void);
	virtual void   Free(void);

public:
	bool GetActive() { return m_bIsActive; };
	void SetActive(_bool _active) { m_bIsActive = _active; };

private:
	LayerMap		m_mapObject;
	LayerList		m_ObjectsList;

	_bool			m_bIsActive;

};

END
