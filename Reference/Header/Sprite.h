#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CSprite : public CBase
{
private:
	explicit CSprite(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSprite(void);

public:
	HRESULT		Ready_Sprite(const _tchar* pPath,
							const _uint& iCnt);

	void		Render_Sprite(
		const _vec2& _position,
		const _vec2& _scale,
		const _float& _angle,
		const D3DCOLOR& _color);

	void		Render_Sprite(
		const _matrix& _mat,
		const D3DCOLOR& _color);

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static CSprite*		Create(LPDIRECT3DDEVICE9 pGraphicDev,
								const _tchar* pPath,
								const _uint& iCnt);
public:
	const D3DXIMAGE_INFO*		GetImageInfo()const { return &m_tImageInfo; }
	_vec3						GetImageCenter()const { return m_vCenter; }
private:
	virtual void Free(void);

private:
	LPD3DXSPRITE			m_pSprite;

	// �̹��� ������ �����ϱ� ���� COM Object
	LPDIRECT3DTEXTURE9		m_pTexture;
	// �̹����� ������ ��Ƶ� ����ü
	D3DXIMAGE_INFO			m_tImageInfo;
	_vec3					m_vCenter{ 0.f,0.f,0.f };			// UI�ؽ��� ���� �ʿ�.
};

END