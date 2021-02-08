#include "Optimization.h"

USING(Engine)
COptimization::COptimization(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(),
	m_pGraphicDev{ pGraphicDev },
	m_pFrustum{ nullptr }
{
	Safe_AddRef(m_pGraphicDev);
}

COptimization::COptimization(const COptimization & rhs)
	: CComponent(rhs),
	m_pGraphicDev(rhs.m_pGraphicDev),
	m_pFrustum{ rhs.m_pFrustum }
{
	Safe_AddRef(m_pGraphicDev);
}

COptimization::~COptimization()
{
}

HRESULT COptimization::Ready_Optimization(const _ulong & dwCntX, const _ulong & dwCntZ)
{
	m_pFrustum = CFrustum::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pFrustum, E_FAIL);

	return S_OK;
}

_bool COptimization::Is_InFrustumForObject(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3 * pWorldPos, const _float & fRadius)
{
	return m_pFrustum->Is_InFrustumForObject(pGraphicDev, pWorldPos, fRadius);
}

void COptimization::Is_InFrustumForTerrain(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3 * pVtxPos, const _ulong & dwCntX, const _ulong & dwCntZ, Engine::INDEX32 * pIndex, _ulong * pTriCnt)
{
	m_pFrustum->Is_InFrustumForTerrain(pGraphicDev, pVtxPos, dwCntX, dwCntZ, pIndex, pTriCnt);
}

COptimization * COptimization::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong & dwCntX, const _ulong & dwCntZ)
{
	COptimization*		pInstance = new COptimization(pGraphicDev);

	if (FAILED(pInstance->Ready_Optimization(dwCntX, dwCntZ)))
		Safe_Release(pInstance);
	return pInstance;
}

CComponent * COptimization::Clone()
{
	return new COptimization(*this);
}

void COptimization::Free()
{
	if (false == m_bClone)
	{
		Safe_Release(m_pFrustum);
	}

	Safe_Release(m_pGraphicDev);
}
