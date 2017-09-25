#pragma once
#include "FrameProcessor.h"
#include "types.h"
#include "FaceRecogEngine.h"
#include "PersonDB.h"
#include "SoundPlayer.h"

#include <vector>
using namespace std;
class CFaceProcessorOutputView;
class CPersonLogView;

namespace KIP
{
	class FaceProcessor : public FrameProcessor
	{
	public:
		FaceProcessor(void);
		~FaceProcessor(void);

	public:
		virtual void setOptions();
		virtual void onDblClick(const CPoint & pt, const CRect & rc);

		list<FaceDrawingData> GetPeopleInfo();
		FaceList& GetDetectedFaceInfo();
		FaceList& GetFaceInfo();
		void FindEmployee(FaceList&  people);
		void updateFaceData(time_t time, int &total, int &watching);
		void FreeShowPeople();
		void clear_data(list<FaceDrawingData> & lst);
		void ReArrangeFaceData();
		void RefreshData(FaceData& errorData, FaceData& correctData);
		void showURL();
		void showMessage();
		void OutputLogData();
		void setFov(int nFov);
		void updateOptions();
		CFaceRecogEngine* getEngineHandle() { return m_smartEngine; }
		int PtInFace(const CPoint & pt);	// added by Robin

	protected:
		virtual void processFrame(const KipImageInfo * pFrame);
		virtual void drawOverlay(CDC * pDC, const CRect & rc);
		virtual void updateImageSize();
		virtual void initialize();

	public:

		//CPersonDB			thePersonDB;
		CFaceRecogEngine*	m_smartEngine;
		int					m_nProcessorID;		//added by KCH
	protected:
		SoundPlayer			m_soundPlayer;
		CCriticalSection	m_secData;
		CCriticalSection	m_secOptions;
		vector<ShowPeopleInfo>	m_showedPeople;



		int					m_goTotalNum;			//지나간 사람수 (총인원)
		int					m_watchingNum;			//시청자수	(1초이상 본사람수)

		int					m_nLimitAdult;
		int					m_nFov;
		CString				m_strManURL;
		CString				m_strWomanURL;
		CString				m_strChildrenURL;
		CString				m_strIntro;
		CString				m_strMsgRegistered;
		CString				m_strMsgUnregistered;
		CString				m_strAlarmRegistered;
		CString				m_strAlarmUnknown;

		int					m_nSubX;
		int					m_nSec;
		int					m_nStep;
		int					m_nStartSoundTime;
		BOOL				m_bPlaySound;
		int					m_nPivotAge;
		int					m_nPivotGender;

	};
}
