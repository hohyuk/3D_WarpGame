#pragma once

namespace Client {
	typedef	signed char				_byte;
	typedef	unsigned char			_ubyte;

	typedef wchar_t					_tchar;

	typedef	signed short			_short;
	typedef	unsigned short			_ushort;

	typedef	signed int				_int;
	typedef	unsigned int			_uint;

	typedef	signed long				_long;
	typedef	unsigned long			_ulong;

	typedef	float					_float;
	typedef	double					_double;

	typedef bool					_bool;
	typedef	D3DXVECTOR2				_vec2;
	//typedef	D3DXVECTOR3				_vec3;
	typedef	D3DXVECTOR4				_vec4;

	//typedef	D3DXMATRIX				_matrix;

	//typedef		D3DXQUATERNION			_quat;
	class _matrix;
	class _vec3 : public D3DXVECTOR3 {
	public:
		_vec3() { ZeroMemory(this, sizeof(_vec3)); }
		_vec3(const _float& x, const _float& y, const _float& z) : D3DXVECTOR3(x, y, z) {}
		_vec3(const D3DXVECTOR3& vector3) : D3DXVECTOR3(vector3) {};
	public:
		inline _float GetLength() const;
		inline _float GetDistance(const _vec3& vDest) const;
		inline _float GetAngle(_vec3* vDest, const bool& isDegree = false) const;
		inline _vec3  Normalize();
		inline _float Dot(const _vec3* vDest) const;
		inline _vec3  Cross(const _vec3* vDest) const;
		inline _vec3* TransformNormal(_matrix* matTrans);
		inline _vec3* TransformCoord(_matrix* matTrans);
		static _vec3  GetVec3FromAngleZ(_float angle, const bool& isDegree = false) {
			if (isDegree) angle = D3DXToRadian(angle);
			return { cosf(angle), sinf(angle), 0.f };
		}
	};

	class _quat : public D3DXQUATERNION {
	public:
		_quat() {}
		_quat(const D3DXQUATERNION& quat) : D3DXQUATERNION(quat) {};
	public:

	};

	class _matrix : public D3DXMATRIX {
	public:
		_matrix() {}
		_matrix(const D3DXMATRIX& mat) : D3DXMATRIX(mat) {};
	public:
		inline _matrix* SetIdentity();
		inline _matrix* Scaling(const _float& x, const _float& y, const _float& z);
		inline _matrix* Scaling(const _vec3& vScale);
		inline _matrix* Translation(const _float& x, const _float& y, const _float& z);
		inline _matrix* Translation(const _vec3& vTrans);
		inline _matrix* LookAt(const _vec3* pLook, const _vec3* pUp);
		inline _matrix* LookAtLH(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp);
		inline _matrix* PerspectiveFovLH(const _float& fovY, const _float& aspect, const _float& zn, const _float& zf);

	};
}

#include "Typedef.inl"