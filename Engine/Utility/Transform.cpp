#include "Transform.h"
#include "GameObject.h"
//#include "ColliderObject.h"
BEGIN(Engine)

CTransform::CTransform() : 
	CComponent(),
	m_vScale(1.f, 1.f, 1.f),
    m_vAngle(0.f, 0.f, 0.f) {

}

CTransform::CTransform(const CTransform& transform) :
	CComponent(transform),
	m_vScale(transform.m_vScale),
    m_vAngle(transform.m_vAngle) {

}

CTransform::~CTransform() {

}

HRESULT CTransform::Ready() {

    return S_OK;
}

_int CTransform::Update(const _float& fTimeDelta) {
	// 크기 변환 적용
	_matrix		matScale;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	// 회전 적용
	_matrix		matRot;
	D3DXMatrixRotationYawPitchRoll(&matRot, m_vAngle.y, m_vAngle.x, m_vAngle.z);

	// 이동 적용
	_matrix		matTrans;
	D3DXMatrixTranslation(&matTrans, m_Info.Pos.x, m_Info.Pos.y, m_Info.Pos.z);

	m_ParentRotTransMat = matRot * matTrans;
	m_Info.matrix = matScale * matRot * matTrans;

    return 0;
}

_vec3 CTransform::GetDegreeAngle()
{
	return _vec3(D3DXToDegree(m_vAngle.x), D3DXToDegree(m_vAngle.y), D3DXToDegree(m_vAngle.z));
}

_matrix CTransform::GetWorldMat() const {
	_matrix matWorld = m_Info.matrix;
	if (m_pParentBoneMatrix != nullptr)
		matWorld = m_Info.matrix * (*m_pParentBoneMatrix);

	CGameObject* pObj = m_pGameObject;
	while (pObj) {
		if (pObj = pObj->GetParent()) {
			if (m_pGameObject->ApplyParentScaleMat())
				matWorld *= pObj->GetTransform()->GetLocalMat();
			else
				matWorld *= pObj->GetTransform()->GetParentRotTransMat();
		}
	}
	return matWorld;
}

void CTransform::SetTransform(LPDIRECT3DDEVICE9& pGraphicDev) const {
	pGraphicDev->SetTransform(D3DTS_WORLD, &(GetWorldMat()));
}


void CTransform::Chase_Target(const _vec3* pTargetPos, const _float& fSpeed, const _float& fTimeDelta) {
	_vec3 vDir = *pTargetPos - m_Info.Pos;

	if (D3DXVec3Length(&vDir) > 0.5f)
		m_Info.Pos += (*D3DXVec3Normalize(&vDir, &vDir)) * fSpeed * fTimeDelta;

	SetDirection(vDir);
}

CComponent* CTransform::Create(CGameObject* const _gameObject) {
	CTransform* pInstance = new CTransform;

	if (FAILED(pInstance->Ready()))
		Safe_Release(pInstance);

    pInstance->m_pGameObject = _gameObject;
	pInstance->m_eCompID = ID_DYNAMIC;
    return pInstance;
}

CComponent* CTransform::Clone(void) {
    return new CTransform(*this);
}

void CTransform::Free(void) {

}

void CTransform::SetDirection(const _vec3& _dir) {
	_vec3	vDir = _dir;

	_vec3	vDirXZ;
	_float	angleX, angleY;

	vDirXZ = vDir;
	vDirXZ.y = 0.f;

	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&vDirXZ, &vDirXZ);

	angleY = acosf(Clamp(D3DXVec3Dot(&vDirXZ, &WORLD_Z_AXIS), -1.f, 1.f));
	angleX = acosf(Clamp(D3DXVec3Dot(&vDirXZ, &vDir), -1.f, 1.f));

	if (vDir.x < 0.f) angleY *= -1.f;
	if (vDir.y < 0.f) angleX *= -1.f;

	m_vAngle.x = -angleX;
	m_vAngle.y = angleY;
}

