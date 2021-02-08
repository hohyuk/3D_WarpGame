#include "RcCol.h"

USING(Engine)
Engine::CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CRcCol::CRcCol(const CRcCol& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CRcCol::~CRcCol()
{

}

HRESULT Engine::CRcCol::Ready_Buffer()
{
	m_dwFVF = FVF_COL;
	m_dwTriCnt = 2;
	m_dwVtxCnt = 4;
	m_dwVtxSize = sizeof(VTXCOL);

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);


	VTXCOL* pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);
	// 1인자 : 어디서부터 잠글 것인가
	// 2인자 : 숫자가 0이면 전체 영역을 잠근다.
	// 3인자 : 인자값을 통해서 버텍스 버퍼 내 정점 중 첫번째 주소를 얻어온다.
	// 4인자 : 잠그는 형태를 묻는 인자, 정적 버퍼인 경우 0

	pVertex[0].vPos = _vec3(-1.f, 1.f, 0.f);
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPos = _vec3(1.f, 1.f, 0.f);
	pVertex[1].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	pVertex[2].vPos = _vec3(1.f, -1.f, 0.f);
	pVertex[2].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
	
	pVertex[3].vPos = _vec3(-1.f, -1.f, 0.f);
	pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 1.f, 1.f);

	m_pVB->Unlock();

	INDEX16* index16 = nullptr;

	m_pIB->Lock(0, 0, (void**)&index16, 0);

	index16[0] = { 0, 1, 2 };
	index16[1] = { 0, 2, 3 };

	// 위와 같음
	/*
	pIndex[0]._0 = 0; pIndex[0]._1 = 1; pIndex[0]._2 = 2;

	pIndex[1]._0 = 0; pIndex[1]._1 = 2; pIndex[1]._2 = 3;
	*/
	m_pIB->Unlock();

	return S_OK;
}


Engine::CRcCol* Engine::CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcCol*	pInstance = new CRcCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

Engine::CComponent* CRcCol::Clone() {
	return new CRcCol(*this);
}

void Engine::CRcCol::Free()
{
	CVIBuffer::Free();
}

