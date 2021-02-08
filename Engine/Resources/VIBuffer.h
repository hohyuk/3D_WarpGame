#ifndef VIBuffer_h__
#define VIBuffer_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer : public CResources {
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer();

public:
	virtual HRESULT	Ready_Buffer();
	virtual void	Render_Buffer();

public:
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuffer(void) { return m_pVB; }
	LPDIRECT3DINDEXBUFFER9	GetIdxBuffer(void) { return m_pIB; }
	_ulong					Get_TriCnt() const { return m_dwTriCnt; }

public:
	virtual void Free();

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;

	_ulong						m_dwVtxCnt;
	_ulong						m_dwTriCnt;
	_ulong						m_dwVtxSize;
	_ulong						m_dwFVF;

	_ulong						m_dwIdxSize;
	D3DFORMAT					m_IdxFmt;
};

END
#endif // VIBuffer_h__
