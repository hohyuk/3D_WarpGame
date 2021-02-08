#include "BaseRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Optimization.h"

BEGIN(Engine)

CBaseRenderer::CBaseRenderer(LPDIRECT3DDEVICE9 _pGraphicDev)
	:
	CComponent(), 
	m_pGraphicDev(_pGraphicDev),
	m_pRenderer{ nullptr },
	m_pBuffer{ nullptr },
	m_pTexture{ nullptr },
    textureContainerIdx(Engine::RESOURCE_STATIC),
    bufferContainerIdx(Engine::RESOURCE_STATIC),
    textureCnt(0),
	m_eRenderID(Engine::RENDERID::RENDER_NONALPHA) {
	lstrcpy(textureTag, L"");
	lstrcpy(bufferTag, L"");

}

CBaseRenderer::CBaseRenderer(const CBaseRenderer& rhs) 
	:
	CComponent(rhs),
	m_pGraphicDev(rhs.m_pGraphicDev),
    textureContainerIdx(rhs.textureContainerIdx),
    bufferContainerIdx(rhs.bufferContainerIdx),
    textureCnt(rhs.textureCnt),
    m_eRenderID(rhs.m_eRenderID){
    lstrcpy(textureTag, rhs.textureTag);
    lstrcpy(bufferTag, rhs.bufferTag);

}

CBaseRenderer::~CBaseRenderer() {

}

void CBaseRenderer::SetRenderInfo(CVIBuffer * _pBuffer, CTexture * _pTexture, Engine::RENDERID _eRenderID)
{
	m_pBuffer = _pBuffer;
	m_pTexture = _pTexture;
	m_eRenderID = _eRenderID;
}

void CBaseRenderer::Compute_ViewZ(const _vec3 * pPos)
{
	_matrix		matCamWorld;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);

	D3DXMatrixInverse(&matCamWorld, NULL, &matCamWorld);

	_vec3	vCamPos;
	memcpy(&vCamPos, &matCamWorld.m[3][0], sizeof(_vec3));

	m_fViewZ = D3DXVec3Length(&(vCamPos - *pPos));
}

void CBaseRenderer::SetRenderInfo(
    const _tchar* _textureTag,
    const _tchar* _bufferTag,
    const _uint& _textureCnt,
    const _ushort& _textureContainerIdx,
    const _ushort& _bufferContainerIdx,
    const Engine::RENDERID& _eRenderID)
{
    textureContainerIdx = _textureContainerIdx;
    bufferContainerIdx = _bufferContainerIdx;
    lstrcpy(textureTag, _textureTag);
    lstrcpy(bufferTag, _bufferTag);
    textureCnt = _textureCnt;
    m_eRenderID = _eRenderID;
}

_bool CBaseRenderer::DrawOptimizationObject()
{
	// 최적화
	bool bDraw = true;		// True 그리기, False 그리지 않기
	if (m_pGameObject && m_pGameObject->GetOptimization())
	{
		COptimization* optimization = m_pGameObject->GetOptimization();

		// 부모행렬이 존재한다면
		if (m_pGameObject->GetParent())
		{
			_vec3 Pos = m_pGameObject->GetTransform()->GetPosition();
			_matrix ParentMat = m_pGameObject->GetParent()->GetTransform()->GetWorldMat();
			D3DXVec3TransformCoord(&Pos, &Pos, &ParentMat);
			bDraw = optimization->Is_InFrustumForObject(m_pGraphicDev, &Pos, 0);
		}
		else
		{
			bDraw = optimization->Is_InFrustumForObject(m_pGraphicDev, &m_pGameObject->GetTransform()->GetPosition(), 0);
		}
	}

	return bDraw;
}

END
