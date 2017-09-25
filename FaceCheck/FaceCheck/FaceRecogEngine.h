#pragma once

#include "types.h"
#include <vector>
#include <list>

#include "ximage.h"

using namespace std;
using namespace KIP;

typedef list<FaceData>	FaceList;

namespace KIP
{
	class CFaceRecogEngine
	{
	public:
		CFaceRecogEngine(int	nFov);
		~CFaceRecogEngine(void);

		void							getThresholdValue(int nLevel);

		BOOL							get_face_rect(FaceData &FaceData, int nW, int nH);

		void							face_detect(const KipImageInfo *pImageInfo, time_t time);
		void							face_track(time_t time, int &goNum, int &watchingNum);

		void							FreeFaceData(FaceData & info);
		void							clear_face_list(FaceList & list);
		void							clear();

		void							UpdateFaceData(FaceData &people, FaceData &cur_people, time_t time, int nWidth, int nHeight, int & num);
		void							MoveFaceData(FaceData &src, FaceData &dst);
		void							SetGenderAge(FaceData &dstInfo, FaceData &srcInfo);
		void							SetParam(int nRegister, int nRecog);
		BOOL							DBFileExist(TCHAR* szFileName);
		void							updateCameraMatrix(int nWidth, int nHeight, int nFov);
		void							SetFov(int nFov);
	protected:

		FaceData *						FindBestSimlarPeople(FaceData & cur_people, float & fSimilarity);
		FaceList::iterator				FindBestSimlarPeopleWithTracking(FaceData & cur_people, float & fSimilarity);
		float 							CalcSimilarity(FaceData & cur_info, FaceData & pivot_info);
		BOOL							FindPeople(FaceData& cur_people, time_t time, int &watchingNum);

	public:
		KipEngineHandle					m_hFaceDetector;
		KipEngineHandle					m_hGenderEstimator;
		KipEngineHandle					m_hAgeEstimator;
		KipEngineHandle					m_hPositionEstimator;

		KipCameraMatrixHandle			m_hCameraMatrix;

		list<FaceData>					m_lstData;
		list<FaceData>					m_lstDetectedData;

		KipImageInfo					m_imageInfo;

		int								m_peopleId;
		int								m_nRegisterTime;
		int								m_nRecogLimitTime;
		int								m_nFov;
		int								m_nCurFov;

		float							m_fThreshold_min;
		float							m_fThreshold_max;

		CCriticalSection				m_section;
	};
}
