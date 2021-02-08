#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Utility.h"

USING(Engine)
IMPLEMENT_SINGLETON(CRenderer)

Engine::CRenderer::CRenderer(void)
{

}

Engine::CRenderer::~CRenderer(void)
{

}

HRESULT CRenderer::Ready_Renderer(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	FAILED_CHECK_RETURN(pGraphicDev->CreateVertexBuffer(sizeof(VTXSCREEN) * 4,
		0, // 정적버퍼로 할당하겠다는 옵션
		FVF_SCREEN,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL),
		E_FAIL);

	FAILED_CHECK_RETURN(pGraphicDev->CreateIndexBuffer(sizeof(INDEX16) * 2,
		0, // 정적버퍼로 할당하겠다는 옵션
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIB,
		NULL),
		E_FAIL);

	D3DVIEWPORT9		ViewPort;
	pGraphicDev->GetViewport(&ViewPort);

	VTXSCREEN*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);

	// 오른쪽 위
	pVertex[0].vPos = _vec4(0.f - 0.5f, 0.f - 0.5f, 0.f, 1.f);
	pVertex[0].vTexUV = _vec2(0.f, 0.f);

	pVertex[1].vPos = _vec4(ViewPort.Width - 0.5f, 0.f - 0.5f, 0.f, 1.f);
	pVertex[1].vTexUV = _vec2(1.f, 0.f);

	pVertex[2].vPos = _vec4(ViewPort.Width - 0.5f, ViewPort.Height - 0.5f, 0.f, 1.f);
	pVertex[2].vTexUV = _vec2(1.f, 1.f);

	pVertex[3].vPos = _vec4(0.f - 0.5f, ViewPort.Height - 0.5f, 0.f, 1.f);
	pVertex[3].vTexUV = _vec2(0.f, 1.f);

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CRenderer::Add_RenderGroup(RENDERID eGroup, CBaseRenderer* pRenderer)
{
	if (RENDER_END <= eGroup)
		return;

	m_RenderGroup[eGroup].push_back(pRenderer);
	Safe_AddRef(pRenderer);
}

void Engine::CRenderer::Render_GameObject(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	if (CUserManager::GetInstance()->IsClientModeOn())
	{
		Render_Priority(pGraphicDev);

		Render_NonAlpha(pGraphicDev);

		Render_Deferred(pGraphicDev);
		Render_OutLine(pGraphicDev);
		Render_LightAcc(pGraphicDev);

		Render_Blend(pGraphicDev);
		Render_OutLineBlend(pGraphicDev);

		Render_Alpha(pGraphicDev);
		Render_UI(pGraphicDev);

		if (CUserManager::GetInstance()->IsRenderTargetOn())
		{
			Render_DebugBuffer(L"MRT_Deferred");
			Render_DebugBuffer(L"MRT_LightAcc");
			Render_DebugBuffer(L"MRT_OutLine");
		}

		Clear_RenderGroup();
	}
	else
	{
		// MFC용
		for (_uint i = 0; i < RENDER_END; ++i)
		{
			if (i == RENDER_ALPHA && !m_RenderGroup[RENDER_ALPHA].empty()) {
				LPDIRECT3DDEVICE9 pDevice = m_RenderGroup[RENDER_ALPHA].front()->GetDevice();
				pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

				for (auto& iter : m_RenderGroup[i]) {
					iter->Render();
					Safe_Release(iter);
				}
				m_RenderGroup[i].clear();

				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
				pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
				//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
				pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			}
			else {
				for (auto& iter : m_RenderGroup[i]) {
					iter->Render();
					Safe_Release(iter);
				}
				m_RenderGroup[i].clear();
			}
		}
	}
}

void Engine::CRenderer::Clear_RenderGroup(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Render_Priority(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (auto& iter : m_RenderGroup[RENDER_PRIORITY]) 
		iter->Render();
	
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

_bool	Compare_ViewZ(CBaseRenderer* pDest, CBaseRenderer* pSrc)
{
	return pDest->Get_ViewZ() > pSrc->Get_ViewZ();
}

void CRenderer::Render_NonAlpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA]) 
		iter->Render();	
}

