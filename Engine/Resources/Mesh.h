#ifndef Mesh_h__
#define Mesh_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CMesh: public CResources
{
protected:
	explicit CMesh(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMesh(const CMesh& rhs);
	virtual ~CMesh(void);

protected:
	_bool		Find_Alpha(const char* pFileName);
	_bool		Find_Specular(const char* pFileName);
	_bool		Find_TextureUV_Anim(const char* pFileName);
	_bool		Find_TextureColor(const char* pFileName);
	_bool		Find_MeshColor(const char* pFileName);

protected:
	_bool		m_bClone;
public:
	virtual CComponent*		Clone(void)PURE;
	virtual void			Free(void);

public:
	virtual void			Render_Meshes(void) {};
	virtual void			Render_Meshes(LPD3DXEFFECT& pEffect, const _uint& iPassNum = 0) {};
};

END
#endif // Mesh_h__
