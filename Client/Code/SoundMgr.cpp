#include "framework.h"
#include "SoundMgr.h"

CSoundMgr* CSoundMgr::m_pInstance = nullptr;
CSoundMgr::CSoundMgr() {
	system = nullptr;
}


CSoundMgr::~CSoundMgr() {
	Release();
}

void CSoundMgr::Initialize() {
	FMOD_RESULT       result;

	result = FMOD::System_Create(&system);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	result = system->init(32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();
}
void CSoundMgr::Release() {
	for (auto& Mypair : m_mapSound) {
		delete[] Mypair.first;
		Mypair.second->release();
	}
	m_mapSound.clear();
	system->close();
	system->release();
}

_float CSoundMgr::GetChannelFreq(CHANNELID eID) {
	_float fFreq;
	channel[eID]->getFrequency(&fFreq);
	return fFreq;
}

void CSoundMgr::SetChannelFreq(CHANNELID eID, const _float& Freq) {
	channel[eID]->setFrequency(Freq);
	system->update();
}

void CSoundMgr::PlaySFX(const wstring& pSoundKey, CHANNELID eID) {
	map<TCHAR*, FMOD::Sound*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter) {
		return pSoundKey == iter.first;
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	//if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	//{
	system->playSound(iter->second, 0, false, &channel[eID]);
	system->update();
}

void CSoundMgr::PlaySFX(const wstring& pSoundKey, CHANNELID eID, DWORD dwMode) {
	map<TCHAR*, FMOD::Sound*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter) {
		return pSoundKey == iter.first;
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	//if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	//{
	system->playSound(iter->second, 0, false, &channel[eID]);
	channel[eID]->setMode(dwMode);
	system->update();
}

void CSoundMgr::PlayBGM(const TCHAR* pSoundKey) {
	map<TCHAR*, FMOD::Sound*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter) {
		return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	system->playSound(iter->second, 0, false, &channel[BGM]);
	channel[BGM]->setMode(FMOD_LOOP_NORMAL);
	system->update();
}

void CSoundMgr::StopSound(CHANNELID eID) {
	channel[eID]->stop();
}

void CSoundMgr::SetVolume(CHANNELID eID, _float volume) {
	channel[eID]->setVolume(volume);
}

void CSoundMgr::StopAll() {
	for (int i = 0; i < MAXCHANNEL; ++i)
		channel[i]->stop();
}

void CSoundMgr::LoadSoundFile() {
	_finddata_t fd;

	long long handle = (long long)_findfirst("../../Resource/Sound/*.*", &fd);

	if (handle == 0)
		return;

	int iResult = 0;

	char szCurPath[128] = "../../Resource/Sound/";
	char szFullPath[128] = "";

	while (iResult != -1) {
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, fd.name);
		FMOD::Sound* pSound = nullptr;

		FMOD_RESULT eRes = system->createSound(szFullPath, FMOD_DEFAULT, 0, &pSound);

		if (eRes == FMOD_OK) {
			int iLength = (int)strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	}
	system->update();
	_findclose(handle);
}
