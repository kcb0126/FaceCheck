#pragma once

#include <list>
#include <afxmt.h>
using namespace std;
class SoundPlayer
{
	struct SoundData
	{
		LPCTSTR lpszData;
		BOOL	bResource;
	};
public:
	SoundPlayer(void);
	~SoundPlayer(void);
public:
	int StartPlayLoop();
	int StopPlayLoop();
	int PlaySoundResource(UINT id, BOOL bAlways = FALSE);
	int PlaySoundFile(LPCTSTR, BOOL bAlways = FALSE);
protected:
	static DWORD WINAPI _PlayLoop(LPVOID param);
	DWORD	PlayLoop();
	int		PlayOneSound();
protected:
	list<SoundData>		m_soundList;
	CCriticalSection	m_soundSec;
	CEvent				m_eventPlay;
	HANDLE				m_hThread;
	volatile BOOL		m_bStop;
	volatile BOOL		m_bPlaying;
};
