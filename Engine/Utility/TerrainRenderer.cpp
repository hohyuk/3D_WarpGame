#include "TerrainRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Export_Resouces.h"
#include "Optimization.h"
#include "Shader.h"

USING(Engine)
CTerrainRenderer::CTerrainRenderer(LPDIRECT3DDEVICE9 _pGraphicDev) :
    Engine::CBaseRenderer(_pGraphicDev)
{
    ZeroMemory(&material, sizeof(D3DMATERIAL9));
}

CTerrainRenderer::CTerrainRenderer(const CTerrainRenderer& rhs) :
    Engine::CBaseRenderer(rhs),
    material(rhs.material),
	m_pIndex{rhs.m_pIndex}
{
    m_pRenderer = CRenderer::GetInstance();
    Engine::Safe_AddRef(m_pRenderer);
}

CTerrainRenderer::~CTerrainRenderer() {

}

HRESULT CTerrainRenderer::Ready() {
    m_pRenderer = CRenderer::GetInstance();
    Engine::Safe_AddRef(m_pRenderer);
    return S_OK;
}

_int CTerrainRenderer::Update(const _float& fTimeDelta) {
    m_pRenderer->Add_RenderGroup(m_eRenderID, this);
    return 0;
}

void CTerrainRenderer::Render() {
	// 최적화
	if (m_pGameObject && m_pGameObject->GetOptimization())
	{
		Engine::COptimization* optimization = m_pGameObject->GetOptimization();

		optimization->Is_InFrustumForTerrain(m_pGraphicDev, GetTerrainBuffer()->Get_VtxPos(),
											 GetTerrainBuffer()->Get_VtxCntX(),
											 GetTerrainBuffer()->Get_VtxCntZ(),
											 m_pIndex,
											 &m_dwTriCnt);

		GetTerrainBuffer()->Copy_Indices(m_pIndex, m_dwTriCnt);
	}

    if (m_pGameObject && m_pGameObject->GetTransform()) {
        m_pGameObject->GetTransform()->SetTransform(m_pGraphicDev);
    }
  
	// 쉐이더가 존재할경우
	if (m_pGameObject && m_pGameObject->GetShader())
	{
		LPD3DXEFFECT pEffect = m_pGameObject->GetShader()->Get_EffectHandle();
		NULL_CHECK(pEffect);
		Safe_AddRef(pEffect);

		_uint	iMaxPass = 0;

		pEffect->Begin(&iMaxPass, 0);	
		pEffect->BeginPass(0);

		FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

		GetTerrainBuffer()->Render_Buffer();

		pEffect->EndPass();
		pEffect->End();

		Safe_Release(pEffect);
	}
	else
	{
		if (material.Diffuse.a != 0.f)
		{
			m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
			m_pGraphicDev->SetMaterial(&material);
		}

		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, m_eFillmode);
		//Engine::Render_Texture(textureContainerIdx, textureTag, textureCnt);
		if (m_pTexture)
			m_pTexture->Render_Texture(textureCnt);
		else
			m_pGraphicDev->SetTexture(0, NULL);

		GetTerrainBuffer()->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
}

CTerrainTex * CTerrainRenderer::GetTerrainBuffer() const
{
	return dynamic_cast<CTerrainTex*>(m_pBuffer);
}

void CTerrainRenderer::AdjustTerrainBuffer(const _ulong & dwCntX, const _ulong & dwCntZ, const _ulong & dwVtxItv, const _float & fDetailX, const _float & fDetailZ)
{
	GetTerrainBuffer()->SetInfo(dwCntX, dwCntZ, dwVtxItv, fDetailX, fDetailZ);

	m_pIndex = new INDEX32[GetTerrainBuffer()->Get_TriCnt()];
}

HRESULT CTerrainRenderer::SetUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	m_matWorld = m_pGameObject->GetTransform()->GetWorldMat();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &m_matProj);

	pEffect->SetMatrix("g_matWorld", &m_matWorld);
	pEffect->SetMatrix("g_matView", &m_matView);
	pEffect->SetMatrix("g_matProj", &m_matProj);

	m_pTexture->Set_Texture(pEffect, "g_BaseTexture", textureCnt);

	/*const D3DLIGHT9*		pLightInfo = Engine::CLightMgr::GetInstance()->Get_Light(0);

	pEffect->SetVector("g_vLightDir", &_vec4(pLightInfo->Direction, 0.f));

	pEffect->SetVector("g_LightDiffuse", (_vec4*)&pLightInfo->Diffuse);
	pEffect->SetVector("g_LightSpecular", (_vec4*)&pLightInfo->Specular);
	pEffect->SetVector("g_LightAmbient", (_vec4*)&pLightInfo->Ambient);

	D3DMATERIAL9			tMtrlInfo;
	ZeroMemory(&tMtrlInfo, sizeof(D3DMATERIAL9));

	tMtrlInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f);
	tMtrlInfo.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	tMtrlInfo.Power = 1.f;

	pEffect->SetVector("g_MtrlDiffuse", (_vec4*)&tMtrlInfo.Diffuse);
	pEffect->SetVector("g_MtrlSpecular", (_vec4*)&tMtrlInfo.Specular);
	pEffect->SetVector("g_MtrlAmbient", (_vec4*)&tMtrlInfo.Ambient);

	pEffect->SetFloat("g_fPower", tMtrlInfo.Power);

	D3DXMatrixInverse(&m_matView, NULL, &m_matView);

	_vec4	vCamPos;
	memcpy(&vCamPos, &m_matView.m[3][0], sizeof(_vec4));

	pEffect->SetVector("g_vCamPos", &vCamPos);*/
	FAILED_CHECK_RETURN(m_pGameObject->SetUp_ConstantTable(pEffect), E_FAIL);
	pEffect->CommitChanges();
	return S_OK;
}

Engine::CTerrainRenderer* CTerrainRenderer::Create(Engine::CGameObject* const _gameObject, LPDIRECT3DDEVICE9 _pGraphicDev /*= nullptr*/) {
	CTerrainRenderer* pInstance = nullptr;
    pInstance = new CTerrainRenderer(_pGraphicDev);
    if (pInstance == nullptr)
        return nullptr;
    pInstance->m_pGameObject = _gameObject;
    pInstance->m_eCompID = Engine::ID_DYNAMIC;
    ((CTerrainRenderer*)pInstance)->Ready();
    return pInstance;
}

Engine::CComponent* CTerrainRenderer::Clone(void) 
{
    return new CTerrainRenderer(*this);
}

void CTerrainRenderer::Free(void) 
{
	Safe_Delete_Array(m_pIndex);
}
