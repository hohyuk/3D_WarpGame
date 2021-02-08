#include "framework.h"

#include "MainApp.h"
//#include "LogoScene.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

CMainApp * CMainApp::Create()
{
	CMainApp*	pInstance = new CMainApp;

	if (FAILED(pInstance->Ready()))
	{
		MSG_BOX("CMainApp Create Failed");
		Client::Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	CSoundMgr::GetInstance()->DestroyInstance();
	Client::Safe_Release(m_pDevice);
	Client::Safe_Release(m_pManagementClass);

	Engine::Release_Utility();
	Engine::Release_Resoures();
	Engine::Release_System();
}

HRESULT CMainApp::Ready()
{
	CSoundMgr::GetInstance()->Initialize();
	//srand((unsigned int)time(NULL));
	//Engine::CUserManager::GetInstance()->SetClientModeOn();

	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pDevice), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Get_Renderer()->Ready_Renderer(m_pDevice), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Scene(m_pDevice, &m_pManagementClass), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pDevice, L"Font_Default", L"¹ÙÅÁ", 15, 20, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pDevice, L"Font_Jinji", L"±Ã¼­", 30, 30, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pDevice, L"Font_SmallGothic", L"¸¼Àº °íµñ", 10, 25, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pDevice, L"Font_Gothic", L"¸¼Àº °íµñ", 15, 37, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pDevice, L"Font_UI_Button", L"HY°ß°íµñ", 17, 30, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pDevice, L"Font_End", L"HY°ß°íµñ", 60, 60, FW_NORMAL), E_FAIL);


	wsprintf(m_szFPS, L"FPS : %d", m_dwRenderCnt);
	return S_OK;
}

_int CMainApp::Update(const _float & fTimeDelta)
{
	if (nullptr == m_pManagementClass)
		return -1;

	m_fTime += fTimeDelta;

	Engine::Set_InputDev();
	//Engine::CUserManager::GetInstance()->KeyInputDebug();

	m_pManagementClass->Update_Scene(fTimeDelta);
	return 0;
}

void CMainApp::Render()
{
	// FPS
	++m_dwRenderCnt;

	if (m_fTime >= 1.f)
	{
		wsprintf(m_szFPS, L"FPS : %d", m_dwRenderCnt);
		m_fTime = 0.f;
		m_dwRenderCnt = 0;
	}

	Engine::Render_Begin(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.f));
	//Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 0.f, 1.f));

	
	//m_pManagementClass->Render_Scene(m_pDevice);

	/*if (Engine::CUserManager::GetInstance()->IsDebugTextOn())
		Engine::Render_Font(L"Font_SmallGothic", m_szFPS, &_vec2(WINCX - 100.f, 10.f), D3DXCOLOR(0.f, 1.f, 0.f, 1.f));
*/
	Engine::Render_End();
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	Engine::CGraphicDev* m_pDeviceClass{ nullptr };

	// Ã¢¸ðµå
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, Engine::MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);

	//FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, Engine::MODE_FULL, WINCX, WINCY, &m_pDeviceClass), E_FAIL);

	Engine::Safe_AddRef(m_pDeviceClass);

	m_pDevice = m_pDeviceClass->Get_GraphicDev();
	Engine::Safe_AddRef(m_pDevice);

	Engine::Safe_Release(m_pDeviceClass);

	// InputDev ¼³Ä¡
	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL);
	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagement)
{
	Engine::CScene* pScene = nullptr;

	//pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(ppManagement), E_FAIL);
	Safe_AddRef(*ppManagement);

	FAILED_CHECK_RETURN((*ppManagement)->SetUp_Scene(pScene), E_FAIL);

	return S_OK;
}
