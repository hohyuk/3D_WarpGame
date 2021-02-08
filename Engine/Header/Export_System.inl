#include "Export_System.h"
BEGIN(Engine)


// GraphicDev //
// Get
// Set
// General
HRESULT		Ready_GraphicDev(HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev) {
	return CGraphicDev::GetInstance()->Ready_GraphicDev(hWnd, eMode, iSizeX, iSizeY, ppGraphicDev);
}
void		Render_Begin(D3DXCOLOR Color) {
	CGraphicDev::GetInstance()->Render_Begin(Color);
}
void		Render_End(void) {
	CGraphicDev::GetInstance()->Render_End();
}


// TimerMgr //
// Get
_float		Get_TimeDelta(const _tchar* pTimerTag) {
	return CTimerMgr::GetInstance()->Get_TimeDelta(pTimerTag);
}
// Set
void	    Set_TimeDelta(const _tchar* pTimerTag) {
	CTimerMgr::GetInstance()->Set_TimeDelta(pTimerTag);
}

// General
HRESULT		Ready_Timer(const _tchar* pTimerTag) {
	return CTimerMgr::GetInstance()->Ready_Timer(pTimerTag);
}

void	    	ReSet_TimeDelta(const _tchar* pTimerTag) {
	return CTimerMgr::GetInstance()->Reset_TimeDelta(pTimerTag);
}


// FrameMgr //
// Get
_bool		IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta) {
	return CFrameMgr::GetInstance()->IsPermit_Call(pFrameTag, fTimeDelta);
}
// Set
// General
HRESULT		Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit) {
	return CFrameMgr::GetInstance()->Ready_Frame(pFrameTag, fCallLimit);
}

// FontMgr
HRESULT	Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFontTag,
	const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight) {
	return CFontMgr::GetInstance()->Ready_Font(pGraphicDev, pFontTag, pFontType, iWidth, iHeight, iWeight);
}
void	Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color) {
	CFontMgr::GetInstance()->Render_Font(pFontTag, pString, pPos, Color);
}
void	Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, const _vec2* pScale, D3DXCOLOR Color) {
	CFontMgr::GetInstance()->Render_Font(pFontTag, pString, pPos, pScale, Color);
}
void	Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, DWORD format, D3DXCOLOR Color) {
	CFontMgr::GetInstance()->Render_Font(pFontTag, pString, pPos, format, Color);
}


// InputDev
inline _bool KeyRelease(const _ubyte& byKeyID) {
	return CInputDev::GetInstance()->KeyRelease(byKeyID);
}
inline _bool KeyPress(const _ubyte& byKeyID) {
	return CInputDev::GetInstance()->KeyPress(byKeyID);
}
inline _bool KeyUp(const _ubyte& byKeyID) {
	return CInputDev::GetInstance()->KeyUp(byKeyID);
}
inline _bool KeyDown(const _ubyte& byKeyID) {
	return CInputDev::GetInstance()->KeyDown(byKeyID);
}

inline _bool KeyRelease(const MOUSEKEYSTATE& eMouse) {
	return CInputDev::GetInstance()->KeyRelease(eMouse);
}
inline _bool KeyPress(const MOUSEKEYSTATE& eMouse) {
	return CInputDev::GetInstance()->KeyPress(eMouse);
}
inline _bool KeyUp(const MOUSEKEYSTATE& eMouse) {
	return CInputDev::GetInstance()->KeyUp(eMouse);
}
inline _bool KeyDown(const MOUSEKEYSTATE& eMouse) {
	return CInputDev::GetInstance()->KeyDown(eMouse);
}

_byte	Get_DIKeyState(_ubyte byKeyID) {
	return CInputDev::GetInstance()->Get_DIKeyState(byKeyID);
}
_byte	Get_DIMouseState(MOUSEKEYSTATE eMouse) {
	return CInputDev::GetInstance()->Get_DIMouseState(eMouse);
}
_long	Get_DIMouseMove(MOUSEMOVESTATE eMouseState) {
	return CInputDev::GetInstance()->Get_DIMouseMove(eMouseState);
}
HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd) {
	return CInputDev::GetInstance()->Ready_InputDev(hInst, hWnd);
}
void	Set_InputDev(void) {
	CInputDev::GetInstance()->Set_InputDev();
}



// SpriteMgr
HRESULT	Ready_Sprite(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pSpriteTag, const _tchar* pFilePath, const _uint& iCnt/* = 0*/)
{
	return CSpriteMgr::GetInstance()->Ready_Sprite(pGraphicDev, pSpriteTag, pFilePath, iCnt);
}

void		Render_Sprite(const _tchar* pSpriteTag, const _uint& iIndex, const _vec2& _position, const _vec2& _scale, const _float& _angle, const D3DCOLOR& _color /*= D3DCOLOR_ARGB(255, 255, 255, 255)*/)
{
	CSpriteMgr::GetInstance()->Render_Sprite(pSpriteTag, iIndex, _position, _scale, _angle, _color);
}

void		Render_Sprite(const _tchar* pSpriteTag, const _uint& iIndex, const _matrix& _mat, const D3DCOLOR& _color /*= D3DCOLOR_ARGB(255, 255, 255, 255)*/)
{
	CSpriteMgr::GetInstance()->Render_Sprite(pSpriteTag, iIndex, _mat, _color);
}

const D3DXIMAGE_INFO*	Find_ImageInfo(const _tchar* pSpriteTag)
{
	return CSpriteMgr::GetInstance()->Find_ImageInfo(pSpriteTag);
}

_vec3 Find_ImageCenter(const _tchar * pSpriteTag)
{
	return CSpriteMgr::GetInstance()->Find_ImageCenter(pSpriteTag);
}

void		Release_System(void) {
	CSpriteMgr::GetInstance()->DestroyInstance();
	CInputDev::GetInstance()->DestroyInstance();
	CFontMgr::GetInstance()->DestroyInstance();
	CFrameMgr::GetInstance()->DestroyInstance();
	CTimerMgr::GetInstance()->DestroyInstance();
	CGraphicDev::GetInstance()->DestroyInstance();
}

END