#ifndef CubeTex_h__
#define CubeTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeTex : public CVIBuffer
{
protected:
	explicit CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCubeTex(const CCubeTex& rhs);
	virtual ~CCubeTex();

public:
	virtual HRESULT	Ready_Buffer();

public:
	static const _tchar* GetComponentTag() { return L"CubeTex"; }
	static CCubeTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone();
	virtual void Free();
};
END

#endif // CubeTex_h__
