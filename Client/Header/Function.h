#pragma once 
#include "Export_Function.h"
namespace Client
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
	DWORD Safe_Release_Delete(T& pointer)
	{
		DWORD	dwRefCnt = 0;
		if (NULL != pointer)
		{
			dwRefCnt = pointer->Release();
			if (dwRefCnt == 0)
			{
				delete pointer;
				pointer = NULL;
			}
		}
		return dwRefCnt;
	}

	template <typename T>
	void Safe_Single_Destory(T& pointer)
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

	template<typename T>
	inline bool IsBetween(const T& _value, const T& _from, const T& _to) {
		return _value > _from && _value < _to;
	}

	// Ŭ���� : �� ����
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

	template<typename T>
	T Wrap(T _Value,T _Min, T _Max)
	{
		T n = fmod(_Value - _Min, _Max - _Min);
		return (n >= 0) ? (n + _Min) : (n + _Max);
	}

	// ���� ��ƿ
	inline _bool GetRandomBool() {
		return rand() % 2 == 0;
	}

	inline _float GetRandomFloat(void)
	{
		return static_cast <_float> (rand()) / static_cast <_float> (RAND_MAX);
	}

	inline _int GetNumberMinBetweenMax(_int _iMin, _int _iMax) {
		if (_iMin > _iMax) abort();

		return rand() % (_iMax - _iMin + 1) + _iMin;
	}

	inline _float GetNumberMinBetweenMax(_float _fMin, _float _fMax) {
		if (_fMin > _fMax) abort();

		_float fT = GetRandomFloat();
		return _fMin * (1.f - fT) + _fMax * fT;
	}
	inline _vec3 GetRandomDirection() {
		_vec3 vRandDir;
		
		while (D3DXVec3Length(&vRandDir) < 0.0001f) {
			vRandDir.x = GetNumberMinBetweenMax(-100.f, 100.f);
			vRandDir.y = GetNumberMinBetweenMax(-100.f, 100.f);
			vRandDir.z = GetNumberMinBetweenMax(-100.f, 100.f);
		}

		D3DXVec3Normalize(&vRandDir, &vRandDir);

		return vRandDir;
	}

	// ���� ��ƿ
	inline _vec3 GetRotationAxis(const _vec3& vU, const _vec3& vV) {
		_vec3 vRotAxis;
		D3DXVec3Cross(&vRotAxis, &vU, &vV);
		D3DXVec3Normalize(&vRotAxis, &vRotAxis);
		return vRotAxis;
	}
	inline _float GetRotationAngle(const _vec3& vU, const _vec3& vV) {
		_vec3 vUnitU;
		_vec3 vUnitV;
		_float fDot;
		D3DXVec3Normalize(&vUnitU, &vU);
		D3DXVec3Normalize(&vUnitV, &vV);
		fDot = Clamp(D3DXVec3Dot(&vUnitU, &vUnitV), -1.f, 1.f);
		return acosf(fDot);
	}
	inline _float GetWeightByCos(_float _fCosRadian) {	// 0~2pi�� ���� ��������� 0~1�� ���� ��ȯ
		return 0.5f * cosf(_fCosRadian) + 0.5f;
	}
	inline _float GetWeightByValue(_float _fValue, _float _fMin, _float _fMax) {	// _fMin�� �������� 0�� ����� ����, _fMax�� �������� 1�� ����� ���� ��ȯ
		if (_fMin > _fMax) abort();

		return Clamp((_fValue - _fMin) / (_fMax - _fMin), 0.f, 1.f);
	}
	inline _float GetValueByWeight(_float _fWeight, _float _fZero, _float _fOne) {	// 0~1�� fZero, fOne�� ������ ���� ���� => ����
		Clamp(&_fWeight, 0.f, 1.f);
		return _fZero * (1.f - _fWeight) + _fOne * _fWeight;
	}
	inline _vec3 GetReflectionVector(const _vec3& _vIncident, const _vec3& _vNormal) {	// �ݻ纤��
		_vec3 vNormal;
		D3DXVec3Normalize(&vNormal, &_vNormal);

		return _vIncident + 2.f * vNormal * (-D3DXVec3Dot(&_vIncident, &vNormal));
	}

	// ��ȿȭ ��ü ����
	template <typename T>
	inline void CollectInvalidObjects(list<T*>& _list)
	{
		for (auto& pObj : _list) 
		{ 
			if(!pObj->IsValid()) 
			{ 
				Client::Safe_Release(pObj); 
			} 
		}
		_list.remove_if([](auto& pObj) 
		{ 
			return pObj == nullptr;
		});
	}

	/*inline void CollectInvalidObjects(Engine::CLayer* _layer)
	{
		CollectInvalidObjects(_layer->GetLayerList());
		auto pMap = _layer->GetLayerMap();
		for (auto iter = pMap.begin(); iter != pMap.end(); ) {
			if(!iter->second->IsValid()) {
				Client::Safe_Release(iter->second);
				iter = pMap.erase(iter);
			}
			else {
				iter++;
			}
		}
	}*/

	//��ü �����
	template< typename ContainerT, typename PredicateT >
	void erase_if(ContainerT& items, const PredicateT& predicate) {
		for (auto it = items.begin(); it != items.end(); ) {
			if (predicate(*it)) 
				it = items.erase(it);
			else ++it;
		}
	}

	// ü�� ��ġ ��� (���� ������)
	inline float Linear_Interpolation(const float& hp, const float& maxHp, const int& barLength, const float& start = 0.f)
	{
		float hpRate = hp / maxHp;			// ���� hp ����
		float hpBar = start * (1.f - hpRate) + barLength * hpRate;					// ���������� ����
		return hpBar;
	}

	inline float Distance_PosXZ(const D3DXVECTOR3& rDst, const D3DXVECTOR3& rSrc)
	{
		D3DXVECTOR3 vDist = rDst - rSrc;

		return sqrtf(vDist.x * vDist.x + vDist.z * vDist.z);
	}

	inline float Distance_Pos(const D3DXVECTOR3& rDst, const D3DXVECTOR3& rSrc)
	{
		D3DXVECTOR3 vDist = rDst - rSrc;

		return sqrtf(vDist.x * vDist.x + vDist.y * vDist.y + vDist.z * vDist.z);
	}

	inline int GetLineCount(const _tchar* szString) {
		int iLineCount = 0;
		for (int i = 0; i < lstrlen(szString); i++) {
			if (szString[i] == '\n')
				iLineCount++;
		}
		return iLineCount;
	}

	inline float fGetLineCount(const _tchar* szString) {
		int iLineCount = 0;
		for (int i = 0; i < lstrlen(szString); i++) {
			if (szString[i] == '\n')
				iLineCount++;
		}
		return (float)iLineCount;
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

		ans.x = asinf(t2);
		ans.y = atan2f(t3, t4);
		ans.z = atan2f(t1, t0);

		return ans;
	}

	inline D3DXQUATERNION ToQuaternion(const D3DXVECTOR3& eulerAngle) {
		D3DXQUATERNION ans;
		float t0 = cosf(eulerAngle.z * 0.5f);
		float t1 = sinf(eulerAngle.z * 0.5f);
		float t2 = cosf(eulerAngle.y * 0.5f);
		float t3 = sinf(eulerAngle.y * 0.5f);
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

}