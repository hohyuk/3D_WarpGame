#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CNaviTriCol : public CVIBuffer
{
protected:
	explicit CNaviTriCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNaviTriCol(const CNaviTriCol& rhs);
	virtual ~CNaviTriCol();

public:
	virtual HRESULT	Ready_Buffer();
	virtual HRESULT	Ready_Buffer(const _vec3& v1, const _vec3& v2, const _vec3& v3);
	
public:
	void			PushTriVertices(const _vec3& v1, const _vec3& v2, const _vec3& v3);
	_bool			PopTriIndex(const _int& _index);
public:
	vector<_vec3>&	GetVecVertices() { return m_vVertices; }
	_int			GetSize() { return static_cast<_int>(m_vVertices.size()); }
	_bool			IsValidVertexIndex(const _int& _index);
	_bool			IsValidTriIndex(const _int& _index);
	void			ChangeColor(const _int& _index, const D3DXCOLOR& _color = D3DXCOLOR(0.f, 0.5f, 1.f, 1.f));
	void			AdjustVertexPos(const _int& _index, const _vec3& vPos);
	void			LoadNaviMesh(const vector<_vec3>& _vLoadVertex);
	void			ClearVertex();
public:
	static const _tchar* GetComponentTag() { return L"NaviTriCol"; }
	static CNaviTriCol*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& v1, const _vec3& v2, const _vec3& v3);
	static CNaviTriCol*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone() override;
	virtual void Free();

private:
	_bool MakeTriBuffer();

private:
	vector<_vec3> m_vVertices;
};
END


