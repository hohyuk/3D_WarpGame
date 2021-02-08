#include "Mesh.h"

Engine::CMesh::CMesh(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
	, m_bClone(false)
{

}

Engine::CMesh::CMesh(const CMesh& rhs)
	: CResources(rhs)
	, m_bClone(true)
{

}

Engine::CMesh::~CMesh(void)
{

}

Engine::_bool Engine::CMesh::Find_Alpha(const char * pFileName)
{
	_uint	iLength = static_cast<_uint>(strlen(pFileName));

	for (_uint i = 0; i < iLength + 1; ++i)
	{
		if (pFileName[i] == '.')
		{
			if (pFileName[i - 1] == 'A')
				return true;
		}
	}

	return false;
}

Engine::_bool Engine::CMesh::Find_Specular(const char * pFileName)
{
	_uint	iLength = static_cast<_uint>(strlen(pFileName));

	for (_uint i = 0; i < iLength + 1; ++i)
	{
		if (pFileName[i] == '.')
		{
			if (pFileName[i - 1] == 'S')
				return true;
		}
	}

	return false;
}

Engine::_bool Engine::CMesh::Find_TextureUV_Anim(const char * pFileName)
{
	// UV 애니메이션에 필요한 텍스쳐 이름 찾기
	if (0 == strcmp(pFileName, "t_conveyormatflat_D.tga"))
		return true;
	else if (0 == strcmp(pFileName, "glass.png"))
		return true;

	return false;
}

Engine::_bool Engine::CMesh::Find_TextureColor(const char * pFileName)
{
	if (0 == strcmp(pFileName, "red_bulb_D.tga")) return true;
	else if(0 == strcmp(pFileName,"T_LightSwitch_D.tga")) return true;
	return false;
}

Engine::_bool Engine::CMesh::Find_MeshColor(const char * pFileName)
{
	if (0 == strcmp(pFileName, "T_Lightning1_D.tga")) return true;

	return false;
}

void Engine::CMesh::Free(void)
{
	CResources::Free();
}

