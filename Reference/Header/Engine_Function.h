#pragma once

namespace Engine
{
	template <typename T>
	DWORD Safe_Release(T& pointer)
	{
		DWORD	dwRefCnt = 0;
		if (NULL != pointer)
		{
			dwRefCnt = pointer->Release();
			if (dwRefCnt == 0)
				pointer = NULL;
		}
		return dwRefCnt;
	}

	template <typename T>
	DWORD Safe_AddRef(T& pointer) {
		DWORD	dwRefCnt = 0;
		if (NULL != pointer)
			dwRefCnt = pointer->AddRef();

		return dwRefCnt;
	}

	template <typename T>
	void Safe_Single_Destroy(T& pointer)
	{
		if (NULL != pointer)
		{
			pointer->DestroyInstance();
			pointer = NULL;
		}
	}

	template <typename T>
	void Safe_Delete(T& pointer)
	{
		if (NULL != pointer)
		{
			delete pointer;
			pointer = NULL;
		}
	}

	template <typename T>
	void Safe_Delete_Array(T& pointer)
	{
		if (NULL != pointer)
		{
			delete[] pointer;
			pointer = NULL;
		}
	}






	//////////////////////////////////////////////////////////////////
	/////////////////////////////////Functor(함수 객체)//////////////////////////

	class CTag_Finder
	{
	public:
		explicit CTag_Finder(const _tchar* pTag)
			: m_pTargetTag(pTag)
		{
		}
		~CTag_Finder() {		}
	public:
		template<typename T>
		bool operator()(const T& pair)
		{
			if (0 == lstrcmpW(m_pTargetTag, pair.first))
			{
				return true;
			}

			return false;
		}

	private:
		const _tchar*		m_pTargetTag = nullptr;
	};

	class CTag_FinderA
	{
	public:
		explicit CTag_FinderA(const char* pTag)
			: m_pTargetTag(pTag)
		{
		}
		~CTag_FinderA() {		}
	public:
		template<typename T>
		bool operator()(const T& pair)
		{
			if (0 == strcmp(m_pTargetTag, pair.first))
			{
				return true;
			}

			return false;
		}

	private:
		const char*		m_pTargetTag = nullptr;
	};

	class CDeleteObj
	{
	public:
		explicit CDeleteObj(void) {}
		~CDeleteObj(void) {}
	public: // operator
		template <typename T>
		void operator () (T& pInstance)
		{
			_ulong dwRefCnt = 0;

			dwRefCnt = pInstance->Release();

			if (0 == dwRefCnt)
				pInstance = nullptr;
		}
	};

	// 연관컨테이너 삭제용
	class CDeleteMap
	{
	public:
		explicit CDeleteMap(void) {}
		~CDeleteMap(void) {}
	public: // operator	
		template <typename T>
		void operator () (T& Pair)
		{
			_ulong dwRefCnt = 0;

			dwRefCnt = Pair.second->Release();

			if (0 == dwRefCnt)
				Pair.second = NULL;
		}
	};

	template<typename T>
	void Clamp(T* _pValue, T _Min, T _Max) {
		if (*_pValue < _Min)		*_pValue = _Min;
		else if (*_pValue > _Max)	*_pValue = _Max;
	}

	template<typename T>
	T Clamp(T _Value, T _Min, T _Max) {
		Clamp(&_Value, _Min, _Max);
		return _Value;
	}

	// 수학 유틸
	// 회전 축
	inline _vec3 GetRotationAxis(const _vec3& vU, const _vec3& vV) {
		_vec3 vRotAxis;
		D3DXVec3Cross(&vRotAxis, &vU, &vV);
		D3DXVec3Normalize(&vRotAxis, &vRotAxis);
		return vRotAxis;
	}

	// 회전 각
	inline _float GetRotationAngle(const _vec3& vU, const _vec3& vV) {
		_vec3 vUnitU;
		_vec3 vUnitV;
		_float fDot;
		D3DXVec3Normalize(&vUnitU, &vU);
		D3DXVec3Normalize(&vUnitV, &vV);
		fDot = Clamp(D3DXVec3Dot(&vUnitU, &vUnitV), -1.f, 1.f);
		return acosf(fDot);
	}

