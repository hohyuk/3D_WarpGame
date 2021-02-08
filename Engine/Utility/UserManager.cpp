#include "UserManager.h"
#include "Export_System.h"
USING(Engine)
IMPLEMENT_SINGLETON(CUserManager)

CUserManager::CUserManager()
{
	for (int i = 0; i < ID::END_ID; ++i)
		m_bIsMode[i] = false;
}

CUserManager::~CUserManager()
{
}

void CUserManager::KeyInputDebug()
{
	if (KeyPress(DIK_P))
	{
		m_bIsMode[ID::STATICMESH_COLLIDER] = !m_bIsMode[ID::STATICMESH_COLLIDER];
	}

	if (KeyPress(DIK_O))
	{
		m_bIsMode[ID::DYNAMIC_COLLIDER] = !m_bIsMode[ID::DYNAMIC_COLLIDER];
	}

	if (KeyPress(DIK_I))
	{
		m_bIsMode[ID::NAVIDRAW] = !m_bIsMode[ID::NAVIDRAW];
	}

	if (KeyPress(DIK_U))
	{
		m_bIsMode[ID::DEBUG_TEXT] = !m_bIsMode[ID::DEBUG_TEXT];
	}

	if (KeyPress(DIK_0))		// ¼ýÀÚ 0
	{
		m_bIsMode[ID::RENDER_TARGET] = !m_bIsMode[ID::RENDER_TARGET];
	}
}
