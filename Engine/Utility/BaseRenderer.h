#pragma once
#include "Component.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "LightMgr.h"

BEGIN(Engine)
class CRenderer;

class ENGINE_DLL CBaseRenderer : public CComponent {
protected:
	explicit CBaseRenderer(LPDIRECT3DDEVICE9 _pGraphicDev);
	explicit CBaseRenderer(const CBaseRenderer& rhs);
	virtual ~CBaseRenderer();
public:
	virtual HRESULT Ready() PURE;
	virtual _int	Update(const _float& fTimeDelta) PURE;
	virtual void	Render() PURE;

public:
	virtual CComponent* Clone(void) PURE;
	virtual void Free(void) PURE;

public:
	virtual HRESULT		SetUp_ConstantTable(LPD3DXEFFECT& pEffect) { return S_OK; }
	virtual void		SetRenderInfo(CVIBuffer* _pBuffer, CTexture* _pTexture = nullptr, Engine::RENDERID _eRenderID = Engine::RENDERID::RENDER_NONALPHA);
public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pGraphicDev; }
	void			  SetDevice(LPDIRECT3DDEVICE9 _pGraphicDev) { m_pGraphicDev = _pGraphicDev; }
public:
	
	_float			Get_ViewZ(void) const { return m_fViewZ; }
	void			Compute_ViewZ(const _vec3* pPos);

	_ushort		GetBufferContainerIdx() { return bufferContainerIdx; }
	_tchar*		GetBufferTag() { return bufferTag; }
	_uint		GetTextureCnt()const { return textureCnt; }


	void		SetTextureContainerIdx(const _ushort& _idx) { textureContainerIdx = _idx; }
	void		SetBufferContainerIdx(const _ushort& _idx) { bufferContainerIdx = _idx; }
	void		SetTextureTag(const _tchar* _tag) { lstrcpy(textureTag, _tag); }
	void		SetBufferTag(const _tchar* _tag) { lstrcpy(bufferTag, _tag); }
	void		SetTextureCnt(const _uint& _Cnt) { textureCnt = _Cnt; }
	void		SetRenderID(const Engine::RENDERID& _eRenderID) { m_eRenderID = _eRenderID; }
	void		SetRenderInfo(
					const _tchar* _textureTag,
					const _tchar* _bufferTag,
					const _uint& _textureCnt = 0,
					const _ushort& _textureContainerIdx = RESOURCE_STATIC,
					const _ushort& _bufferContainerIdx = RESOURCE_STATIC,
					const Engine::RENDERID& _eRenderID = RENDER_NONALPHA);
	
	void		SetFillMode(const D3DFILLMODE& _fillmode) { m_eFillmode = _fillmode; }
protected:
	_bool		DrawOptimizationObject();
protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	CRenderer*			m_pRenderer{ nullptr };
	CVIBuffer*			m_pBuffer{ nullptr };
	CTexture*			m_pTexture{ nullptr };

	Engine::RENDERID	m_eRenderID;
	_ushort				textureContainerIdx;
	_ushort				bufferContainerIdx;
	_tchar				textureTag[64];
	_tchar				bufferTag[64];
	_uint				textureCnt{};
	D3DFILLMODE			m_eFillmode{ D3DFILL_SOLID };
	_float				m_fViewZ{ 0.f };

	// Shader 필요한 상수테이블 
	_matrix				m_matWorld, m_matView, m_matProj;
};
END