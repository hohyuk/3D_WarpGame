#include "GameObject.h"
#include "ProtoMgr.h"
#include "Transform.h"
//#include "ColliderObject.h"
//#include "DynamicMesh.h"

BEGIN(Engine)
CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)	
	: 
	m_pGraphicDev(pGraphicDev) {
	Safe_AddRef(m_pGraphicDev);
}

CGameObject::~CGameObject() {
	for (_uint i = 0; i < ID_END; ++i) {
		for_each(m_mapComponent[i].begin(), m_mapComponent[i].end(), CDeleteMap());
		m_mapComponent[i].clear();
	}
}

HRESULT CGameObject::Ready(void) {

	m_pTransform = AddComponent<CTransform>();

	return S_OK;
}

_int CGameObject::Update(const _float& fTimeDelta) {
	for (const auto& comp : m_mapComponent[Engine::ID_DYNAMIC])
		if (comp.second->GetActive())
			comp.second->Update(fTimeDelta);
	for (const auto& child : m_vecChildren)
	{
		child->Update(fTimeDelta);
	}
		

	/*for (auto collider : m_vecCollider)
		collider->Update(fTimeDelta);*/

	//for (const auto& collider : m_mapCollider)
	//	collider.second->Update(fTimeDelta);
	return 0;
}

void CGameObject::SetValid(_bool _bIsValid)
{
	m_bIsValid = _bIsValid; 
	for (auto& child : m_vecChildren) 
		child->SetValid(m_bIsValid);
}

void CGameObject::SetActive(_bool _active)
{
	m_bIsActive = _active;

	for (auto& child : m_vecChildren)
		child->SetActive(m_bIsActive);
}

void CGameObject::SetParent(CGameObject* pGameObj) {
	m_pParent = pGameObj;
}

void CGameObject::AddChild(CGameObject* pGameObj, const _bool& bIsParentScale /*= true*/) {
	if (!pGameObj) return;

	pGameObj->SetParent(this);
	pGameObj->m_bIsParentScale = bIsParentScale;
	m_vecChildren.emplace_back(pGameObj);
}

_bool CGameObject::AddChild_Bone(CGameObject * pGameObj, const char * _pBoneName)
{
	//if (!pGameObj || pGameObj->GetParent())
	//	return false;

	//// 뼈이름이 이미 있으면 나가기
	//if (Find_BoneName(_pBoneName)) return false;

	//if (_pBoneName) {
	//	const _matrix* pBoneMatrixPointer = GetBoneMatrixPtr(_pBoneName);
	//	if (!pBoneMatrixPointer)
	//		return false;	// 본 행렬이 존재하지 않으면 기존 상태를 유지한다.
	//	else
	//		pGameObj->GetTransform()->SetParentBoneMatrix(pBoneMatrixPointer);
	//}
	//else
	//	pGameObj->GetTransform()->SetParentBoneMatrix(nullptr);

	//pGameObj->SetParent(this);
	//m_vecChildren.emplace_back(pGameObj);
	return true;
}

_bool CGameObject::AddCollider(CColliderObject * _pCollider, const char * _pBoneName)
{
	//if (!_pCollider || _pCollider->GetParent())
	//	return false;

	//// 뼈이름이 이미 있으면 나가기
	//if (Find_BoneName(_pBoneName)) return false;

	//if (_pBoneName) {
	//	const _matrix* pBoneMatrixPointer = GetBoneMatrixPtr(_pBoneName);
	//	if (!pBoneMatrixPointer)
	//		return false;	// 본 행렬이 존재하지 않으면 기존 상태를 유지한다.
	//	else
	//		_pCollider->GetTransform()->SetParentBoneMatrix(pBoneMatrixPointer);
	//}
	//else
	//	_pCollider->GetTransform()->SetParentBoneMatrix(nullptr);

	//m_mapCollider.emplace(_pBoneName, _pCollider);
	////m_vecCollider.emplace_back(_pCollider);
	//_pCollider->m_pParent = this;
	return true;
}

_bool CGameObject::DeleteCollider(const char * _pBoneName)
{
	if (!Find_BoneName(_pBoneName)) return false;

	//Engine::Safe_Release(m_mapCollider[_pBoneName]);
	//m_mapCollider.erase(_pBoneName);
	return true;
}