	// 랜덤 범위
	inline _int GetRandomInt(_int _iMin, _int _iMax)
	{
		if (_iMin >= _iMax)
			return _iMin;
		_int value = _iMax - _iMin;
		_int iRandNum = rand() % value;

		return iRandNum + _iMin;
	}

	inline _float GetRandomFloat(_float _fMin, _float _fMax)
	{
		if (_fMin >= _fMax)
			return _fMin;

		_float fRandNum = (rand() % 10000) * 0.0001f;

		return (fRandNum * (_fMax - _fMin)) + _fMin;
	}

	inline void GetRandomVector(_vec3* _pOut, _vec3* _pMin, _vec3* _pMax)
	{
		if (!_pOut || !_pMin || !_pMax)
			return;

		_pOut->x = GetRandomFloat(_pMin->x, _pMax->x);
		_pOut->y = GetRandomFloat(_pMin->y, _pMax->y);
		_pOut->z = GetRandomFloat(_pMin->z, _pMax->z);
	}

	inline D3DXQUATERNION* D3DXQuaternionLookRotation(D3DXQUATERNION* pOut, const D3DXVECTOR3* pLookAt, const D3DXVECTOR3* pUp) {

		_vec3 nLook, nUp, nRight;
		D3DXVec3Normalize(&nLook, pLookAt);
		D3DXVec3Normalize(&nUp, pUp);

		D3DXVec3Cross(&nRight, &nUp, &nLook);
		D3DXVec3Normalize(&nRight, &nRight);
		D3DXVec3Cross(&nUp, &nLook, &nRight);
		_matrix matRot;
		D3DXMatrixIdentity(&matRot);
		matRot.m[0][0] = nRight.x; matRot.m[0][1] = nRight.y; matRot.m[0][2] = nRight.z;
		matRot.m[1][0] = nUp.x;    matRot.m[1][1] = nUp.y;    matRot.m[1][2] = nUp.z;
		matRot.m[2][0] = nLook.x;  matRot.m[2][1] = nLook.y;  matRot.m[2][2] = nLook.z;

		D3DXQuaternionRotationMatrix(pOut, &matRot);
		return pOut;
	}

	inline D3DXVECTOR3 ToEulerianAngle(const D3DXQUATERNION& pQt) {
		D3DXVECTOR3 ans;

		float q2sqr = pQt.y * pQt.y;
		float t0 = -2.0f * (q2sqr + pQt.z * pQt.z) + 1.0f;
		float t1 = +2.0f * (pQt.x * pQt.y + pQt.w * pQt.z);
		float t2 = -2.0f * (pQt.x * pQt.z - pQt.w * pQt.y);
		float t3 = +2.0f * (pQt.y * pQt.z + pQt.w * pQt.x);
		float t4 = -2.0f * (pQt.x * pQt.x + q2sqr) + 1.0f;

		t2 = t2 > 1.0f ? 1.0f : t2;
		t2 = t2 < -1.0f ? -1.0f : t2;

		ans.y = asinf(t2);
		ans.x = atan2f(t3, t4);
		ans.z = atan2f(t1, t0);

		return ans;
	}

	inline D3DXQUATERNION ToQuaternion(const D3DXVECTOR3& eulerAngle) {
		D3DXQUATERNION ans;
		float t0 = cosf(eulerAngle.y * 0.5f);
		float t1 = sinf(eulerAngle.y * 0.5f);
		float t2 = cosf(eulerAngle.z * 0.5f);
		float t3 = sinf(eulerAngle.z * 0.5f);
		float t4 = cosf(eulerAngle.x * 0.5f);
		float t5 = sinf(eulerAngle.x * 0.5f);

		ans.w = t2 * t4 * t0 + t3 * t5 * t1;
		ans.x = t3 * t4 * t0 - t2 * t5 * t1;
		ans.y = t2 * t5 * t0 + t3 * t4 * t1;
		ans.z = t2 * t4 * t1 - t3 * t5 * t0;
		return ans;
	}

