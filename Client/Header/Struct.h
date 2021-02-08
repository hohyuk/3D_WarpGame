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
	_float fAppearanceSec;						// ���� ����ð� (��ȸ�ϸ鼭 üũ)
	MONSTER::E_TYPE eMonsterType;				// (TYPE_NORMAL, TYPE_BOSS)
	ATTACK_PATTERN::E_PATTERN eAttackPattern;	// źȯ ����(0~15)
	ITEM::E_TYPE eItemType;						// ������ ������ Ÿ�� (power, max_power, buddy)
	_float fScaleX;				// ���� �ʺ� ����
	_float fScaleY;				// ���� ���� ����
	_float fScaleZ;				// ���� ���� ����
	_float fHp;				// ���� HP
	_int iMonsterNum;		// �ش� Ÿ���� ���Ͱ� �� ���� ��������
	_float fOffsetMaxX;		// ���� X��ǥ���� ������ ������ �ִ� ���� (���� ����)
	_float fOffsetMaxZ;		// ���� Y��ǥ���� ������ ������ �ִ� ���� (���� ����)
	_float fOffsetMaxSec;	// �ش� ������ �����ϴµ� �ִ� ������ Ÿ��(�� ������ ����� ���!)
	vector<ROUTING_INFO> vecRoutingInfos;
}MONSTER_GEN_INFO;

// �ִϸ��̼� ����
typedef struct _anim_info_line {
	//int iState = -1;					// ���¸� ��Ÿ���� �������� 0�� �⺻������ Idle
	int iStartFrameIndex = 0;			// �ִϸ��̼� ���� �ε���
	int iFrameCount = 0;				// ���� �ε����������� ����� �� ������.
	float fTotalTime = 0.f;				// �� �ִϸ��̼� �� ���� �ð�
	int iCountToRepeat = 0;				// �� �ִϸ��̼��� �� �� ����? (0 - ����, 1 - 1ȸ�ϰ� ��(�� �� ������ IDLE�� ��ȯ))
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
	int iAnimIndex = 0;				// ������ �ִ� �ε���
	int iCol = 1;					// �ִ� ��Ʋ�� �̹������� ���� �� (������ �������� ��� ���� ���ϴµ� ����.)
	int iStartFrameIndex = 0;		// �ִϸ��̼� ���� �ε���
	int iFrameCount = 1;			// ���� �ε����������� ����� �� �Ƽ�
	float fTotalTime = 0.f;			// �ִ� �� ����ð�
	int iCountToRepeat = 0;			// �ִ� �ݺ� Ƚ�� (0 - ����)
	bool bIsReversePlay = false;	// �Ųٷ� ����� ������?
}AnimInfo;

// �ִ� ��� ó�� ����ü
typedef struct _anim_processing_info {
	float fAnimElapsedTime = 0.f;
	int iCurrentIndex = 0;
	int iRepeatedCount = 0;
}AnimProcessingInfo;


// ������ ����ü
typedef struct tagRay
{
	_vec3 vOrigin;	// ������ ��ġ
	_vec3 vDir;		// ������ ���⺤��
}RAY;

// ����Ʈ ����ü

typedef struct tagQuestInfo {
	_tchar szSpeaker[32];
	_tchar szScript[128];
	_vec4  rcScriptRect;
}QUEST_INFO;