void CRenderer::Render_NonAlpha_Shader(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	m_RenderGroup[RENDER_NONALPHA_SHADER].sort(Compare_ViewZ);
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA_SHADER])
		iter->Render();

	// Glass
	m_RenderGroup[RENDER_GLASS].sort(Compare_ViewZ);
	for (auto& iter : m_RenderGroup[RENDER_GLASS])
		iter->Render();
}

void CRenderer::Render_Alpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

	m_RenderGroup[RENDER_ALPHA].sort(Compare_ViewZ);

	for (auto& iter : m_RenderGroup[RENDER_ALPHA])
		iter->Render();

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

void CRenderer::Render_UI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_UI])
		iter->Render();

	for (auto& iter : m_RenderGroup[RENDER_FADE_INOUT])
		iter->Render();
}

void CRenderer::Render_Deferred(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	Begin_MRT(L"MRT_Deferred");
	Render_NonAlpha_Shader(pGraphicDev);
	End_MRT(L"MRT_Deferred");
}

void CRenderer::Render_OutLine(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	Begin_MRT(L"MRT_OutLine");
	m_RenderGroup[RENDER_NONALPHA_OUTLINE].sort(Compare_ViewZ);
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA_OUTLINE])
		iter->Render();
	End_MRT(L"MRT_OutLine");
}

void CRenderer::Render_LightAcc(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	Begin_MRT(L"MRT_LightAcc");

	CShader*	pShader = dynamic_cast<Engine::CShader*>(Engine::Clone(L"Proto_Shader_Shade"));
	
	NULL_CHECK(pShader);

	LPD3DXEFFECT pEffect = pShader->Get_EffectHandle();// 빛 출력을 위한 쉐이더 파일이 필요하다.
	Safe_AddRef(pEffect);

	Engine::Throw_RenderTargetTexture(pEffect, L"Target_Normal", "g_NormalTexture");
	Engine::Throw_RenderTargetTexture(pEffect, L"Target_Depth", "g_DepthTexture");

	pEffect->Begin(NULL, 0);

	Engine::Render_Light(pEffect);

	pEffect->End();

	End_MRT(L"MRT_LightAcc");

	Safe_Release(pEffect);
	Safe_Release(pShader);
}

void CRenderer::Render_Blend(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	CShader*		pShader = dynamic_cast<Engine::CShader*>(Engine::Clone(L"Proto_Shader_Blend"));
	NULL_CHECK(pShader);

	LPD3DXEFFECT pEffect = pShader->Get_EffectHandle();
	Safe_AddRef(pEffect);

	Engine::Throw_RenderTargetTexture(pEffect, L"Target_Albedo", "g_AlbedoTexture");
	Engine::Throw_RenderTargetTexture(pEffect, L"Target_Shade", "g_ShadeTexture");
	Engine::Throw_RenderTargetTexture(pEffect, L"Target_Specular", "g_SpecularTexture");

	//Engine::Throw_RenderTargetTexture(pEffect, L"Target_OutLineExpansion", "g_OutLineTexture");

	pEffect->Begin(NULL, 0);
	pEffect->BeginPass(0);

	pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTXSCREEN));
	pGraphicDev->SetFVF(FVF_SCREEN);
	pGraphicDev->SetIndices(m_pIB);
	pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);
	Safe_Release(pShader);
}

void CRenderer::Render_OutLineBlend(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	CShader*		pShader = dynamic_cast<Engine::CShader*>(Engine::Clone(L"Proto_Shader_OutLine"));
	NULL_CHECK(pShader);

	LPD3DXEFFECT pEffect = pShader->Get_EffectHandle();
	Safe_AddRef(pEffect);

	Engine::Throw_RenderTargetTexture(pEffect, L"Target_OutLineExpansion", "g_OutLineTexture");
	Engine::Throw_RenderTargetTexture(pEffect, L"Target_Shade", "g_ShadeTexture");

	pEffect->Begin(NULL, 0);
	pEffect->BeginPass(0);

	pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTXSCREEN));
	pGraphicDev->SetFVF(FVF_SCREEN);
	pGraphicDev->SetIndices(m_pIB);
	pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);
	Safe_Release(pShader);
}

void Engine::CRenderer::Free(void)
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);

	Clear_RenderGroup();
}

