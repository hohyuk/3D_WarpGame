#include "Frustum.h"

USING(Engine)

CFrustum::CFrustum(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	Safe_AddRef(m_pGraphicDev);
}

CFrustum::CFrustum(const CFrustum & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev)
{
	for (_uint i = 0; i < 6; ++i)
		m_Plane[i] = rhs.m_Plane[i];

	for (_uint i = 0; i < 8; ++i)
		m_vPoint[i] = rhs.m_vPoint[i];

	Safe_AddRef(m_pGraphicDev);
}

CFrustum::~CFrustum(void)
{
}

HRESULT CFrustum::Ready_Frustum()
{
	m_vPoint[0] = _vec3(-1.f, 1.f, 0.f);
	m_vPoint[1] = _vec3(1.f, 1.f, 0.f);
	m_vPoint[2] = _vec3(1.f, -1.f, 0.f);
	m_vPoint[3] = _vec3(-1.f, -1.f, 0.f);

	m_vPoint[4] = _vec3(-1.f, 1.f, 1.f);
	m_vPoint[5] = _vec3(1.f, 1.f, 1.f);
	m_vPoint[6] = _vec3(1.f, -1.f, 1.f);
	m_vPoint[7] = _vec3(-1.f, -1.f, 1.f);

	return S_OK;
}

_bool CFrustum::Is_InFrustumForObject(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3 * pWorldPos, const _float & fRadius)
{
	FAILED_CHECK_RETURN(MakeFrustumPlane(pGraphicDev), false);

	return Is_InFrustum(pWorldPos, fRadius);
}

_bool CFrustum::Is_InFrustum(const _vec3 * pPos)
{
	_float		fResult = 0.f;

	for (_uint i = 0; i < 6; ++i)
	{
		fResult = D3DXPlaneDotCoord(&m_Plane[i], pPos);

		// 결과값이 < 0 면이 후방에 있음.
		// ==  0 같은 면에 있음
		// > 0 면의 정방에 있음
		if (fResult > 0.f)
			return false;
	}

	return true;
}

_bool CFrustum::Is_InFrustum(const _vec3 * pPos, const _float & fRadius)
{
	_float		fResult = 0.f;

	for (_uint i = 0; i < 6; ++i)
	{
		fResult = D3DXPlaneDotCoord(&m_Plane[i], pPos);

		if (fResult > fRadius)
			return false;
	}

	return true;
}

void CFrustum::Is_InFrustumForTerrain(LPDIRECT3DDEVICE9 & pGraphicDev, const _vec3 * pVtxPos, const _ulong & dwCntX, const _ulong & dwCntZ, Engine::INDEX32 * pIndex, _ulong * pTriCnt)
{
	MakeFrustumPlane(pGraphicDev);

	// 화면안에 들어온 삼각형을 카운트하기 위해 0으로 해준다.
	*pTriCnt = 0;

	_bool	bIsIn[3] = { false };
	_ulong dwTriCnt = 0;

	for (_ulong i = 0; i < dwCntZ - 1; ++i)
	{
		for (_ulong j = 0; j < dwCntX - 1; ++j)
		{
			_ulong dwIndex = i * dwCntX + j;

			// 오른쪽 위 삼각형 중 정점 하나라도 절두체와 충돌했는지 검사
			bIsIn[0] = Is_InFrustum(&pVtxPos[dwIndex + dwCntX]);
			bIsIn[1] = Is_InFrustum(&pVtxPos[dwIndex + dwCntX + 1]);
			bIsIn[2] = Is_InFrustum(&pVtxPos[dwIndex + 1]);

			if (true == bIsIn[0] || true == bIsIn[1] || true == bIsIn[2])
			{
				pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
				pIndex[dwTriCnt]._1 = dwIndex + dwCntX + 1;
				pIndex[dwTriCnt]._2 = dwIndex + 1;
				++dwTriCnt;
			}

			// 왼쪽 아래 삼각형 중 정점 하나라도 절두체와 충돌했는지 검사
			bIsIn[0] = Is_InFrustum(&pVtxPos[dwIndex + dwCntX]);
			bIsIn[1] = Is_InFrustum(&pVtxPos[dwIndex + 1]);
			bIsIn[2] = Is_InFrustum(&pVtxPos[dwIndex]);

			if (true == bIsIn[0] || true == bIsIn[1] || true == bIsIn[2])
			{
				pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
				pIndex[dwTriCnt]._1 = dwIndex + 1;
				pIndex[dwTriCnt]._2 = dwIndex;
				++dwTriCnt;
			}
		}
	}

	*pTriCnt = dwTriCnt;
}

CFrustum * CFrustum::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFrustum*	pInstance = new CFrustum(pGraphicDev);

	if (FAILED(pInstance->Ready_Frustum()))
		Safe_Release(pInstance);

	return pInstance;
}

void CFrustum::Free()
{
	Safe_Release(m_pGraphicDev);
}

_bool CFrustum::MakeFrustumPlane(LPDIRECT3DDEVICE9& pGraphicDev)
{
	FAILED_CHECK_RETURN(Ready_Frustum(), false);

	_matrix		matProj, matView;
	pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXMatrixInverse(&matView, NULL, &matView);

	for (_uint i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matProj);
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matView);
	}

	// D3DXPlaneFromPoints
	// 3개의 점으로부터 평면을 생성하는 함수

	//x+
	D3DXPlaneFromPoints(&m_Plane[0], &m_vPoint[1], &m_vPoint[5], &m_vPoint[6]);

	//x-
	D3DXPlaneFromPoints(&m_Plane[1], &m_vPoint[4], &m_vPoint[0], &m_vPoint[3]);

	//y+
	D3DXPlaneFromPoints(&m_Plane[2], &m_vPoint[4], &m_vPoint[5], &m_vPoint[1]);

	//y-
	D3DXPlaneFromPoints(&m_Plane[3], &m_vPoint[3], &m_vPoint[2], &m_vPoint[6]);

	//z+
	D3DXPlaneFromPoints(&m_Plane[4], &m_vPoint[7], &m_vPoint[6], &m_vPoint[5]);

	//z-
	D3DXPlaneFromPoints(&m_Plane[5], &m_vPoint[0], &m_vPoint[1], &m_vPoint[2]);

	return true;
}
