#include "Sprite.h"
#include "GraphicDev.h"
USING(Engine)

CSprite::CSprite(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pSprite(nullptr)
{
	m_pGraphicDev->AddRef();
}

CSprite::~CSprite(void)
{
}

HRESULT CSprite::Ready_Sprite(const _tchar * pPath, const _uint & iCnt)
{
	if (FAILED(D3DXGetImageInfoFromFile(pPath, &m_tImageInfo)))
	{
		MSG_BOX("Failed Sprite ImageInfo");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pGraphicDev,
		pPath,
		m_tImageInfo.Width,
		m_tImageInfo.Height,
		m_tImageInfo.MipLevels,
		0,
		m_tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0, nullptr, nullptr,
		&m_pTexture)))
	{
		MSG_BOX("Failed Sprite TextureFromFileEx");
		return E_FAIL;
	}
	/*if (FAILED(D3DXCreateTextureFromFile(m_pGraphicDev, pPath, (LPDIRECT3DTEXTURE9*)&pTexture)))
		return E_FAIL;*/

	//FAILED_CHECK_RETURN(D3DXCreateSprite(m_pGraphicDev, &m_pSprite), E_FAIL);

	// 스프라이트 컴객체 생성
	FAILED_CHECK_RETURN(D3DXCreateSprite(m_pGraphicDev, &m_pSprite), E_FAIL);
	m_pSprite->AddRef();

	m_vCenter = { static_cast<float>(m_tImageInfo.Width >> 1), static_cast<float>(m_tImageInfo.Height >> 1) , 0.f };
	return S_OK;
}

void CSprite::Render_Sprite(const _vec2 & _position, const _vec2 & _scale, const _float & _angle, const D3DCOLOR & _color)
{
	D3DXMATRIX matWorld, matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, _scale.x, _scale.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, _angle);
	D3DXMatrixTranslation(&matTrans, _position.x, _position.y, 0.f);
	matWorld = matScale * matRotZ * matTrans;


	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTexture, nullptr, &m_vCenter, nullptr, _color);
	m_pSprite->End();
}

void CSprite::Render_Sprite(const _matrix & _mat, const D3DCOLOR & _color)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&_mat);
	m_pSprite->Draw(m_pTexture, nullptr, &m_vCenter, nullptr, _color);
	m_pSprite->End();
}

CSprite * CSprite::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pPath, const _uint & iCnt)
{
	CSprite*	pInstance = new CSprite(pGraphicDev);

	if (FAILED(pInstance->Ready_Sprite(pPath, iCnt)))
	{
		MSG_BOX("Sprite Create Failed");
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

void CSprite::Free(void)
{
	Engine::Safe_Release(m_pSprite);
	Engine::Safe_Release(m_pGraphicDev);
}