	inline D3DXQUATERNION ToQuaternion(const float& yaw, const float& pitch, const float& roll) {
		D3DXQUATERNION ans;
		float t0 = cosf(yaw * 0.5f);
		float t1 = sinf(yaw * 0.5f);
		float t2 = cosf(roll * 0.5f);
		float t3 = sinf(roll * 0.5f);
		float t4 = cosf(pitch * 0.5f);
		float t5 = sinf(pitch * 0.5f);

		ans.w = t2 * t4 * t0 + t3 * t5 * t1;
		ans.x = t3 * t4 * t0 - t2 * t5 * t1;
		ans.y = t2 * t5 * t0 + t3 * t4 * t1;
		ans.z = t2 * t4 * t1 - t3 * t5 * t0;
		return ans;
	}

	// 뷰포트 행렬 얻기
	inline _matrix GetViewportMatrix(const D3DVIEWPORT9& vp) {
		_matrix matViewport;
		D3DXMatrixIdentity(&matViewport);

		matViewport._11 = vp.Width * 0.5f;
		matViewport._22 = -(vp.Height * 0.5f);
		matViewport._33 = vp.MaxZ - vp.MinZ;
		matViewport._41 = vp.X + vp.Width * 0.5f;
		matViewport._42 = vp.Y + vp.Height * 0.5f;
		matViewport._43 = vp.MinZ;

		return matViewport;
	}

	//반사벡터 (1.f미만 => 굴절, 1.f => 슬라이딩, 1.f초과 => 반사 )
	inline _vec3 GetReflectionVector(const _vec3& _vIncident, const _vec3& _vNormal, const _float& _fReflectivity = 2.f) {
		_vec3 vNormal;
		return _vIncident + _fReflectivity * vNormal * (-D3DXVec3Dot(&_vIncident, D3DXVec3Normalize(&vNormal, &_vNormal)));
	}

	// 클라이언트 커서 좌표얻기
	inline POINT GetClientCursorPoint(const HWND& _hWND)
	{
		POINT pt;
		GetCursorPos(&pt);				// 데스크탑 기준 좌표
		ScreenToClient(_hWND, &pt);		// 윈도우창 기준 좌표
		return pt;
	}

	// Ray
	inline RAY GetPickingRay(LPDIRECT3DDEVICE9 pGraphicDev, _matrix matWorld, POINT	ptMouse)
	{
		RAY ray;
		D3DVIEWPORT9		ViewPort;
		ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
		pGraphicDev->GetViewport(&ViewPort);

		// 뷰포트 -> 투영
		_vec3	vMousePos;
		vMousePos.x = (ptMouse.x / (ViewPort.Width * 0.5f)) - 1.f;
		vMousePos.y = (ptMouse.y / -(ViewPort.Height * 0.5f)) + 1.f;
		vMousePos.z = 0.f;

		// L * W * V * P * (P^-1)
		// L * W * V

		// 투영 -> 뷰 스페이스
		_matrix	matProj;
		pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
		D3DXMatrixInverse(&matProj, NULL, &matProj);
		D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

		// 뷰 스페이스 -> 월드
		_matrix	matView;
		pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matView, NULL, &matView);


		ray.vPos = _vec3(0.f, 0.f, 0.f);
		ray.vDir = vMousePos - ray.vPos;

		D3DXVec3TransformCoord(&ray.vPos, &ray.vPos, &matView);
		D3DXVec3TransformNormal(&ray.vDir, &ray.vDir, &matView);

		// 월드 -> 로컬
		_matrix	InverseMatWorld;

		D3DXMatrixInverse(&InverseMatWorld, NULL, &matWorld);

		D3DXVec3TransformCoord(&ray.vPos, &ray.vPos, &InverseMatWorld);
		D3DXVec3TransformNormal(&ray.vDir, &ray.vDir, &InverseMatWorld);

