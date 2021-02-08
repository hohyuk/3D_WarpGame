#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
protected:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTex(const CTerrainTex& rhs);
	virtual ~CTerrainTex();

public:
	_vec3*		Get_VtxPos()const { return m_pPos; }

	_ulong		Get_VtxCntX() const { return m_dwCntX; }
	_ulong		Get_VtxCntZ() const { return m_dwCntZ; }

	_ulong		Get_VtxItv()const { return m_dwVtxItv; }
	_float		Get_DetailX()const { return m_fDetailX; }
	_float		Get_DetailZ()const { return m_fDetailZ; }

	void		Copy_Indices(INDEX32* pIndex, const _ulong& dwTriCnt);
public:
	HRESULT	Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	
	void	SetInfo(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv = 1, const _float& fDetailX = 20.f, const _float & fDetailZ = 20.f);

public:
	static const _tchar* GetComponentTag() { return L"TerrainTex"; }
	static CTerrainTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual CComponent*	Clone();
	virtual void Free();

protected:
	HANDLE				m_hFile;
	BITMAPFILEHEADER	m_fH;
	BITMAPINFOHEADER	m_iH;
	_vec3*				m_pPos;

	_ulong				m_dwCntX;
	_ulong				m_dwCntZ;

	_ulong				m_dwVtxItv;
	_float				m_fDetailX{ 20.f };
	_float				m_fDetailZ{ 20.f };
};
END

#endif // TerrainTex_h__
