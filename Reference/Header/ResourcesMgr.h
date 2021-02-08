#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

#include "Engine_Define.h"
#include "Base.h"

// VIBuffer
#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"
#include "CubeTex.h"
#include "TerrainTex.h"
#include "NaviTriCol.h"

// Texture
#include "Texture.h"

// Mesh
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "NaviMesh.h"

BEGIN(Engine)

class ENGINE_DLL CResourcesMgr : public CBase 
{
	DECLARE_SINGLETON(CResourcesMgr)

private:
	explicit CResourcesMgr();
	virtual ~CResourcesMgr();

public:
	HRESULT		Reserve_ContainerSize(const _ushort& wSize);

	HRESULT		Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pBufferTag, 
							BUFFERID eID, 
							_ulong dwCntX = 1, 
							_ulong dwCntZ = 1, 
							_ulong dwItv = 1);

	HRESULT		Ready_Terrain_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx, 
							const _tchar* pBufferTag,
							const _tchar* pDataPath,
							_ulong dwCntX = 1, 
							_ulong dwCntZ = 1, 
							_ulong dwItv = 1);

	HRESULT		Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pTextureTag,
							TEXTURETYPE eType, 
							const _tchar* pFilePath, 
							const _uint& iCnt = 0);

	HRESULT		Ready_Meshes(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pMeshTag,
							MESHTYPE eType,
							const _tchar* pFilePath,
							const _tchar* pFileName);

	void		Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag);
	void		Render_Texture(const _ushort& wContainerIdx, const _tchar* pTextureTag, const _uint& iIndex);

	void		Adjust_TerrainBuffer(const _ushort& wContainerIdx, const _tchar* pBufferTag, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv, const _float& fDetail);
	CComponent*	Clone(const _ushort& wContainerIdx, const _tchar* pResourcesTag);

public:
	CVIBuffer*				Get_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag);
	LPDIRECT3DBASETEXTURE9	Get_Texture(const _ushort& wContainerIdx, const _tchar* pTextureTag, const _uint& iIndex);

private:
	CResources*		Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourcesTag);

public:
	virtual void Free();

private:
	map<const _tchar*, CResources*>*		m_pmapResource;
	_ushort									m_wSize{};
};

END
#endif // ResourcesMgr_h__
