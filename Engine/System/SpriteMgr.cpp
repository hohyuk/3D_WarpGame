#include "SpriteMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSpriteMgr)

CSpriteMgr::CSpriteMgr(void)
{

}

CSpriteMgr::~CSpriteMgr(void)
{
	Free();
}

HRESULT CSpriteMgr::Ready_Sprite(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pSpriteTag, const _tchar * pFilePath, const _uint & iCnt)
{
	CSprite*		pSprite = nullptr;

	pSprite = Find_Sprite(pSpriteTag);
	if (nullptr != pSprite)
		return E_FAIL;

	pSprite = CSprite::Create(pGraphicDev, pFilePath, iCnt);
	NULL_CHECK_RETURN(pSprite, E_FAIL);

	m_mapSprite.emplace(pSpriteTag, pSprite);
	return S_OK;
}

void CSpriteMgr::Render_Sprite(const _tchar * pSpriteTag, const _uint & iIndex, const _vec2 & _position, const _vec2 & _scale, const _float & _angle, const D3DCOLOR & _color)
{
	CSprite*	pSprite = Find_Sprite(pSpriteTag);
	NULL_CHECK(pSprite);

	pSprite->Render_Sprite(_position, _scale, _angle, _color);
}

void CSpriteMgr::Render_Sprite(const _tchar * pSpriteTag, const _uint & iIndex, const _matrix & _mat, const D3DCOLOR & _color)
{
	if (pSpriteTag == nullptr) return;

	CSprite*	pSprite = Find_Sprite(pSpriteTag);
	NULL_CHECK(pSprite);

	pSprite->Render_Sprite(_mat, _color);
}

const D3DXIMAGE_INFO * CSpriteMgr::Find_ImageInfo(const _tchar * pSpriteTag)
{
	CSprite* pSprite =  Find_Sprite(pSpriteTag);

	if (!pSprite)
		return nullptr;

	return pSprite->GetImageInfo();
}

_vec3 CSpriteMgr::Find_ImageCenter(const _tchar * pSpriteTag)
{
	CSprite* pSprite = Find_Sprite(pSpriteTag);

	// 이미지가 존재하지 않으면 0,0,0으로 출력
	if (!pSprite)
		return _vec3(0.f, 0.f, 0.f);

	return pSprite->GetImageCenter();
}

CSprite * CSpriteMgr::Find_Sprite(const _tchar * pSpriteTag)
{
	auto	iter = find_if(m_mapSprite.begin(), m_mapSprite.end(), CTag_Finder(pSpriteTag));

	if (iter == m_mapSprite.end())
		return nullptr;

	return iter->second;
}

void CSpriteMgr::Free(void)
{
	for_each(m_mapSprite.begin(), m_mapSprite.end(), CDeleteMap());
	m_mapSprite.clear();
}
