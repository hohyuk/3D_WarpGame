#ifndef AniCtrl_h__
#define AniCtrl_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CAniCtrl : public CBase
{
private:
	explicit CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	explicit CAniCtrl(const CAniCtrl& rhs);
	virtual ~CAniCtrl();

public: 
	LPD3DXANIMATIONCONTROLLER		Get_AnimationCtrl() { return m_pAniCtrl; }
	_bool							Is_AnimationSetEnd();

public:
	HRESULT			Ready_AnimationCtrl();

	void			Set_AnimationSet(const _uint& iIndex);

	void			Play_Animation(const _float& fTimeDelta);
	_float			GetAccTime()const { return m_fAccTime; }		// 현재 애님 시간
private:
	LPD3DXANIMATIONCONTROLLER			m_pAniCtrl;

	_uint								m_iCurrentTrack;
	_uint								m_iNewTrack;

	_float								m_fAccTime;
	_uint								m_iOldAniIdx;

	_double								m_dPeriod = 0.0;				// 하나의 애님의 총 재생시간

public:
	static CAniCtrl*			Create(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	static CAniCtrl*			Create(const CAniCtrl& rhs);
	virtual void				Free();
};

END

#endif // AniCtrl_h__
