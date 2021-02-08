#pragma once
#include "Component.h"

BEGIN(Engine)

typedef struct _INFO_MATRIX {
	_INFO_MATRIX() { D3DXMatrixIdentity(&this->matrix); };
	union {
		_matrix matrix;
		struct {
			_vec3 Right; _float _14;
			_vec3 Up;    _float _24;
			_vec3 Look;  _float _34;
			_vec3 Pos;   _float _44;
		};
	};
} INFO_MATRIX;

class ENGINE_DLL CTransform : public CComponent {
protected:
	explicit CTransform();
	explicit CTransform(const CTransform& transform);
	virtual ~CTransform(void);
public:
	virtual HRESULT Ready();
	virtual _int	Update(const _float& fTimeDelta);
	void			SetTransform(LPDIRECT3DDEVICE9& pGraphicDev)const;

	void			Chase_Target(const _vec3* pTargetPos, const _float& fSpeed, const _float& fTimeDelta);
public:
	static const _tchar* GetComponentTag() { return L"Transform"; }
	static CComponent* Create(CGameObject* const _gameObject);
	virtual CComponent* Clone(void) override;
	virtual void Free(void) override;
public:
	// Get
	_vec3	 GetRight() { return m_Info.Right; }
	_vec3	 GetUp()    { return m_Info.Up   ; }
	_vec3	 GetLook()  { return m_Info.Look ; }
	_vec3	 GetNormalRight() { return *D3DXVec3Normalize(&_vec3(), &m_Info.Right); }
	_vec3	 GetNormalUp()    { return *D3DXVec3Normalize(&_vec3(), &m_Info.Up)   ; }
	_vec3	 GetNormalLook()  { return *D3DXVec3Normalize(&_vec3(), &m_Info.Look) ; }
	_vec3	 GetPosition() { return m_Info.Pos; }
	_vec3	 GetAngle() { return m_vAngle; }
	_vec3	 GetScale() { return m_vScale; }
	_vec3	 GetDegreeAngle();

	_matrix  GetLocalMat() const { return m_Info.matrix; }
	_matrix  GetWorldMat() const;
	_matrix  GetParentRotTransMat()const { return m_ParentRotTransMat; }
	// Set
	void	 SetPosition(const _vec3& _position) { m_Info.Pos = _position; }
	void	 SetPosition(const _float& _x, const _float& _y, const _float& _z) { m_Info.Pos = { _x,_y,_z }; }

	void	 SetAngle(const _vec3& _angle) { m_vAngle = _angle; }
	void	 SetAngle(const _float& _x, const _float& _y, const _float& _z) { m_vAngle = { _x,_y,_z }; }

	void	 SetScale(const _vec3& _scale) { m_vScale = _scale; }
	void	 SetScale(const _float& _x, const _float& _y, const _float& _z) { m_vScale = { _x,_y,_z }; }

	void	 SetDirection(const _vec3& _dir);
	void	 SetDirection(const _vec3& _dir,const _float& fTimeDelta);

	void	 SetLookAt(const _vec3& _dir, const _vec3& _up);
	void	 SetLookAt(const _quat& _lookAt);
	void	 SetMatrix(const _matrix* _mat) { m_Info.matrix = *_mat; }
	void	 SetLookRotate(const _float& angle) { m_vAngle.y = angle; }
	// Add
	void	 Translate(const _vec3& _position) { m_Info.Pos += _position; }
	void	 Rotate(const _vec3& _angle) { m_vAngle += _angle; }
	void	 Rotate(const _vec3& _axis, const _float& _angle, const _bool& _rotZ = false);
	void	 Rotate(const INFO& _eInfoID, const _float& _angle);
	void	 Rotate(const _float& _x, const _float& _y, const _float& _z);

	void	 RotateSlerp(const _vec3& _angle, const _float& t);
	void	 RotateSlerp(const _vec3& _axis, const _float& _angle, const _float& t);

	void	 RotateByAxis(_float _fDeltaAngle, const _vec3& _vRotAxis);

	void	 AddScale(const _vec3& _scale) { m_vScale += _scale; }

	void SetParentBoneMatrix(const _matrix* _pParentBoneMatrix) { m_pParentBoneMatrix = _pParentBoneMatrix; }
	const _matrix* GetParentBoneMatrixPointer() const { return m_pParentBoneMatrix; }
	_bool IsZeroAngle();
private:
	INFO_MATRIX    m_Info;
	_vec3	m_vScale;
	_vec3	m_vAngle;
	const _matrix* m_pParentBoneMatrix = nullptr;
	_matrix			m_ParentRotTransMat;
};
END