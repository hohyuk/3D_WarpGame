#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CProtoMgr : public CBase {
	DECLARE_SINGLETON(CProtoMgr)

private:
	explicit CProtoMgr(void);
	virtual ~CProtoMgr(void);

public:
	HRESULT			Ready_Proto(const _tchar* pProtoTag, CComponent* pInstance);
	CComponent* Clone(const _tchar* pProtoTag);

private:
	CComponent* Find_Proto(const _tchar* pProtoTag);
private:
	virtual void Free(void);
private:
	map<const _tchar*, CComponent*>			m_mapPrototype;
};

END