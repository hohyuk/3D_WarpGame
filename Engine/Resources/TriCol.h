#ifndef TriCol_h__
#define TriCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTriCol : public CVIBuffer
{
protected:
	explicit CTriCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTriCol(const CTriCol& rhs);
	virtual ~CTriCol();

public:
	virtual HRESULT	Ready_Buffer();

public:
	static const _tchar* GetComponentTag() { return L"TriCol"; }
	static CTriCol*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone() override;
	virtual void Free();
};
END

#endif // TriCol_h__
