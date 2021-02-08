#ifndef Renderer_h__
#define Renderer_h__

#include "Component.h"
#include "BaseRenderer.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer : public CComponent
{
	DECLARE_SINGLETON(CRenderer)

private:
	explicit CRenderer(void);
	virtual ~CRenderer(void);

public:
	HRESULT	Ready_Renderer(LPDIRECT3DDEVICE9& pGraphicDev);
	void	Add_RenderGroup(RENDERID eGroup, CBaseRenderer* pRenderer);
	void	Render_GameObject(LPDIRECT3DDEVICE9 & pGraphicDev);
	list<CBaseRenderer*>* GetRenderGroup(RENDERID eGroup){ return &m_RenderGroup[eGroup];}
	void	Clear_RenderGroup(void);

private:
	void		Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_NonAlpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_NonAlpha_Shader(LPDIRECT3DDEVICE9& pGraphicDev);

	void		Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_UI(LPDIRECT3DDEVICE9& pGraphicDev);

	void		Render_Deferred(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_OutLine(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_LightAcc(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_Blend(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_OutLineBlend(LPDIRECT3DDEVICE9& pGraphicDev);

private:
	list<CBaseRenderer*>				m_RenderGroup[RENDER_END];
	LPDIRECT3DVERTEXBUFFER9				m_pVB;
	LPDIRECT3DINDEXBUFFER9				m_pIB;
private:
	virtual CComponent*	Clone() { return nullptr; }
	virtual void Free(void);
};

END
#endif // Renderer_h__
