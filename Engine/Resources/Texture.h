#pragma once

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CResources
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture();

public:
	HRESULT		Ready_Texture(const _tchar* pPath, TEXTURETYPE eType, const _uint& iCnt);
	void		Render_Texture(const _uint& iIndex = 0);

	LPDIRECT3DBASETEXTURE9	Get_Texture(const _uint& iIndex = 0);
	void					Set_Texture(LPD3DXEFFECT& pEffect, const char* pConstantName, const _uint& iIndex = 0);		// Shader¿ë RenderTexture

public:
	static const _tchar* GetComponentTag() { return L"Texture"; }
	static CTexture*	 Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pPath, TEXTURETYPE eType, const _uint& iCnt);
	virtual CComponent*  Clone() override;
	virtual void		 Free();

private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;
};
END

