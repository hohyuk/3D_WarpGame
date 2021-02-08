#include "NaviTriCol.h"

USING(Engine)
Engine::CNaviTriCol::CNaviTriCol(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CNaviTriCol::CNaviTriCol(const CNaviTriCol& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CNaviTriCol::~CNaviTriCol(void)
{

}

HRESULT Engine::CNaviTriCol::Ready_Buffer(void)
{
	m_vVertices.reserve(3 * 100);	// 삼각형 정점 3개 * 갯수

	m_dwFVF = FVF_COL;
	m_dwTriCnt = m_dwVtxCnt = 0;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;
	
	return S_OK;
}

HRESULT CNaviTriCol::Ready_Buffer(const _vec3 & v1, const _vec3 & v2, const _vec3 & v3)
{
	m_dwFVF = FVF_COL;
	m_dwTriCnt = 1;
	m_dwVtxCnt = 3;
	m_dwVtxSize = sizeof(VTXCOL);

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL*		pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);
	
	pVertex[0].vPos = v1;
	pVertex[0].dwColor = D3DXCOLOR(0.f, 0.5f, 1.f, 1.f);

	pVertex[1].vPos = v2;
	pVertex[1].dwColor = D3DXCOLOR(0.f, 0.5f, 1.f, 1.f);

	pVertex[2].vPos = v3;
	pVertex[2].dwColor = D3DXCOLOR(0.f, 0.5f, 1.f, 1.f);

	m_pVB->Unlock();

	INDEX16* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	m_pIB->Unlock();
	return S_OK;
}

void CNaviTriCol::PushTriVertices(const _vec3 & v1, const _vec3 & v2, const _vec3 & v3)
{
	// 삼각형 벡터에 넣기
	m_vVertices.emplace_back(v1);
	m_vVertices.emplace_back(v2);
	m_vVertices.emplace_back(v3);

	MakeTriBuffer();
}

_bool CNaviTriCol::PopTriIndex(const _int& _index)
{
	if (!IsValidTriIndex(_index)) return false;

	for (_int i = 0; i < 3; ++i) 
		m_vVertices.erase(m_vVertices.begin() + 3 * _index);		// 제거
	
	if (!MakeTriBuffer()) return false;

	return true;
}

_bool CNaviTriCol::IsValidVertexIndex(const _int& _index)
{
	return !(_index < 0 || _index >= 3);
}

_bool CNaviTriCol::IsValidTriIndex(const _int& _index)
{
	return !(_index < 0 || _index >= static_cast<_int>(m_vVertices.size() / 3));
}

void CNaviTriCol::ChangeColor(const _int & _index, const D3DXCOLOR & _color)
{
	if (!IsValidTriIndex(_index)) return;

	VTXCOL*		pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);

	for (_int i = 0; i < 3; ++i) 
		pVertex[(3 * _index) + i].dwColor = _color;
	
	m_pVB->Unlock();
}

void CNaviTriCol::AdjustVertexPos(const _int & _index, const _vec3 & vPos)
{
	//if (!IsValidTriIndex(_index)) return;
	m_vVertices[_index] = vPos;
	MakeTriBuffer();
}

void CNaviTriCol::LoadNaviMesh(const vector<_vec3>& _vLoadVertex)
{
	// 기존에 있는 vector를 지운다
	m_vVertices.clear();
	m_vVertices.assign(_vLoadVertex.begin(), _vLoadVertex.end());

	MakeTriBuffer();
}

void CNaviTriCol::ClearVertex()
{
	m_vVertices.clear();
	MakeTriBuffer();
}

CNaviTriCol * CNaviTriCol::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & v1, const _vec3 & v2, const _vec3 & v3)
{
	CNaviTriCol*	pInstance = new CNaviTriCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(v1, v2, v3)))
		Safe_Release(pInstance);

	return pInstance;
}

Engine::CNaviTriCol* Engine::CNaviTriCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNaviTriCol*	pInstance = new CNaviTriCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

Engine::CComponent* CNaviTriCol::Clone(void) {
	return new CNaviTriCol(*this);
}

void Engine::CNaviTriCol::Free(void)
{
	m_vVertices.clear();
	m_vVertices.shrink_to_fit();
	CVIBuffer::Free();
}

_bool CNaviTriCol::MakeTriBuffer()
{
	// 기존 버퍼 삭제
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

	// 삼각형 갯수 및 정점 갯수 
	m_dwVtxCnt = static_cast<_ulong>(m_vVertices.size());
	m_dwTriCnt = m_dwVtxCnt / 3;

	// 삼각형이 없다면 나가기
	if (0 == m_dwTriCnt) return false;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), false);

	// 정점 만들기
	VTXCOL*		pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);

	for (_int i = 0; i < (_int)m_dwVtxCnt; ++i) {
		pVertex[i].vPos = m_vVertices[i];
		pVertex[i].dwColor = D3DXCOLOR(0.f, 0.5f, 1.f, 1.f);
	}
	m_pVB->Unlock();

	// 삼각형 만들기
	INDEX16*	pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	for (_int i = 0; i < (_int)m_dwTriCnt; ++i) {
		pIndex[i]._0 = i * 3;
		pIndex[i]._1 = i * 3 + 1;
		pIndex[i]._2 = i * 3 + 2;
	}
	m_pIB->Unlock();

	return true;
}

