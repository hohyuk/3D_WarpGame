#ifndef InputDev_h__
#define InputDev_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CInputDev : public CBase
{
	DECLARE_SINGLETON(CInputDev)

private:
	explicit CInputDev(void);
	virtual ~CInputDev(void);

public:
	// 키가 떼어져 있을때
	_bool KeyRelease(const _ubyte& byKeyID) { return !(m_byKeyState[byKeyID] & 0x80); }

	// 키가 눌러져 있을때
	_bool KeyPress(const _ubyte& byKeyID) { return (m_byKeyState[byKeyID] & 0x80); }

	// 키가 떼어질 때
	_bool KeyUp(const _ubyte& byKeyID) { return (!(m_byKeyState[byKeyID] & 0x80) && (m_byExKeyState[byKeyID] & 0x80)); }

	// 키가 눌릴 때
	_bool KeyDown(const _ubyte& byKeyID) { return ((m_byKeyState[byKeyID] & 0x80) && !(m_byExKeyState[byKeyID] & 0x80)); }
	

	// 키가 떼어져 있을때
	_bool KeyRelease(const MOUSEKEYSTATE& eMouse) { return !(m_tMouseState.rgbButtons[eMouse] & 0x80); }

	// 키가 눌러져 있을때
	_bool KeyPress(const MOUSEKEYSTATE& eMouse) { return (m_tMouseState.rgbButtons[eMouse] & 0x80); }

	// 키가 떼어질 때
	_bool KeyUp(const MOUSEKEYSTATE& eMouse) { return (!(m_tMouseState.rgbButtons[eMouse] & 0x80) && (m_tExMouseState.rgbButtons[eMouse] & 0x80)); }

	// 키가 눌릴 때
	_bool KeyDown(const MOUSEKEYSTATE& eMouse) { return ((m_tMouseState.rgbButtons[eMouse] & 0x80) && !(m_tExMouseState.rgbButtons[eMouse] & 0x80)); }


	_byte	Get_DIKeyState(_ubyte byKeyID) { return m_byKeyState[byKeyID]; }

	_byte	Get_DIMouseState(MOUSEKEYSTATE eMouse) { return m_tMouseState.rgbButtons[eMouse]; }
	
	_long	Get_DIMouseMove(MOUSEMOVESTATE eMouseState)
	{
		return *(((_long*)&m_tMouseState) + eMouseState);
	}


public:
	HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd);
	void	Set_InputDev(void);

public:
	virtual void	Free(void);

private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;

private:
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8	m_pMouse = nullptr;

private:
	_byte					m_byKeyState[256];
	DIMOUSESTATE			m_tMouseState;
	_byte					m_byExKeyState[256];
	DIMOUSESTATE			m_tExMouseState;
};
END
#endif // InputDev_h__
