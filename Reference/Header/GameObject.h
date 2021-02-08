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
	// 생성자, 소멸자
public:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameObject();

	// 생성, 소멸 함수
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

	// 가상 함수
public:
	virtual HRESULT Ready();
	virtual _int	Update(const _float& fTimeDelta);
	virtual void	OnCollision(CollisionInfo _tCollisionInfo) {}

	virtual void	SaveData(HANDLE & hFile) {}
	virtual void	LoadData(HANDLE & hFile) {}
	// Shader
	virtual HRESULT SetUp_ConstantTable(LPD3DXEFFECT & pEffect) { return S_OK; }

	// public 함수, 변수
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
	// 부모가 가지고있는 행렬을 통해 위치 좌표 변환
	_vec3	GetTransformCoordToParent() const;

	// 기본 Components
	CTransform* GetTransform() { return m_pTransform; }
	COptimization* GetOptimization() { return m_pOptimization; }
	CShader* GetShader() { return m_pShader; }
private:
	_bool Find_BoneName(const char* pBoneName);
	// protected 함수, 변수
protected:
	LPDIRECT3DDEVICE9 m_pGraphicDev;

	CLayer* m_pLayer = nullptr;

	CGameObject* m_pParent = nullptr;
	vector<CGameObject*> m_vecChildren;
	//map<string, CColliderObject*> m_mapCollider;
	DWORD				m_dwByte{};

	_bool	m_bIsValid{ true };			// 오브젝트 삭제 유/무
	_bool	m_bIsActive{ true };		// 활성화 유/무
protected:
	_bool			m_bIsParentScale{ true };
	_bool			m_bIsGroggyOn{ false };			// 플레이어에게 침투 당했는지 안당했는지 특정 오브젝트만 사용
	_bool			m_bIsTargetOn{ false };			// Player가 타겟팅할수있는지
	_bool			m_bIsEventOn{ false };
	_int			m_iEventValue{ EVENT_NONE };

	// private 함수, 변수
private:

	// Component 함수
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

	// 기본 Components
protected:
	CTransform*					m_pTransform{ nullptr };
	COptimization*				m_pOptimization{ nullptr };
	CShader*					m_pShader{ nullptr };
};
END
