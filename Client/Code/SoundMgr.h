#pragma once
#include "fmod.hpp"
class CSoundMgr {
public:
	static CSoundMgr* GetInstance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr;

		return m_pInstance;
	}
	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	enum CHANNELID { BGM, PLAYERBOOSTER, DOOR, VOICE, BULLET, ENEMY, EFFECT, RADIO, UI, MAXCHANNEL };
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();

	void Release();
public:
	//void PlaySound(const wstring& pSoundKey, CHANNELID eID);
	//void PlaySound(const wstring& pSoundKey, CHANNELID eID, DWORD dwMode);
	_float GetChannelFreq(CHANNELID eID);
	void SetChannelFreq(CHANNELID eID, const _float& Freq);
	void PlaySFX(const wstring& pSoundKey, CHANNELID eID);
	void PlaySFX(const wstring& pSoundKey, CHANNELID eID, DWORD dwMode);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void SetVolume(CHANNELID eID, _float volume);
	void StopAll();

private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_pInstance;
	// ���� ���ҽ� ������ ���� ��ü 
	//map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	map<TCHAR*, FMOD::Sound*> m_mapSound;

	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	//FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	FMOD::Channel* channel[MAXCHANNEL];

	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	//FMOD_SYSTEM* m_pSystem;
	FMOD::System* system;

	FMOD_CHANNELGROUP* pBoosterChannelGroup;

};

