#ifndef Camera_h__
#define Camera_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera : public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCamera();

public:
	virtual HRESULT			Ready();
	virtual _int			Update(const _float& fTimeDelta);

public:
	void SetProjectionMatrix(const _float & _fFOV, const _float & _fAspect, const _float & _fNear, const _float & _fFar);

protected:
	virtual void Free();

protected:
	_matrix			m_matView, m_matProj;
	_vec3			m_vEye, m_vAt, m_vUp;
	_float			m_fFovY, m_fAspect, m_fNear, m_fFar;
};


END
#endif // Camera_h__
