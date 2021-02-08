#ifndef NaviMesh_h__
#define NaviMesh_h__

#include "Base.h"
#include "Mesh.h"
#include "Cell.h"

BEGIN(Engine)

class ENGINE_DLL CNaviMesh : public CMesh
{
private:
	explicit CNaviMesh(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNaviMesh(const CNaviMesh& rhs);
	virtual ~CNaviMesh(void);

public:
	HRESULT					Ready_NaviMeshes(void);
	virtual void			Render_Meshes();
	
	_vec3					Move_OnNaviMesh(_ulong& _dwIndex, const _vec3* pTargetPos, const _vec3* pTargetDir);
	_bool					Warp_OnNaviMesh(_ulong& _dwIndex, _vec3& pWarpPos);
	_bool					EnemyMove_OnNaviMesh(_ulong& _dwIndex, _vec3* pTargetPos, const _vec3* pTargetDir);
	_int					GetSize() { return static_cast<_int>(m_vecCell.size()); }
	void					Reserve(const _int& size);
	_bool					Add_NaviCell(const _vec3 & v1, const _vec3 & v2, const _vec3 & v3);
	void					DeleteNaviCell(const _int& _index);
	void					AdjustVertexPos(const _vec3& vPos, const _int& _CurCell_Index, const _int& _CellVertex_Index);
	void					ClearCell();

	_ulong					Find_Cell_Index(_ulong& _dwIndex, const _vec3& _vTargetPos);
	_bool					IsChange_IndexCell(_ulong& _dwIndex, const _vec3& _vTargetPos);

private:
	HRESULT		Link_Cell();


public:
	static const _tchar* GetComponentTag() { return L"NaviMesh"; }
	static CNaviMesh*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone();
	virtual void			Free();

private:
	vector<CCell*>			m_vecCell;
};

END
#endif // NaviMesh_h__
