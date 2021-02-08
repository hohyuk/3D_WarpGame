#ifndef Export_System_h__
#define Export_System_h__

#include "GraphicDev.h"
#include "TimerMgr.h"
#include "FrameMgr.h"
#include "FontMgr.h"
#include "InputDev.h"
#include "SpriteMgr.h"

BEGIN(Engine)

// GraphicDev //
// Get
// Set
// General
inline HRESULT	Ready_GraphicDev(HWND hWnd,	WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev);
inline void		Render_Begin(D3DXCOLOR Color);
inline void		Render_End(void);

// TimerMgr //
// Get
inline _float		Get_TimeDelta(const _tchar* pTimerTag);
// Set
inline void	    	Set_TimeDelta(const _tchar* pTimerTag);
// General
inline HRESULT		Ready_Timer(const _tchar* pTimerTag);

inline void	    	ReSet_TimeDelta(const _tchar* pTimerTag);

// FrameMgr //
// Get
inline _bool		IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);
// Set
// General
inline	HRESULT		Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);


// FontMgr
inline HRESULT	Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFontTag, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight);
inline void		Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color);
inline void		Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, const _vec2* pScale, D3DXCOLOR Color);
inline void		Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, DWORD format, D3DXCOLOR Color);


// InputDev
inline _bool	KeyRelease(const _ubyte& byKeyID);				// 키가 떼어져 있을때
inline _bool	KeyPress(const _ubyte& byKeyID);				// 키가 눌러져 있을때
inline _bool	KeyUp(const _ubyte& byKeyID);					// 키가 떼어질 때
inline _bool	KeyDown(const _ubyte& byKeyID);					// 키가 눌릴 때

inline _bool	KeyRelease(const MOUSEKEYSTATE& eMouse);		// 마우스가 떼어져 있을때
inline _bool	KeyPress(const MOUSEKEYSTATE& eMouse);			// 마우스가 눌러져 있을때
inline _bool	KeyUp(const MOUSEKEYSTATE& eMouse);				// 마우스가 떼어질 때
inline _bool	KeyDown(const MOUSEKEYSTATE& eMouse);			// 마우스가 눌릴 때

inline _byte	Get_DIKeyState(_ubyte byKeyID);
inline _byte	Get_DIMouseState(MOUSEKEYSTATE eMouse);
inline _long	Get_DIMouseMove(MOUSEMOVESTATE eMouseState);
inline	HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd);
inline	void	Set_InputDev(void);



//// SpriteMgr
inline HRESULT	Ready_Sprite(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pSpriteTag, const _tchar* pFilePath, const _uint& iCnt = 0);
inline void		Render_Sprite(const _tchar* pSpriteTag, const _uint& iIndex, const _vec2& _position, const _vec2& _scale, const _float& _angle, const D3DCOLOR& _color = D3DCOLOR_ARGB(255, 255, 255, 255));
inline void		Render_Sprite(const _tchar* pSpriteTag, const _uint& iIndex, const _matrix& _mat, const D3DCOLOR& _color = D3DCOLOR_ARGB(255, 255, 255, 255));
inline const	D3DXIMAGE_INFO*	Find_ImageInfo(const _tchar* pSpriteTag);
inline _vec3	Find_ImageCenter(const _tchar * pSpriteTag);

// Release
inline void		    Release_System(void);


END

#include "Export_System.inl"

#endif // Export_System_h__
