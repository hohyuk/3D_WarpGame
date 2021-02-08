#pragma once

#include "Component.h"
#include "Frustum.h"

BEGIN(Engine)

class ENGINE_DLL COptimization final : public CComponent
{
private:
	explicit COptimization(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit COptimization(const COptimization& rhs);
	virtual ~COptimization();

public:
	HRESULT				Ready_Optimization(const _ulong& dwCntX, const _ulong& dwCntZ);
	_bool				Is_InFrustumForObject(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* pWorldPos, const _float& fRadius);
	void				Is_InFrustumForTerrain(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* pVtxPos,
												const _ulong& dwCntX,
												const _ulong& dwCntZ,
												Engine::INDEX32* pIndex,
												_ulong* pTriCnt);

public:
	static const _tchar* GetComponentTag() { return L"Optimization"; }
	static COptimization*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ);
	virtual CComponent*				Clone() override;
	virtual void					Free() override;

private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	CFrustum*			m_pFrustum;
};

END