CColliderObject* CGameObject::GetCollider(const char * _pBoneName)
{
	if (!Find_BoneName(_pBoneName)) return nullptr;
	//return m_mapCollider[_pBoneName];
	return nullptr;
}

CGameObject* CGameObject::GetChild(_uint idx) const {
	if (m_vecChildren.size()) 
		return m_vecChildren[idx];
	else 
		return nullptr;
}

void CGameObject::ReleaseChild(const _uint& idx)
{
	if ((0 > idx || m_vecChildren.size() <= idx)) return;
	Safe_Release(m_vecChildren[idx]);
	m_vecChildren.erase(m_vecChildren.begin() + idx);
}

void CGameObject::ReleaseChild(CGameObject * _pChild)
{
	if (!_pChild)
		return;

	auto iter = find(m_vecChildren.begin(), m_vecChildren.end(), _pChild);

	if (iter == m_vecChildren.end()) return;

	_pChild->m_pParent = nullptr;
	//_pChild->GetTransform()->SetParentBoneMatrix(nullptr);

	m_vecChildren.erase(iter);
}

// 뼈행렬 포인터로 뽑아준다.
const _matrix * CGameObject::GetBoneMatrixPtr(const char* _pBoneName)
{
	/*if (!_pBoneName) return nullptr;

	CDynamicMesh* pPlayerMeshCom = GetComponent<CDynamicMesh>();
	NULL_CHECK_RETURN(pPlayerMeshCom, nullptr);

	
	const D3DXFRAME_DERIVED* pFrame = pPlayerMeshCom->Get_FrameByName(_pBoneName);
	NULL_CHECK_RETURN(pFrame, nullptr);

	return &(pFrame->CombinedTransformationMatrix);*/

	return nullptr;
}

_vec3 CGameObject::GetTransformCoordToParent() const
{
	if (!m_pTransform) return _vec3(0.f, 0.f, 0.f);
	/*if (!m_pParent)
		return m_pTransform->GetPosition();

	_vec3 vPos = m_pTransform->GetPosition();
	D3DXVec3TransformCoord(&vPos, &vPos, &m_pParent->GetTransform()->GetWorldMat());
	return vPos;*/
	return _vec3(0.f, 0.f, 0.f);
}

_bool CGameObject::Find_BoneName(const char * pBoneName)
{
	/*auto	iter = find_if(m_mapCollider.begin(),
		m_mapCollider.end(), Engine::CTag_FinderA(pBoneName));*/
	/*auto	iter = m_mapCollider.find(pBoneName);
	if (iter == m_mapCollider.end())
		return false;
*/
	return true;
}

CComponent* CGameObject::AddComponent(const _tchar* pComponentTag) {
	for (_uint i = 0; i < ID_END; ++i) {
		auto iter = find_if(m_mapComponent[i].begin(), m_mapComponent[i].end(), CTag_Finder(pComponentTag));

		if (iter != m_mapComponent[i].end())
			return nullptr;
	}
	/*CComponent* pComp = CProtoMgr::GetInstance()->Clone(pComponentTag);
	if (pComp) {
		pComp->SetOwner(this);
		m_mapComponent[pComp->m_eCompID].emplace(pComponentTag, pComp);
		return pComp;
	}*/
	return nullptr;
}
CComponent* CGameObject::GetComponent(const _tchar* pComponentTag) {
	for (_uint i = 0; i < ID_END; ++i) {
		auto	iter = find_if(m_mapComponent[i].begin(), m_mapComponent[i].end(), CTag_Finder(pComponentTag));

		if (iter == m_mapComponent[i].end())
			continue;

		return iter->second;
	}
	return nullptr;
}

CGameObject* CGameObject::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CGameObject* pGameObject = nullptr;
	pGameObject = new CGameObject(pGraphicDev);
	pGameObject->Ready();
	return pGameObject;
}

void CGameObject::Free(void) {
	for (_uint i = 0; i < ID_END; ++i) {
		for_each(m_mapComponent[i].begin(), m_mapComponent[i].end(), CDeleteMap());
		m_mapComponent[i].clear();
	}
	for (auto& child : m_vecChildren)
		Safe_Release(child);

	/*for_each(m_mapCollider.begin(), m_mapCollider.end(), CDeleteMap());
	m_mapCollider.clear();
*/
	Safe_Release(m_pGraphicDev);
}

END