#include "Timer.h"

USING(Engine)

Engine::CTimer::CTimer(void)
	: m_fTimeDelta(0.f)
{

}

Engine::CTimer::~CTimer(void)
{

}

HRESULT Engine::CTimer::Ready_Timer(void)
{

	m_FrameT = chrono::steady_clock::now();
	m_LastT = chrono::steady_clock::now();

	/*QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceCounter(&m_FixTime);

	QueryPerformanceFrequency(&m_CpuTick);*/

	return S_OK;
}

void Engine::CTimer::SetUp_TimeDelta(void)
{
	m_FrameT = chrono::steady_clock::now();

	chrono::duration<_float> fTimeDelta = m_FrameT - m_LastT;

	m_fTimeDelta = fTimeDelta.count();

	m_LastT = m_FrameT;

	//QueryPerformanceCounter(&m_FrameTime);
	//
	//if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	//{
	//   QueryPerformanceFrequency(&m_CpuTick);
	//   m_FixTime = m_FrameTime;
	//}

	//m_fTimeDelta = (_float(m_FrameTime.QuadPart) - _float(m_LastTime.QuadPart)) / (_float)m_CpuTick.QuadPart;


	//m_LastTime = m_FrameTime;
}

void	Engine::CTimer::Reset_TimeDelta() {
	m_FrameT = chrono::steady_clock::now();
	m_LastT = chrono::steady_clock::now();
	m_fTimeDelta = 0.f;
}

Engine::CTimer* Engine::CTimer::Create(void)
{
	CTimer*   pInstance = new CTimer;

	if (FAILED(pInstance->Ready_Timer()))
		Safe_Release(pInstance);

	return pInstance;
}

void Engine::CTimer::Free(void)
{

}




