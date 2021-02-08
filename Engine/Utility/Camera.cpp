#include "Camera.h"

USING(Engine)

Engine::CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	
}

Engine::CCamera::~CCamera()
{

}

HRESULT Engine::CCamera::Ready()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

Engine::_int Engine::CCamera::Update(const _float& fTimeDelta)
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	return 0;
}

void CCamera::SetProjectionMatrix(const _float & _fFOV, const _float & _fAspect, const _float & _fNear, const _float & _fFar)
{
	m_fFovY = _fFOV;
	m_fAspect = _fAspect;
	m_fNear = _fNear;
	m_fFar = _fFar;

	_matrix matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, // 행렬 결과
								m_fFovY,		// fovY
								m_fAspect,	// 종횡비
								m_fNear,		// 절두체의 near 평면의 z값
								m_fFar);		// 절두체의 far 평면의 z값

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Engine::CCamera::Free()
{
	CGameObject::Free();
}

