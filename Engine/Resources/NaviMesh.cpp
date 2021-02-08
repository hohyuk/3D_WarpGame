#include "NaviMesh.h"
USING(Engine)

Engine::CNaviMesh::CNaviMesh(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMesh(pGraphicDev)
	/*, m_dwIndex(0)*/
{

}

Engine::CNaviMesh::CNaviMesh(const CNaviMesh& rhs)
	: CMesh(rhs)
	, m_vecCell(rhs.m_vecCell)
	/*, m_dwIndex(rhs.m_dwIndex)*/
{
	for (auto& iter : m_vecCell)
		Safe_AddRef(iter);
}

Engine::CNaviMesh::~CNaviMesh(void)
{

}

HRESULT Engine::CNaviMesh::Ready_NaviMeshes(void)
{
	//m_vecCell.reserve(4);

	//CCell*		pCell = nullptr;

	//// 0번 
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(0.f, 0.f, 2.f), &_vec3(2.f, 0.f, 0.f), &_vec3(0.f, 0.f, 0.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//// 1번 
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(0.f, 0.f, 2.f), &_vec3(2.f, 0.f, 2.f), &_vec3(2.f, 0.f, 0.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//// 2번 
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(0.f, 0.f, 4.f), &_vec3(2.f, 0.f, 2.f), &_vec3(0.f, 0.f, 2.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//// 3번 
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(2.f, 0.f, 2.f), &_vec3(4.f, 0.f, 0.f), &_vec3(2.f, 0.f, 0.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//FAILED_CHECK_RETURN(Link_Cell(), E_FAIL);

	return S_OK;
}

void CNaviMesh::Render_Meshes(void)
{
	for (auto& iter : m_vecCell)
		iter->Render_Cell();
}

_vec3 CNaviMesh::Move_OnNaviMesh(_ulong& _dwIndex, const _vec3 * pTargetPos, const _vec3 * pTargetDir)
{
	_vec3		vEndPos = *pTargetPos + *pTargetDir;

	if (CCell::MOVE == m_vecCell[_dwIndex]->CompareCell(&vEndPos, &_dwIndex))
	{
		vEndPos.y = m_vecCell[_dwIndex]->Get_Height(vEndPos);
		return vEndPos;
	}
	else if (CCell::STOP == m_vecCell[_dwIndex]->CompareCell(&vEndPos, &_dwIndex))
	{
		_vec3 vCorrectedPos;
		vCorrectedPos = m_vecCell[_dwIndex]->Get_PosInCell(vEndPos);
		vCorrectedPos.y = m_vecCell[_dwIndex]->Get_Height(vCorrectedPos);

		_vec3 vTemp;
		vTemp = GetReflectionVector((*pTargetDir)*5.f, *D3DXVec3Normalize(&vTemp, &_vec3(vCorrectedPos.x - vEndPos.x, 0.f, vCorrectedPos.z - vEndPos.z)), 1.1f);
		
		return _vec3(vCorrectedPos + (m_vecCell[_dwIndex]->GetCenterPoint() - vCorrectedPos) * 0.004f);
	}
	return *pTargetPos;
}

_bool CNaviMesh::Warp_OnNaviMesh(_ulong& _dwIndex, _vec3& pWarpPos)
{
	if (!IsChange_IndexCell(_dwIndex, pWarpPos)) return false;

	_vec3		vEndPos = pWarpPos;
	if (CCell::MOVE == m_vecCell[_dwIndex]->CompareCell(&vEndPos, &_dwIndex))
	{
		vEndPos.y = m_vecCell[_dwIndex]->Get_Height(vEndPos);
		pWarpPos = vEndPos;
		return true;
	}
	else if (CCell::STOP == m_vecCell[_dwIndex]->CompareCell(&pWarpPos, &_dwIndex))
	{
		return false;
	}
	
	return false;
}

_bool CNaviMesh::EnemyMove_OnNaviMesh(_ulong & _dwIndex, _vec3 * pTargetPos, const _vec3 * pTargetDir)
{
	_vec3		vEndPos = *pTargetPos + *pTargetDir;

	if (CCell::MOVE == m_vecCell[_dwIndex]->CompareCell(&vEndPos, &_dwIndex))
	{
		*pTargetPos = vEndPos;
		return true;
	}
	else if (CCell::STOP == m_vecCell[_dwIndex]->CompareCell(&vEndPos, &_dwIndex))
	{
		_vec3 a = *pTargetPos;
		_vec3 b = vEndPos;
		return false;
	}
		
	return false;
}

void CNaviMesh::Reserve(const _int & size)
{
	m_vecCell.reserve(size);
}

_bool CNaviMesh::Add_NaviCell(const _vec3 & v1, const _vec3 & v2, const _vec3 & v3)
{
	CCell*		pCell = nullptr;

	pCell = CCell::Create(m_pGraphicDev, static_cast<_int>(m_vecCell.size()), &v1, &v2, &v3);
	NULL_CHECK_RETURN(pCell, false);
	m_vecCell.push_back(pCell);
	FAILED_CHECK_RETURN(Link_Cell(), false);

	return true;
}

void CNaviMesh::DeleteNaviCell(const _int & _index)
{
	if (0 > _index || m_vecCell.size() <= _index) return;
	
	Safe_Release(m_vecCell[_index]);
	m_vecCell.erase(m_vecCell.begin() + _index);

	FAILED_CHECK_RETURN(Link_Cell(),);
}

void CNaviMesh::AdjustVertexPos(const _vec3& vPos, const _int& _CurCell_Index, const _int& _CellVertex_Index)
{
	if (0 > _CurCell_Index || m_vecCell.size() <= _CurCell_Index) return;

	m_vecCell[_CurCell_Index]->Set_Pos(_CellVertex_Index, vPos);
}

void CNaviMesh::ClearCell()
{
	for_each(m_vecCell.begin(), m_vecCell.end(), CDeleteObj());
	m_vecCell.clear();
}

_ulong CNaviMesh::Find_Cell_Index(_ulong& _dwIndex, const _vec3 & _vTargetPos)
{
	_int size = static_cast<int>(m_vecCell.size());

	for (_int i = 0; i < size; ++i) {
		if (m_vecCell[i]->IsCollide(_vTargetPos)) {
			_dwIndex = i;
			return _dwIndex;
		}
	}

	return _dwIndex;
}

_bool CNaviMesh::IsChange_IndexCell(_ulong & _dwIndex, const _vec3 & _vTargetPos)
{
	_int size = static_cast<int>(m_vecCell.size());

	for (_int i = 0; i < size; ++i) {
		if (m_vecCell[i]->IsCollide(_vTargetPos)) {
			_dwIndex = i;
			return true;
		}
	}

	return false;
}

HRESULT Engine::CNaviMesh::Link_Cell(void)
{
	for (_ulong i = 0; i < m_vecCell.size(); ++i)
	{
		for (_ulong j = 0; j < m_vecCell.size(); ++j)
		{
			if (i == j)
				continue;

			if (nullptr == m_vecCell[i]->Get_Neighbor(CCell::NEIGHBOR_AB) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(CCell::POINT_A),
					m_vecCell[i]->Get_Point(CCell::POINT_B),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(CCell::NEIGHBOR_AB, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(CCell::NEIGHBOR_BC) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(CCell::POINT_B),
					m_vecCell[i]->Get_Point(CCell::POINT_C),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(CCell::NEIGHBOR_BC, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(CCell::NEIGHBOR_CA) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(CCell::POINT_C),
					m_vecCell[i]->Get_Point(CCell::POINT_A),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(CCell::NEIGHBOR_CA, m_vecCell[j]);
				continue;
			}

		}
	}

	return S_OK;
}

Engine::CNaviMesh* Engine::CNaviMesh::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNaviMesh*		pInstance = new CNaviMesh(pGraphicDev);

	if (FAILED(pInstance->Ready_NaviMeshes()))
		Safe_Release(pInstance);

	return pInstance;
}

Engine::CComponent* Engine::CNaviMesh::Clone(void)
{
	return new CNaviMesh(*this);
}

void Engine::CNaviMesh::Free(void)
{
	for_each(m_vecCell.begin(), m_vecCell.end(), CDeleteObj());
	m_vecCell.clear();

	CMesh::Free();
}

