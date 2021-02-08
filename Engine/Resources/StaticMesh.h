#ifndef StaticMesh_h__
#define StaticMesh_h__

#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CStaticMesh : public CMesh
{
private:
	explicit CStaticMesh(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CStaticMesh(const CStaticMesh& rhs);
	virtual ~CStaticMesh(void);

public:
	static const _tchar* GetComponentTag() { return L"StaticMesh"; }
	static CStaticMesh*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFilePath, const _tchar* pFileName);
	virtual CComponent* Clone(void) override;
	virtual void Free(void) override;

public:
	const _ulong&		Get_NumVtx(void) { return m_dwNumVtx; }
	const _ulong&		Get_Stride(void) { return m_dwStride; }
	_vec3*		Get_VtxPos(void)const { return m_pVtxPos; }

	INDEX16*			Get_Indices() const { return m_pIndices; }
	_ulong				Get_NumIndices() const { return m_dwNumIndices; }
public:
	HRESULT		Ready_Meshes(const _tchar* pFilePath, const _tchar* pFileName);
	virtual void		Render_Meshes(void) override;
	virtual void		Render_Meshes(LPD3DXEFFECT& pEffect, const _uint& iPassNum = 0) override;

private:
	LPD3DXMESH			m_pOriMesh;		// ���� �ε� ������ �����ϴ� �޽� �İ�ü
	LPD3DXMESH			m_pMesh;		// �븻 ������ �����Ͽ� ��ȯ��Ų �޽� �İ�ü

	LPD3DXBUFFER		m_pAdjacency;	// ������ �̿��� ������ �����ϱ� ���� ù��° �ּҸ� �����Ϸ��� ��� ����
	LPD3DXBUFFER		m_pSubset;		// ����� ���� == �ؽ����� ���� == ������ ����
	D3DXMATERIAL*		m_pMtrl;
	_ulong				m_dwSubsetCnt;

	_ulong				m_dwStride;
	_ulong				m_dwNumVtx;
	_vec3*				m_pVtxPos;

	INDEX16*			m_pIndices;
	_ulong				m_dwNumIndices;

	LPDIRECT3DTEXTURE9*	m_ppTextures;
};

END
#endif // StaticMesh_h__