		return ray;
	}


	// Ray 카메라 (광선 벡터)
	inline RAY GetPickingRay(LPDIRECT3DDEVICE9 pGraphicDev, const POINT& ptMouse)
	{
		_vec3 vRay = _vec3(static_cast<FLOAT>(ptMouse.x), static_cast<FLOAT>(ptMouse.y), 0.f);
		_matrix matInvViewport, matInvProj, matInvView;
		D3DVIEWPORT9 vp;
		pGraphicDev->GetViewport(&vp);

		// 뷰포트 행렬의 역 구하기
		matInvViewport = GetViewportMatrix(vp);
		D3DXMatrixInverse(&matInvViewport, NULL, &matInvViewport);

		// 투영 행렬의 역 구하기
		pGraphicDev->GetTransform(D3DTS_PROJECTION, &matInvProj);
		D3DXMatrixInverse(&matInvProj, NULL, &matInvProj);

		// 뷰 행렬의 역 구하기
		pGraphicDev->GetTransform(D3DTS_VIEW, &matInvView);
		D3DXMatrixInverse(&matInvView, NULL, &matInvView);

		D3DXVec3TransformCoord(&vRay, &vRay, &(matInvViewport * matInvProj * matInvView));		// 카메라 공간
		_vec3 vCameraPos = _vec3(matInvView._41, matInvView._42, matInvView._43);
		vRay -= vCameraPos;
		D3DXVec3Normalize(&vRay, &vRay);

		return RAY{ vRay, vCameraPos };
	}

	// 광선 충돌 지점 얻기
	inline _vec3 GetHitPos(const _vec3& _V1, const _vec3& _V2, const _vec3& _V3, const _float& _fU, const _float& _fV) {
		return _V1 + _fU * (_V2 - _V1) + _fV * (_V3 - _V1);
	}

	// Ray Sphere충돌 1 - 블로그 참고 https://m.blog.naver.com/PostView.nhn?blogId=hermet&logNo=68084286&proxyReferer=https:%2F%2Fwww.google.com%2F
	inline _bool IsIntersectRaySphere(const RAY& _ray, const _vec3& vSpherePos, const _float& _fRadius)
	{

		return true;
	}

	// Ray Sphere충돌 2
	inline _bool IsRaySphereCollided(const RAY& _Ray, _float _fRadius, const _vec3& _vSpherePos, _float* pT = nullptr) {
		_vec3 vM = _Ray.vPos - _vSpherePos;
		_float fA = D3DXVec3Dot(&_Ray.vDir, &_Ray.vDir);				// u.u
		_float fB = 2.f * D3DXVec3Dot(&vM, &_Ray.vDir);					// 2(m.u)
		_float fC = D3DXVec3Dot(&vM, &vM) - _fRadius * _fRadius;		// m.m - r^2
		_float fD = fB * fB - 4.f * fA * fC;	// 판별식 b^2 - 4ac

		if (fD < 0.f)	// 판별식이 음수이면 충돌하지 않은 것이다.
			return false;

		_float fT1 = (-fB + sqrtf(fD)) / (2.f * fA);
		_float fT2 = (-fB - sqrtf(fD)) / (2.f * fA);
		_float fT = min(fT1, fT2);

		if (fT < 0.f)	// fT가 음수이면, 충돌하지 않은 것이다.
			return false;

		if (pT)
			*pT = fT;

		return true;
	}

	// Ray Box충돌 
	inline _bool IsIntersectRayToAABB(const RAY& _ray, const _vec3 * pDestMin, const _vec3 * pDestMax, const _matrix& pDestWorld) {
		_vec3	vDestMin, vDestMax;
		//_float	fMin, fMax;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, &pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, &pDestWorld);

		_float fMinX = (vDestMin.x - _ray.vPos.x) / _ray.vDir.x;
		_float fMaxX = (vDestMax.x - _ray.vPos.x) / _ray.vDir.x;

		if (fMinX > fMaxX)
		{
			float tmp = fMinX;
			fMinX = fMaxX;
			fMaxX = tmp;
		}

		_float fMinY = (vDestMin.y - _ray.vPos.y) / _ray.vDir.y;
		_float fMaxY = (vDestMax.y - _ray.vPos.y) / _ray.vDir.y;

		if (fMinY > fMaxY)
		{
			float tmp = fMinY;
			fMinY = fMaxY;
			fMaxY = tmp;
		}

		if ((fMinX > fMaxY) || (fMinY > fMaxX))
			return false;

		if (fMinY > fMinX)
			fMinX = fMinY;

		if (fMaxY < fMaxX)
			fMaxX = fMaxY;

		float tzmin = (vDestMin.z - _ray.vPos.z) / _ray.vDir.z;
		float tzmax = (vDestMin.z - _ray.vPos.z) / _ray.vDir.z;

		if (tzmin > tzmax)
		{
			float tmp = tzmin;
			tzmin = tzmax;
			tzmax = tmp;
		}

		if ((fMinX > tzmax) || (tzmin > fMaxX))
			return false;


		return true;
	}

	// 평면에 투영된 점 위치얻기
	inline _vec3 GetPointProjectedOntoPlane(const D3DXPLANE& _plPlane, const _vec3& _vPos) {
		_vec3 vPlaneNormal = _vec3(_plPlane.a, _plPlane.b, _plPlane.c);
		_float fK = D3DXVec3Dot(&vPlaneNormal, &_vPos) + _plPlane.d;
		return _vPos - fK * vPlaneNormal;
	}

	// 삼각형에 투영된 점 위치얻기
	inline _vec3 GetPointProjectedOntoTriangle(const _vec3& _vV1, const _vec3& _vV2, const _vec3& _vV3, const _vec3& _vPos) {
		D3DXPLANE plPlane;
		return GetPointProjectedOntoPlane(*D3DXPlaneFromPoints(&plPlane, &_vV1, &_vV2, &_vV3), _vPos);
	}

	// 세 정점으로부터 외적얻기 
	inline _vec3 GetCross(const _vec3& _vV1, const _vec3& _vV2, const _vec3& _vV3) {
		_vec3 vCross;
		D3DXVec3Cross(&vCross, &(_vV2 - _vV1), &(_vV3 - _vV1));
		return vCross;
	}

	inline _bool IsFacing(const _vec3& _vDir1, const _vec3& _vDir2) {
		_vec3 vNormalizedDir1, vNormalizedDir2;
		D3DXVec3Normalize(&vNormalizedDir1, &_vDir1);
		D3DXVec3Normalize(&vNormalizedDir2, &_vDir2);

		// 음수이면 마주 보고 있는 것이다.
		return D3DXVec3Dot(&vNormalizedDir1, &vNormalizedDir2) < 0.f;
	}

	// 구와 박스 충돌		// 출처: https://hoidu.tistory.com/entry/충돌처리-구와-AABB에-대한-충돌처리 [Du의 재미있는 프로그래밍 세상]
	inline _bool CollisionSphereAABB(const _vec3& _vPos,const _float& _fRadius, 
									 const _vec3& _vMax, const _vec3& _vMin, const _matrix * pWorldMat)
	{
		/*_vec3	vMin, vMax;
		D3DXVec3TransformCoord(&max, &max, &pObj->GetTransform()->GetWorldMat());
		D3DXVec3TransformCoord(&vMin, &min, &pObj->GetTransform()->GetWorldMat());*/
		if (_vMax.x < (_vPos.x - _fRadius) || _vMin.x >(_vPos.x + _fRadius)) return false;
		if (_vMax.y < (_vPos.y - _fRadius) || _vMin.y >(_vPos.y + _fRadius)) return false;
		if (_vMax.z < (_vPos.z - _fRadius) || _vMin.z >(_vPos.z + _fRadius)) return false;

		return true;
	}
}