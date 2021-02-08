#pragma once
#include "Engine_Define.h"
#include "BaseRenderer.h"

BEGIN(Engine)
class CTerrainTex;

class ENGINE_DLL CTerrainRenderer : public Engine::CBaseRenderer {
protected:
	explicit CTerrainRenderer(LPDIRECT3DDEVICE9 _pGraphicDev);
	explicit CTerrainRenderer(const CTerrainRenderer& rhs);
	virtual ~CTerrainRenderer();

public:
	virtual HRESULT Ready();
	virtual _int	Update(const _float& fTimeDelta);
	virtual void	Render();
public:
	void		SetMaterial(const D3DMATERIAL9& _material) { material = _material; }
	
	CTerrainTex* GetTerrainBuffer() const;

	void		AdjustTerrainBuffer(const _ulong & dwCntX, const _ulong & dwCntZ, const _ulong & dwVtxItv, const _float& fDetailX, const _float & fDetailZ);

public:
	static const _tchar* GetComponentTag() { return L"TerrainRenderer"; }
	static CTerrainRenderer* Create(Engine::CGameObject* const _gameObject, LPDIRECT3DDEVICE9 _pGraphicDev = nullptr);
	virtual CComponent* Clone() override;
	virtual void Free() override;
private:
	virtual HRESULT		SetUp_ConstantTable(LPD3DXEFFECT& pEffect);
protected:
	INDEX32*			m_pIndex{ nullptr };
	_ulong				m_dwTriCnt = 0;
	D3DMATERIAL9		material;
};

END