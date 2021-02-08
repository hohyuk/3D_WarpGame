#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CResources : public CComponent 
{
protected:
	explicit CResources(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CResources(const CResources& rhs);
	virtual ~CResources();

public:
	virtual void		Free();

protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
};

END

