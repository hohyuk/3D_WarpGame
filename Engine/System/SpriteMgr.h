#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "Sprite.h"

BEGIN(Engine)

class ENGINE_DLL CSpriteMgr : public CBase
{
	DECLARE_SINGLETON(CSpriteMgr)

private:
	explicit CSpriteMgr(void);
	virtual ~CSpriteMgr(void);

public:
	HRESULT	Ready_Sprite(LPDIRECT3DDEVICE9 pGraphicDev,
						const _tchar* pSpriteTag,
						const _tchar* pFilePath,
						const _uint& iCnt);

	void	Render_Sprite(const _tchar* pSpriteTag,
						const _uint& iIndex,
						const _vec2& _position,
						const _vec2& _scale,
						const _float& _angle,
						const D3DCOLOR& _color);

	void	Render_Sprite(const _tchar* pSpriteTag,
						const _uint& iIndex,
						const _matrix& _mat,
						const D3DCOLOR& _color);
public:
	const D3DXIMAGE_INFO*	Find_ImageInfo(const _tchar* pSpriteTag);				// 이미지 정보
	_vec3	Find_ImageCenter(const _tchar* pSpriteTag);								// 이미지 센터

private:
	CSprite*		Find_Sprite(const _tchar* pSpriteTag);

private:
	map<const _tchar*, CSprite*>		m_mapSprite;

public:
	virtual void Free(void);
};

END
