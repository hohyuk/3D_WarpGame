#pragma once
#include "Engine_Define.h"
#include "Base.h"
#include "Layer.h"

BEGIN(Engine)
class CLayer;
class CComponent;
class CTransform;
class COptimization;
class CColliderObject;
class CShader;
class ENGINE_DLL CGameObject : public CBase{
	// ������, �Ҹ���
public:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameObject();

	// ����, �Ҹ� �Լ�
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

	// ���� �Լ�
public:
	virtual HRESULT Ready();
	virtual _int	Update(const _float& fTimeDelta);
	virtual void	OnCollision(CollisionInfo _tCollisionInfo) {}

	virtual void	SaveData(HANDLE & hFile) {}
	virtual void	LoadData(HANDLE & hFile) {}
	// Shader
	virtual HRESULT SetUp_ConstantTable(LPD3DXEFFECT & pEffect) { return S_OK; }

	// public �Լ�, ����
public:
	LPDIRECT3DDEVICE9& GetGraphicDev() { return m_pGraphicDev; }

	CLayer* GetLayer() const { return m_pLayer; }
	void	SetLayer(CLayer* _pLayer) { m_pLayer = _pLayer; }

	_bool	IsValid() const { return m_bIsValid; }
	void	SetValid(_bool _bIsValid);

	_bool	IsActive() const { return m_bIsActive; }
	void	SetActive(_bool _active);


	CGameObject* GetParent() const  { return m_pParent; }
	void		 SetParent(CGameObject* pGameObj);
	
	void		 AddChild(CGameObject* pGameObj, const _bool& bIsParentScale = true);
	_bool		 AddChild_Bone(CGameObject* pGameObj, const char* _pBoneName);

	_bool		 AddCollider(CColliderObject* _pCollider, const char* _pBoneName = nullptr);
	_bool		 DeleteCollider(const char* _pBoneName = nullptr);

	CColliderObject*	GetCollider(const char* _pBoneName);
	//map<string, CColliderObject*>& GetColliderList() { return m_mapCollider; }

	CGameObject* GetChild(_uint idx = 0) const;
	vector<CGameObject*>* GetChildren() { return &m_vecChildren; }
	void ReleaseChild(const _uint& idx);
	void ReleaseChild(CGameObject* _pChild);
	const _matrix* GetBoneMatrixPtr(const char* _pBoneName);


	_bool ApplyParentScaleMat()const { return m_bIsParentScale; }
	
	void	SetGroggyOn(const _bool& bIsGroggyOn) { m_bIsGroggyOn = bIsGroggyOn; }
	_bool	IsGroggy()const { return m_bIsGroggyOn; }

	_bool	GetTargetOn()const { return m_bIsTargetOn; }

	_bool IsEventOn()const { return m_bIsEventOn; }
	void SetEventOn(const _bool& bEvent = true) { m_bIsEventOn = bEvent; }

	_int GetEventTagValue()const { return m_iEventValue; }
	void SetEventTagValue(const _int& _EventVal) { m_iEventValue = _EventVal; }
	// �θ� �������ִ� ����� ���� ��ġ ��ǥ ��ȯ
	_vec3	GetTransformCoordToParent() const;

	// �⺻ Components
	CTransform* GetTransform() { return m_pTransform; }
	COptimization* GetOptimization() { return m_pOptimization; }
	CShader* GetShader() { return m_pShader; }
private:
	_bool Find_BoneName(const char* pBoneName);
	// protected �Լ�, ����
protected:
	LPDIRECT3DDEVICE9 m_pGraphicDev;

	CLayer* m_pLayer = nullptr;

	CGameObject* m_pParent = nullptr;
	vector<CGameObject*> m_vecChildren;
	//map<string, CColliderObject*> m_mapCollider;
	DWORD				m_dwByte{};

	_bool	m_bIsValid{ true };			// ������Ʈ ���� ��/��
	_bool	m_bIsActive{ true };		// Ȱ��ȭ ��/��
protected:
	_bool			m_bIsParentScale{ true };
	_bool			m_bIsGroggyOn{ false };			// �÷��̾�� ħ�� ���ߴ��� �ȴ��ߴ��� Ư�� ������Ʈ�� ���
	_bool			m_bIsTargetOn{ false };			// Player�� Ÿ�����Ҽ��ִ���
	_bool			m_bIsEventOn{ false };
	_int			m_iEventValue{ EVENT_NONE };

	// private �Լ�, ����
private:

	// Component �Լ�
public:
	CComponent* GetComponent(const _tchar* pComponentTag);
	CComponent* AddComponent(const _tchar* pComponentTag);
	template <class T>
	T* GetComponent() {
		const _tchar* tag = T::GetComponentTag();
		return static_cast<T*>(GetComponent(tag));
	}
	template <class T>
	T* AddComponent() {
		const _tchar* tag = T::GetComponentTag();
		return static_cast<T*>(AddComponent(tag));
	}

protected:
	map<const _tchar*, CComponent*>	m_mapComponent[ID_END];

	// �⺻ Components
protected:
	CTransform*					m_pTransform{ nullptr };
	COptimization*				m_pOptimization{ nullptr };
	CShader*					m_pShader{ nullptr };
};
END