void CTransform::SetDirection(const _vec3 & _dir, const _float & fTimeDelta)
{
	_vec3	vDir = _dir;

	_vec3	vDirXZ;
	_float	angleX, angleY;

	vDirXZ = vDir;
	vDirXZ.y = 0.f;

	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&vDirXZ, &vDirXZ);

	angleY = acosf(Clamp(D3DXVec3Dot(&vDirXZ, &WORLD_Z_AXIS), -1.f, 1.f));
	angleX = acosf(Clamp(D3DXVec3Dot(&vDirXZ, &vDir), -1.f, 1.f));

	if (vDir.x < 0.f)
		angleY = D3DXToRadian(360.f) - angleY;
	
	if (vDir.y < 0.f) angleX *= -1.f;

	_vec3 vAngle;
	m_vAngle.x = -angleX;
	vAngle.y = angleY;
	m_vAngle.z = 0.f;
	//D3DXVec3Lerp(&m_vAngle, &m_vAngle, &vAngle, 0.1f);

	
	m_vAngle.y = vAngle.y * 0.1f;
}

void CTransform::SetLookAt(const _vec3& _dir, const _vec3& _up) {
	/*_quat qt;
	_vec3 vNormalDir, vNormalUp;
	D3DXVec3Normalize(&vNormalDir, &_dir);
	D3DXVec3Normalize(&vNormalUp, &_up);
	D3DXQuaternionLookRotation(&qt, &vNormalDir, &vNormalUp);
	m_vAngle = ToEulerianAngle(qt);

	if (vNormalDir.z < 0.f) {
		m_vAngle.y *= -1.f;
		m_vAngle.x *= -1.f;
	}*/
	//if (vNormalDir.y < 0.f) m_vAngle.x *= -1.f;

	// 12.01 성구가 수정
	_vec3   vDir, vDirXZ, vUp, vTempRight, vTempUp, vAngle;

	D3DXVec3Normalize(&vDir, &_dir);
	D3DXVec3Normalize(&vUp, &_up);
	vDirXZ = vDir;
	vDirXZ.y = 0.f;
	D3DXVec3Normalize(&vDirXZ, &vDirXZ);

	vTempUp = { 0.f, 1.f, 0.f };
	D3DXVec3Cross(&vTempRight, &vTempUp, &vDir);
	D3DXVec3Cross(&vTempUp, &vDir, &vTempRight);
	vAngle.z = acosf(Clamp(D3DXVec3Dot(&vTempUp, &vUp), -1.f, 1.f));

	vAngle.y = acosf(Clamp(D3DXVec3Dot(&vDirXZ, &WORLD_Z_AXIS), -1.f, 1.f));
	vAngle.x = -acosf(Clamp(D3DXVec3Dot(&vDirXZ, &vDir), -1.f, 1.f));

	if (vDir.x < 0.f)
	{
		//vAngle.y = D3DXToRadian(360.f) - vAngle.y;

		vAngle.y *= -1.f;
	}
	if (vDir.y < 0.f) vAngle.x *= -1.f;

	//D3DXVec3Lerp(&m_vAngle, &m_vAngle, &vAngle, 0.1f);
	m_vAngle = vAngle;
}

void CTransform::SetLookAt(const _quat& _lookAt) {
	m_vAngle = ToEulerianAngle(_lookAt);
}

void CTransform::Rotate(const _vec3& _axis, const _float& _angle, const _bool& _rotZ /*= false*/) {
	_matrix m_matRot;
	D3DXMatrixRotationAxis(&m_matRot, &_axis, _angle);
	D3DXVec3TransformNormal(&m_Info.Look, &m_Info.Look, &m_matRot);
	if (_rotZ) {
		D3DXVec3TransformNormal(&m_Info.Up, &m_Info.Up, &m_matRot);
		SetLookAt(m_Info.Look, m_Info.Up);
	}
	else {
		SetDirection(m_Info.Look);
	}
}

