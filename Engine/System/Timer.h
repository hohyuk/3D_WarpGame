#ifndef Timer_h__
#define Timer_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)


class ENGINE_DLL CTimer : public CBase
{
private:
	explicit CTimer(void);
	virtual ~CTimer(void);

public:
	_float      Get_TimeDelta(void) { return m_fTimeDelta; }

public:
	HRESULT      Ready_Timer(void);
	void      SetUp_TimeDelta(void);

	void		Reset_TimeDelta();
private:
	//LARGE_INTEGER      m_FrameTime;
	//LARGE_INTEGER      m_FixTime;
	//LARGE_INTEGER      m_LastTime;
	//LARGE_INTEGER      m_CpuTick;
	chrono::steady_clock::time_point m_FrameT;
	chrono::steady_clock::time_point m_LastT;

private:
	_float            m_fTimeDelta;

public:
	static   CTimer*      Create(void);
	virtual void      Free(void);
};

END
#endif // Timer_h__
