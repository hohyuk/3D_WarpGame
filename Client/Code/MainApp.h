#pragma once

#include "Export_Function.h"

class CMainApp : public CBase
{
private: // 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

	// 생성, 소멸 함수
public:
	static CMainApp*	Create();
	virtual void		Free();

	// public 함수, 변수
public:
	HRESULT		Ready();
	_int		Update(const _float& fTimeDelta);
	void		Render();

private:
	HRESULT			SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT			Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagement);

private:
	Engine::CManagement*		m_pManagementClass{ nullptr };
	LPDIRECT3DDEVICE9			m_pDevice{ nullptr };
	_ulong		m_dwRenderCnt = 0;
	_tchar		m_szFPS[256];

	_float		m_fTime = 0.f;
};