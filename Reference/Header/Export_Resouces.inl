// ResourcesMgr
// Get
inline Engine::CVIBuffer* Get_Buffer(const Engine::_ushort& wContainerIdx, const Engine::_tchar* pBufferTag)
{
	return Engine::CResourcesMgr::GetInstance()->Get_Buffer(wContainerIdx, pBufferTag);
}
LPDIRECT3DTEXTURE9	Get_NormalTexture(const _tchar* pTextureTag, const _uint& iIndex) {
	return LPDIRECT3DTEXTURE9(CResourcesMgr::GetInstance()->Get_Texture(TEX_NORMAL, pTextureTag, iIndex));
}

CComponent*	Clone(const _ushort& wContainerIdx, const _tchar* pResourcesTag)
{
	return CResourcesMgr::GetInstance()->Clone(wContainerIdx, pResourcesTag);
}

// Set
// General

HRESULT		Reserve_ContainerSize(const _ushort& wSize)
{
	return CResourcesMgr::GetInstance()->Reserve_ContainerSize(wSize);
}
HRESULT		Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort& wContainerIdx, const _tchar* pBufferTag, BUFFERID eID, _ulong dwCntX, _ulong dwCntZ, _ulong dwItv)
{
	return CResourcesMgr::GetInstance()->Ready_Buffer(pGraphicDev, wContainerIdx, pBufferTag, eID, dwCntX, dwCntZ, dwItv);
}
HRESULT		Ready_Terrain_Buffer(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort& wContainerIdx, const _tchar* pBufferTag, const _tchar* pDataPath, _ulong dwCntX, _ulong dwCntZ, _ulong dwItv)
{
	return CResourcesMgr::GetInstance()->Ready_Terrain_Buffer(pGraphicDev, wContainerIdx, pBufferTag, pDataPath, dwCntX, dwCntZ, dwItv);
}
void		Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag)
{
	CResourcesMgr::GetInstance()->Render_Buffer(wContainerIdx, pBufferTag);
}

HRESULT		Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort& wContainerIdx, const _tchar* pTextureTag, TEXTURETYPE eType, const _tchar* pFilePath, const _uint& iCnt)
{
	return CResourcesMgr::GetInstance()->Ready_Texture(pGraphicDev, wContainerIdx, pTextureTag, eType, pFilePath, iCnt);
}

HRESULT		Ready_Meshes(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort& wContainerIdx, const _tchar* pMeshTag, MESHTYPE eType, const _tchar* pFilePath, const _tchar* pFileName)
{
	return CResourcesMgr::GetInstance()->Ready_Meshes(pGraphicDev, wContainerIdx, pMeshTag, eType, pFilePath, pFileName);
}

void		Render_Texture(const _ushort& wContainerIdx, const _tchar* pTextureTag, const _uint& iIndex)
{
	CResourcesMgr::GetInstance()->Render_Texture(wContainerIdx, pTextureTag, iIndex);
}

// Adjust
void		Adjust_TerrainBuffer(const _ushort& wContainerIdx, const _tchar* pBufferTag, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv, const _float& fDetail/* = 20.f*/)
{
	CResourcesMgr::GetInstance()->Adjust_TerrainBuffer(wContainerIdx, pBufferTag, dwCntX, dwCntZ, dwVtxItv, fDetail);
}
// Release Resources
void Release_Resoures()
{
	CResourcesMgr::GetInstance()->DestroyInstance();
}
