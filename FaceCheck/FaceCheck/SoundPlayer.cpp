#include "StdAfx.h"
#include "SoundPlayer.h"
#include <Mmsystem.h>
SoundPlayer::SoundPlayer(void)
{
	m_hThread = NULL;
	m_bStop = FALSE;
	m_bPlaying = FALSE;
}

SoundPlayer::~SoundPlayer(void)
{
	StopPlayLoop();
	CSingleLock _lockList(&m_soundSec, TRUE);
	for (list<SoundData>::iterator itr = m_soundList.begin(); itr != m_soundList.end(); itr++)
	{
		if (itr->bResource)
			free((void*)itr->lpszData);
	}
}

DWORD SoundPlayer::_PlayLoop(LPVOID param)
{
	return ((SoundPlayer*)param)->PlayLoop();
}

DWORD SoundPlayer::PlayLoop()
{
	while (true)
	{
		CSingleLock _lockPlay(&m_eventPlay, TRUE);
		while (m_bStop == FALSE && PlayOneSound() == 0)
		{
		}
		if (m_bStop)
			break;
	}

	return 0;
}

int SoundPlayer::StartPlayLoop()
{
	if (m_hThread != NULL)
		return 0;
	m_bStop = FALSE;
	m_hThread = CreateThread(NULL, 0, _PlayLoop, (LPVOID)this, 0, 0);
	if (m_hThread == NULL)
		return -1;
	return 0;
}

int SoundPlayer::StopPlayLoop()
{
	if (m_hThread == NULL)
		return 0;
	InterlockedExchange((LONG*)&m_bStop, TRUE);
	m_eventPlay.SetEvent();
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
	return 0;
}

int	SoundPlayer::PlayOneSound()
{
	CSingleLock _lockList(&m_soundSec, TRUE);
	if (m_soundList.empty())
		return -1;
	InterlockedExchange((LONG*)&m_bPlaying, TRUE);
	SoundData data = m_soundList.front();
	m_soundList.pop_front();
	_lockList.Unlock();
	if (data.bResource)
		PlaySound(data.lpszData, NULL, SND_SYNC | SND_RESOURCE);
	else
	{
		PlaySound(data.lpszData, NULL, SND_SYNC | SND_FILENAME);
		free((void*)data.lpszData);
	}
	InterlockedExchange((LONG*)&m_bPlaying, FALSE);
	return 0;
}

int SoundPlayer::PlaySoundResource(UINT id, BOOL bAlways)
{
	CSingleLock _lockList(&m_soundSec, TRUE);
	if (bAlways == FALSE && (!m_soundList.empty() || m_bPlaying))
		return -1;
	SoundData data = { MAKEINTRESOURCE(id), TRUE };
	m_soundList.push_back(data);
	m_eventPlay.SetEvent();
	return 0;
}

int SoundPlayer::PlaySoundFile(LPCTSTR lpszFileName, BOOL bAlways)
{
	CSingleLock _lockList(&m_soundSec, TRUE);
	if (bAlways == FALSE && (!m_soundList.empty() || m_bPlaying))
		return -1;
	SoundData data = { _tcsdup(lpszFileName), FALSE };
	m_soundList.push_back(data);
	m_eventPlay.SetEvent();
	return 0;
}
