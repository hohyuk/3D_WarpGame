#pragma once
#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CFrustum final : public CBase
{
private:
	explicit CFrustum(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFrustum(const CFrustum& rhs);
	virtual ~CFrustum();

public:
	LPDIRECT3DDEVICE9		Get_GraphicDev() { return m_pGraphicDev; }

public:
	HRESULT				Ready_Frustum();
	_bool				Is_InFrustumForObject(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* pWorldPos, const _float& fRadius);
	_bool				Is_InFrustum(const _vec3* pPos);
	_bool				Is_InFrustum(const _vec3* pPos, const _float& fRadius);
	void				Is_InFrustumForTerrain(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* pVtxPos,
											   const _ulong& dwCntX,
											   const _ulong& dwCntZ,
											   Engine::INDEX32* pIndex,
											   _ulong* pTriCnt);

public:
	static CFrustum*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void			Free();

private:
	_bool				MakeFrustumPlane(LPDIRECT3DDEVICE9& pGraphicDev);
private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	_vec3					m_vPoint[8];
	D3DXPLANE				m_Plane[6];
};

END