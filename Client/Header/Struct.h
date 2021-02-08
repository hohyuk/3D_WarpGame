#pragma once

typedef struct _routing_info {
	_routing_info(_float _fX, _float _fY, _float _fZ, _float _fSecToReach)
		:
		vPoint(_vec3(_fX, _fY, _fZ)),
		fSecToReach(_fSecToReach)
	{}
	_routing_info(_vec3 _vPoint, _float _fSecToReach)
		:
		vPoint(_vPoint),
		fSecToReach(_fSecToReach)
	{}
	_vec3 vPoint;
	_float fSecToReach;
}ROUTING_INFO;

typedef struct _monster_generation_info {
	_float fAppearanceSec;						// 몬스터 등장시간 (순회하면서 체크)
	MONSTER::E_TYPE eMonsterType;				// (TYPE_NORMAL, TYPE_BOSS)
	ATTACK_PATTERN::E_PATTERN eAttackPattern;	// 탄환 패턴(0~15)
	ITEM::E_TYPE eItemType;						// 떨구는 아이템 타입 (power, max_power, buddy)
	_float fScaleX;				// 몬스터 너비 배율
	_float fScaleY;				// 몬스터 높이 배율
	_float fScaleZ;				// 몬스터 깊이 배율
	_float fHp;				// 몬스터 HP
	_int iMonsterNum;		// 해당 타입의 몬스터가 몇 마리 나오는지
	_float fOffsetMaxX;		// 몬스터 X좌표에서 평행히 떨어진 최대 정도 (음수 포함)
	_float fOffsetMaxZ;		// 몬스터 Y좌표에서 평행히 떨어진 최대 정도 (음수 포함)
	_float fOffsetMaxSec;	// 해당 지점에 도달하는데 주는 딜레이 타임(초 단위로 양수만 취급!)
	vector<ROUTING_INFO> vecRoutingInfos;
}MONSTER_GEN_INFO;

// 애니메이션 관련
typedef struct _anim_info_line {
	//int iState = -1;					// 상태를 나타내는 열거형값 0은 기본적으로 Idle
	int iStartFrameIndex = 0;			// 애니메이션 시작 인덱스
	int iFrameCount = 0;				// 시작 인덱스에서부터 출력할 총 프레임.
	float fTotalTime = 0.f;				// 한 애니메이션 총 진행 시간
	int iCountToRepeat = 0;				// 한 애니메이션을 몇 번 진행? (0 - 무한, 1 - 1회하고 끝(별 일 없으면 IDLE로 전환))
	bool bIsReversePlay = false;
}AnimInfoLine;

typedef struct _anim_info {
public:
	_anim_info(int _iAnimIndex = 0, int _iCol = 1, int _iStartFrameIndex = 0, int _iFrameCount = 0, float _fTotalTime = 0.f, int _iCountToRepeat = 0, bool _bIsReversePlay = false) :
		iAnimIndex(_iAnimIndex),
		iCol(_iCol),
		iStartFrameIndex(_iStartFrameIndex),
		iFrameCount(_iFrameCount),
		fTotalTime(_fTotalTime),
		iCountToRepeat(_iCountToRepeat),
		bIsReversePlay(_bIsReversePlay)
	{}

public:
	int iAnimIndex = 0;				// 실행할 애님 인덱스
	int iCol = 1;					// 애님 아틀라스 이미지에서 열의 수 (실행할 프레임의 행과 열을 구하는데 쓰임.)
	int iStartFrameIndex = 0;		// 애니메이션 시작 인덱스
	int iFrameCount = 1;			// 시작 인덱스에서부터 출력할 총 컷수
	float fTotalTime = 0.f;			// 애님 총 진행시간
	int iCountToRepeat = 0;			// 애님 반복 횟수 (0 - 무한)
	bool bIsReversePlay = false;	// 거꾸로 재생할 것인지?
}AnimInfo;

// 애님 재생 처리 구조체
typedef struct _anim_processing_info {
	float fAnimElapsedTime = 0.f;
	int iCurrentIndex = 0;
	int iRepeatedCount = 0;
}AnimProcessingInfo;


// 광선의 구조체
typedef struct tagRay
{
	_vec3 vOrigin;	// 광선의 위치
	_vec3 vDir;		// 광선의 방향벡터
}RAY;

// 퀘스트 구조체

typedef struct tagQuestInfo {
	_tchar szSpeaker[32];
	_tchar szScript[128];
	_vec4  rcScriptRect;
}QUEST_INFO;