void CTransform::Rotate(const INFO& _eInfoID, const _float& _angle) {
	if (_eInfoID == INFO_LOOK) {
		m_vAngle.z += _angle;
		return;
	}
	_matrix m_matRot;
	D3DXMatrixRotationAxis(&m_matRot, (_vec3*)(((D3DXVECTOR4*)(&m_Info)) + _eInfoID), _angle);
	D3DXVec3TransformNormal(&m_Info.Look, &m_Info.Look, &m_matRot);
	SetDirection(m_Info.Look);
}

void CTransform::Rotate(const _float & _x, const _float & _y, const _float & _z)
{
	_matrix m_matRot;
	D3DXMatrixRotationYawPitchRoll(&m_matRot, _y, _x, _z);
}

void CTransform::RotateSlerp(const _vec3& _angle, const _float& t) {
	_matrix m_matRot, matScale;
	D3DXQUATERNION qtOrign, qt;
	D3DXQuaternionRotationYawPitchRoll(&qtOrign, m_vAngle.y, m_vAngle.x, m_vAngle.z);
	D3DXQuaternionRotationYawPitchRoll(&qt, _angle.y, _angle.x, _angle.z);

	D3DXQuaternionSlerp(&qt, &qtOrign, &qt, t);
	D3DXMatrixRotationQuaternion(&m_matRot, &qt);

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	m_matRot = matScale * m_matRot;

	D3DXVec3TransformNormal(&m_Info.Look, &_vec3(0.f, 0.f, 1.f), &m_matRot);
	D3DXVec3TransformNormal(&m_Info.Up, &_vec3(0.f, 1.f, 0.f), &m_matRot);
	SetLookAt(m_Info.Look, m_Info.Up);
	//SetDirection(m_Info.Look);
}

void CTransform::RotateSlerp(const _vec3& _axis, const _float& _angle, const _float& t) {
	_matrix m_matRot, matScale;
	D3DXQUATERNION qtOrign, qt;
	D3DXQuaternionRotationYawPitchRoll(&qtOrign, m_vAngle.y, m_vAngle.x, m_vAngle.z);
	D3DXQuaternionRotationAxis(&qt, &_axis, _angle);
	
	
	D3DXQuaternionSlerp(&qt, &qtOrign, &qt, t);
	D3DXMatrixRotationQuaternion(&m_matRot, &qt);
	//D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	//m_matRot = matScale * m_matRot;
	D3DXVec3TransformNormal(&m_Info.Look, &_vec3(0.f, 0.f, 1.f), &m_matRot);
	D3DXVec3TransformNormal(&m_Info.Up, &_vec3(0.f, 1.f, 0.f), &m_matRot);
	SetLookAt(m_Info.Look, m_Info.Up);
	//SetDirection(m_Info.Look);
}

void CTransform::RotateByAxis(_float _fDeltaAngle, const _vec3 & _vRotAxis)
{
	_matrix m_matRot;
	D3DXMatrixRotationAxis(&m_matRot, &_vRotAxis, _fDeltaAngle);

	/*D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	m_matRot = matScale * m_matRot;*/
	m_matRot._11 *= m_vScale.x;
	m_matRot._22 *= m_vScale.y;
	m_matRot._33 *= m_vScale.z;
	m_matRot._41 *= m_Info.Pos.x;
	m_matRot._42 *= m_Info.Pos.y;
	m_matRot._43 *= m_Info.Pos.z;

	D3DXVec3TransformNormal(&m_Info.Right, &m_Info.Right, &m_matRot);
	D3DXVec3TransformNormal(&m_Info.Up, &m_Info.Up, &m_matRot);
	D3DXVec3TransformNormal(&m_Info.Look, &m_Info.Look, &m_matRot);

	D3DXVec3Normalize(&m_Info.Right, &m_Info.Right);
	D3DXVec3Normalize(&m_Info.Up, &m_Info.Up);
	D3DXVec3Normalize(&m_Info.Look, &m_Info.Look);
}

_bool CTransform::IsZeroAngle()
{
	if (m_vAngle.x != 0 || m_vAngle.y != 0 || m_vAngle.z != 0) return false;

	return true;
}

END