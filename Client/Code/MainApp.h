#pragma once

#include "Export_Function.h"

class CMainApp : public CBase
{
private: // ������, �Ҹ���
	explicit CMainApp();
	virtual ~CMainApp();

	// ����, �Ҹ� �Լ�
public:
	static CMainApp*	Create();
	virtual void		Free();

	// public �Լ�, ����
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