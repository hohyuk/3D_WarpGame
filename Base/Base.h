#pragma once

#pragma warning(disable : 26812)

class _declspec(dllexport) CBase
{
protected:
	inline explicit CBase();
	inline virtual ~CBase();

public:
	inline unsigned long	AddRef(void);
	inline unsigned long	Release(void);

private:
	unsigned long			m_dwRefCnt{};

public:
	inline virtual void		Free(void) = 0;
};

#include "Base.inl"