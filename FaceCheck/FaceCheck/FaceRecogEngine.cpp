#include "StdAfx.h"
#include "FaceRecogEngine.h"
#include "TrackingFace.h"
#include "licenseDef.h"
//#include "PersonLogView.h"
#define			LOG_PHOTO_WIDTH			100
#define			LOG_PHOTO_HEIGHT		100

CxImage KipImage2CxImage(const KipImageInfo &imageInfo)
{
	CxImage xImage = NULL;

	switch (imageInfo.format)
	{
	case KipImageCodeBGR24u:
	{
		if (imageInfo.pixel_addr != NULL)
		{
			int stepBytes = (imageInfo.width * 24 + 31) / 32 * 4;
			xImage.CreateFromArray(imageInfo.pixel_addr, imageInfo.width, imageInfo.height, 24, stepBytes, false);
		}
		break;
	}
	default:
	{
		return NULL;
	}
	}

	return xImage;
}
CFaceRecogEngine::CFaceRecogEngine(int nFov)
{
	m_hFaceDetector = KipFD_Create(FACE_DETECT_ID, FACE_DETECT_KEY);
	m_hGenderEstimator = KipGE_Create(GENDER_ESTIMATION_ID, GENDER_ESTIMATION_KEY);
	m_hAgeEstimator = KipAE_Create(AGE_ESTIMATION_ID, AGE_ESTIMATION_KEY);
	m_hPositionEstimator = KipHP_Create(HEAD_POSTION_ID, HEAD_POSTION_KEY);

	m_hCameraMatrix = KipHP_CreateCameraMatrix(320, 240, nFov);

	m_nRegisterTime = 0;
	m_nRecogLimitTime = 0;

	m_nFov = nFov;
	m_nCurFov = nFov;

	getThresholdValue(AfxGetApp()->GetProfileInt(_T("FaceOption"), _T("ThresholdLevel"), 3));
}

CFaceRecogEngine::~CFaceRecogEngine(void)
{
	clear_face_list(m_lstDetectedData);
	clear_face_list(m_lstData);
	m_peopleId = 0;

	KipFD_Destroy(m_hFaceDetector);
	KipGE_Destroy(m_hGenderEstimator);
	KipAE_Destroy(m_hAgeEstimator);
	KipHP_Destroy(m_hPositionEstimator);
	KipHP_DestroyCameraMatrix(m_hCameraMatrix);
}

void CFaceRecogEngine::getThresholdValue(int nLevel)
{
	switch (nLevel)
	{
	case 1:
		m_fThreshold_min = 0.75f;
		m_fThreshold_max = 0.83f;
		break;
	case 2:
		m_fThreshold_min = 0.83f;
		m_fThreshold_max = 0.87f;
		break;
	case 3:
		m_fThreshold_min = 0.86f;
		m_fThreshold_max = 0.92f;
		break;
	case 4:
		m_fThreshold_min = 0.89f;
		m_fThreshold_max = 0.95f;
		break;
	case 5:
		m_fThreshold_min = 0.92f;
		m_fThreshold_max = 0.98f;
		break;
	}
}

void CFaceRecogEngine::FreeFaceData(FaceData & info)
{
	if (!info.vRecog.empty())
	{
		for (int j = 0; j < (int)info.vRecog.size(); j++)
		{
			if (info.vRecog[j] != NULL)
			{
				::delete[] info.vRecog[j];
				info.vRecog[j] = NULL;
			}
		}
		info.vRecog.clear();
	}

	if (info.pTrackingFace)
	{
		delete info.pTrackingFace;
		info.pTrackingFace = NULL;
	}

	if (_tcslen(info.szDbName) > 0)
		memset(info.szDbName, 0, _tcslen(info.szDbName));

	if (_tcslen(info.szName) > 0)
		memset(info.szName, 0, _tcslen(info.szName));

	if (_tcslen(info.szURL) > 0)
		memset(info.szURL, 0, _tcslen(info.szURL));

	if (info.imgCamera != NULL)
	{
		::delete info.imgCamera;
		info.imgCamera = NULL;
	}

	if (info.imgRegistered != NULL)
	{
		::delete info.imgRegistered;
		info.imgRegistered = NULL;
	}
}

void CFaceRecogEngine::clear_face_list(FaceList & lst)
{
	for (FaceList::iterator itr = lst.begin(); itr != lst.end(); itr++)
	{
		FreeFaceData(*itr);
	}
	lst.clear();
}

void CFaceRecogEngine::clear()
{
	clear_face_list(m_lstDetectedData);
	clear_face_list(m_lstData);
}

BOOL IsFrontal(const FaceData & info)
{
	return info.gender <= 100 && info.gender >= 0;
}

void CFaceRecogEngine::SetParam(int nRegister, int nRecog)
{
	m_nRegisterTime = nRegister;
	m_nRecogLimitTime = nRecog;
}

void CFaceRecogEngine::updateCameraMatrix(int nWidth, int nHeight, int nFov)
{
	m_hCameraMatrix = KipHP_CreateCameraMatrix(nWidth, nHeight, nFov);
}

BOOL CFaceRecogEngine::get_face_rect(FaceData &data, int nW, int nH)
{
	BOOL bFaceInImage = TRUE;

	int l1 = INT_MAX, r1 = 0, t1 = INT_MAX, b1 = 0;
	for (int i = 0; i < LANDMARK_COUNT; i++)
	{
		int x = (int)data.faceCorner.rect[i].x;
		int y = (int)data.faceCorner.rect[i].y;

		if (x < 0 || x > nW)
			bFaceInImage = FALSE;
		if (y < 0 || y > nH)
			bFaceInImage = FALSE;

		l1 = MIN(x, l1);
		r1 = MAX(x, r1);
		t1 = MIN(y, t1);
		b1 = MAX(y, b1);

	}

	data.bound.left = MIN(MAX(l1, 0), nW);
	data.bound.right = MIN(MAX(r1, 0), nW);
	data.bound.top = MIN(MAX(t1, 0), nH);
	data.bound.bottom = MIN(MAX(b1, 0), nH);

	return bFaceInImage;
}

void	CFaceRecogEngine::MoveFaceData(FaceData &src, FaceData &dst)
{
	dst = src;
	src.vRecog.clear();
	src.pTrackingFace = NULL;
	src.imgCamera = NULL;
	src.imgRegistered = NULL;
}

void CFaceRecogEngine::SetGenderAge(FaceData &dstInfo, FaceData &srcInfo)
{
	if (dstInfo.bIsOneSecond == FALSE && IsFrontal(srcInfo)/* && fabs(srcInfo.fViewAngle) <= 15.0f*/)
	{
		if (dstInfo.gender == -1 || dstInfo.FrontCount == 0)
		{
			dstInfo.gender = srcInfo.gender;
			dstInfo.age = srcInfo.age;
			dstInfo.FrontCount++;
		}
		else if (IsFrontal(dstInfo))
		{
			dstInfo.gender = (dstInfo.gender * dstInfo.FrontCount + srcInfo.gender) / (dstInfo.FrontCount + 1);
			dstInfo.age = (dstInfo.age * dstInfo.FrontCount + srcInfo.age) / (dstInfo.FrontCount + 1);
			dstInfo.FrontCount++;
		}
	}
}

BOOL CFaceRecogEngine::DBFileExist(TCHAR* szFileName)
{
	FILE* fp = _tfopen(szFileName, _T("rb"));
	if (fp == 0)
		return false;

	fclose(fp);

	return TRUE;
}
void CFaceRecogEngine::UpdateFaceData(FaceData &people, FaceData& curPeople, time_t time, int nWidth, int nHeight, int & num)
{
	people.faceCorner = curPeople.faceCorner;

	BOOL bCurFrontal = IsFrontal(curPeople);
	if (people.bLastFrontal && bCurFrontal)
		people.duration += difftime(time, people.lasttime);
	people.bLastFrontal = bCurFrontal;
	people.lasttime = time;
	people.depth = curPeople.depth;
	people.fSimilar = curPeople.fSimilar;

	// ly-add 2015.01.07
	people.fViewAngle = curPeople.fViewAngle;

	BOOL bFaceInImage = get_face_rect(people, nWidth, nHeight);

	if (people.id != curPeople.id)
		people.id = curPeople.id;
	if (_tcslen(curPeople.szDbName) != 0 && _tcscmp(people.szDbName, curPeople.szDbName) != 0)
	{
		memset(people.szDbName, 0, _tcslen(people.szDbName));
		memcpy(people.szDbName, curPeople.szDbName, sizeof(curPeople.szDbName));
	}

	if (_tcslen(curPeople.szName) != 0 && _tcscmp(people.szName, curPeople.szName) != 0)
	{
		memset(people.szName, 0, _tcslen(people.szName));
		memcpy(people.szName, curPeople.szName, sizeof(curPeople.szName));
	}

	if (_tcslen(curPeople.szURL) != 0 && _tcscmp(people.szURL, curPeople.szURL) != 0)
	{
		memset(people.szURL, 0, _tcslen(people.szURL));
		memcpy(people.szURL, curPeople.szURL, sizeof(curPeople.szURL));
	}

	/*by Robin if (DBFileExist(people.szDbName))
	{
	if (people.bIsEmployee < curPeople.bIsEmployee)
	people.bIsEmployee = curPeople.bIsEmployee;
	}
	else
	people.bIsEmployee = FALSE;*/
	//--------------------------------------------------------

	if (people.bIsOneSecond == FALSE && bFaceInImage == TRUE && people.duration > m_nRegisterTime &&
		IsFrontal(people))
		//정면얼굴에서 성별,나이가 설정되고  1초가 지나면 리스트에 등록
	{
		people.bIsOneSecond = TRUE;
		num++;
	}

	// add by apollo 2013.8.9
	if (curPeople.imgCamera != NULL)
	{
		if (people.imgCamera != NULL)
			::delete people.imgCamera;
		people.imgCamera = curPeople.imgCamera;
		curPeople.imgCamera = NULL;
	}

	if (people.bIsEmployee && curPeople.imgRegistered != NULL)
	{
		if (people.imgRegistered != NULL)
			::delete people.imgRegistered;
		people.imgRegistered = curPeople.imgRegistered;
		curPeople.imgRegistered = NULL;
	}
}

void CFaceRecogEngine::face_detect(const KipImageInfo *pImageInfo, time_t time)
{
	CSingleLock _lock(&m_section, TRUE);
	clear_face_list(m_lstDetectedData);

	//얼굴검출
	if (m_hFaceDetector == NULL)
		return;

	m_imageInfo = *pImageInfo;

	int nFace = KipFD_Detect(m_hFaceDetector, pImageInfo);
	if (nFace <= 0)
		return;

	int nW = pImageInfo->width;
	int nH = pImageInfo->height;

	if (m_nFov != m_nCurFov)
	{
		KipHP_DestroyCameraMatrix(m_hCameraMatrix);
		m_hCameraMatrix = KipHP_CreateCameraMatrix(nW, nH, m_nFov);
		m_nCurFov = m_nFov;
	}

	int nFrontalFaceCount = 0;

	for (int i = 0; i < nFace; i++)
	{
		FaceData tempInfo = { 0 };

		//얼굴표식점 얻기
		KipFaceLandmark *pFaceLandmark = NULL;
		int nLandmark = KipFD_GetLandmarks(m_hFaceDetector, i, &pFaceLandmark);

		for (int j = 0; j < 4; j++)
			tempInfo.faceCorner.rect[j] = pFaceLandmark[j].pos;

		//얼굴특징량얻기
		KipFaceFeature pFaceFeature;
		int nSuccess = KipFD_GetFeature(m_hFaceDetector, pImageInfo, i, &pFaceFeature);

		//3D-좌표 얻기
		KipHeadPosition	hp = { 0 };
		KipHP_Estimate(m_hPositionEstimator, m_hCameraMatrix, pFaceLandmark, nLandmark, &hp);
		tempInfo.depth = hp.position.z;

		//사람인덱스 초기화
		tempInfo.id = -1;

		//picasa특징량 보관
		PBYTE pRecog = ::new BYTE[DATA_DIM];
		memcpy(pRecog, pFaceFeature.recogInfo, DATA_DIM);
		tempInfo.vRecog.push_back(pRecog);

		//얼굴령역크기를 얻고 얼굴이 밖에 나가지 않았는가를 판정.
		BOOL bFaceInImage = get_face_rect(tempInfo, nW, nH);

		//얼굴보기각도		
		tempInfo.fViewAngle = pFaceFeature.anglePan;

		//신뢰도값
		tempInfo.confidence = pFaceFeature.confidence;

		//최초본시간
		tempInfo.initialTime = time;

		//마지막으로 본시간
		tempInfo.lasttime = time;

		//---------------- 2012/10/18 chs add---------------------
		//등록된 가족인가?
		tempInfo.bIsEmployee = FALSE;

		//가족DB파일이름
		memset(tempInfo.szDbName, 0, MAX_PATH);

		//가족이름
		memset(tempInfo.szName, 0, MAX_PATH);

		//URL
		memset(tempInfo.szURL, 0, MAX_URL);

		//--------------------------------------------------------

		//성별식별, 나이추정
		if (nSuccess == 0 && fabs(tempInfo.fViewAngle) <= 20.0f && bFaceInImage == TRUE/*  && pFaceFeature.confidence >= 0.6f*/)
		{
			tempInfo.gender = KipGE_Estimate(m_hGenderEstimator, &pFaceFeature);
			tempInfo.age = KipAE_Estimate(m_hAgeEstimator, &pFaceFeature, tempInfo.gender);
			tempInfo.FrontCount = 1;
			tempInfo.bLastFrontal = TRUE;
			nFrontalFaceCount++;
		}
		else
		{
			tempInfo.gender = -1;
			tempInfo.age = -1;
			tempInfo.FrontCount = 0;
			tempInfo.bLastFrontal = FALSE;
		}

		tempInfo.pTrackingFace = new CTrackingFace();
		tempInfo.pTrackingFace->Init(&tempInfo.faceCorner, tempInfo.confidence);
		KipFD_FreeLandmarks(pFaceLandmark);
		KipFD_FreeFeature(&pFaceFeature);

		m_lstDetectedData.push_back(tempInfo);
	}

	if (nFrontalFaceCount == 0)
		return;

	CxImage imgFrame = KipImage2CxImage(*pImageInfo);
	RGBQUAD rgb0 = { 0 };
	for (list<FaceData>::iterator itr = m_lstDetectedData.begin(); itr != m_lstDetectedData.end(); itr++)
	{
		if (itr->gender == -1)
			continue;

		CxImage *imgFace = ::new CxImage();
		imgFrame.Crop(itr->bound, imgFace);
		imgFace->Thumbnail(LOG_PHOTO_WIDTH, LOG_PHOTO_HEIGHT, rgb0);
		itr->imgCamera = imgFace;
	}
}

void CFaceRecogEngine::face_track(time_t time, int &goNum, int &watchingNum)
{
	int curpeople_count = (int)m_lstDetectedData.size();
	int prevpeople_count = (int)m_lstData.size();
	if (curpeople_count <= 0 && prevpeople_count <= 0)		//전프레임에도 현재프레임에서도 사람이 없을때는 탈퇴.
		return;

	if (curpeople_count> 0 && prevpeople_count <= 0 && goNum <= 0)	//첫프레임에는 사람이 없는데 현재프레임에서 사람이 생겼을때 등록
	{
		goNum = curpeople_count;
		for (FaceList::iterator itr = m_lstDetectedData.begin(); itr != m_lstDetectedData.end(); itr++)
		{
			FaceData faceData;
			MoveFaceData(*itr, faceData);
			faceData.id = m_peopleId++;
			faceData.bIsVisible = TRUE;

			m_lstData.push_back(faceData);
		}

		return;
	}

	for (FaceList::iterator itr = m_lstData.begin(); itr != m_lstData.end(); itr++)
	{
		itr->bIsVisible = FALSE;
	}

	//이전프레임과 현재프레임에 인식을 적용하여 같은 얼굴들은 서로 일치시키고 
	//같지않은 경우 10초이하이면 버리고 새 얼굴이면 m_lstData에 추가한다.

	boolean bIsUpdated = FALSE;
	int nCountofTemp = 0;
	float fSimilar = 0.f;

	for (FaceList::iterator itrDetected = m_lstDetectedData.begin(); itrDetected != m_lstDetectedData.end(); itrDetected++)
	{
		FaceData & cur_people = *itrDetected;

		//pFaceData에 있는 특징량과 같으면서 3초이하에 발견된 사람
		if (FindPeople(cur_people, time, watchingNum) == FALSE) //아니면 새로등록
		{
			FaceData FaceData;
			MoveFaceData(cur_people, FaceData);
			FaceData.id = goNum;
			FaceData.bIsVisible = TRUE;

			m_lstData.push_back(FaceData);
			goNum++;

			nCountofTemp++;
		}
	}

	//객체가 완전히 사라졌다면 목록에서 제거
	FaceList::iterator itrPrev = m_lstData.end();
	BOOL bIsPrevPeople = FALSE;
	for (FaceList::iterator itr = m_lstData.begin(); itr != m_lstData.end(); itr++)
	{
		FaceData & pivot_info = *itr;
		if (pivot_info.bIsVisible)
			continue;

		if (difftime(time, pivot_info.lasttime) > m_nRecogLimitTime)
		{
			//객체 제거
			FreeFaceData(pivot_info);
			m_lstData.erase(itr);
			if (bIsPrevPeople)
				itr = itrPrev;
			else if (m_lstData.size() == 0)
				break;
			else
				itr = m_lstData.begin();
		}
		else
		{
			itrPrev = itr;
			pivot_info.bLastFrontal = FALSE;
			pivot_info.pTrackingFace->UpdateWithoutData();
			bIsPrevPeople = TRUE;
		}
	}
}

BOOL	CFaceRecogEngine::FindPeople(FaceData& cur_people, time_t time, int &watchingNum)
{
	float fSimilar;
	list<FaceData>::iterator itrBestTracking = FindBestSimlarPeopleWithTracking(cur_people, fSimilar);
	BOOL bTracking = FALSE;

	if (fSimilar > THRESHOLD_TRACKING)
	{
		FaceData & pivot_info = *itrBestTracking;
		if (difftime(time, pivot_info.lasttime) <= m_nRecogLimitTime)
		{
			bTracking = TRUE;
			SetGenderAge(pivot_info, cur_people);

			UpdateFaceData(pivot_info, cur_people, time, m_imageInfo.width, m_imageInfo.height, watchingNum);
			if (pivot_info.bIsOneSecond)
			{
				pivot_info.pTrackingFace->UpdateWithData(&cur_people.faceCorner, cur_people.confidence);
				pivot_info.bIsVisible = TRUE;

				return TRUE;
			}
		}
	}

	FaceData * pivot_people = FindBestSimlarPeople(cur_people, fSimilar);
	if (pivot_people == NULL || fSimilar < m_fThreshold_min)
	{
		if (bTracking)
		{
			itrBestTracking->bIsVisible = TRUE;
			itrBestTracking->pTrackingFace->UpdateWithData(&cur_people.faceCorner, cur_people.confidence);

			return TRUE;
		}

		return FALSE;
	}

	if (bTracking == TRUE && pivot_people == &(*itrBestTracking))
	{
		pivot_people->bIsVisible = TRUE;
		pivot_people->pTrackingFace->UpdateWithData(&cur_people.faceCorner, cur_people.confidence);

		return TRUE;
	}

	FaceData & pivot_info = *pivot_people;

	if (difftime(time, pivot_info.lasttime) > m_nRecogLimitTime) // RECOG_LIMIT초전에 리스트에 있던 얼굴로 인식못되면 
	{
		return FALSE;
	}
	if (fSimilar < m_fThreshold_max && pivot_info.vRecog.size() < MAX_RECOGINFO_COUNT)
	{
		PBYTE pRecog = ::new BYTE[DATA_DIM];
		memcpy(pRecog, cur_people.vRecog[0], DATA_DIM);
		pivot_info.vRecog.push_back(pRecog);
	}

	SetGenderAge(pivot_info, cur_people);

	UpdateFaceData(pivot_info, cur_people, time, m_imageInfo.width, m_imageInfo.height, watchingNum);
	pivot_info.pTrackingFace->Init(&cur_people.faceCorner, cur_people.confidence);
	pivot_info.bIsVisible = TRUE;

	if (bTracking)
	{
		pivot_info.duration += itrBestTracking->duration;
		FreeFaceData(*itrBestTracking);
		m_lstData.erase(itrBestTracking);
	}

	return TRUE;
}

float CFaceRecogEngine::CalcSimilarity(FaceData & cur_info, FaceData & pivot_info)
{
	int nRecogCount = (int)pivot_info.vRecog.size();
	PBYTE *ppRecogData = new PBYTE[nRecogCount + 1];
	ppRecogData[0] = cur_info.vRecog[0];

	for (int k = 0; k < nRecogCount; k++)
		ppRecogData[k + 1] = pivot_info.vRecog[k];
	float fSimilar;

	KipFC_CompareCluster(m_hFaceDetector, (void**)ppRecogData, nRecogCount + 1, &fSimilar);
	delete[] ppRecogData;
	return fSimilar;
}

FaceData * CFaceRecogEngine::FindBestSimlarPeople(FaceData & cur_people, float & fSimilarity)
{
	FaceData * ret = NULL;
	float fMax = 0;
	for (FaceList::iterator itr = m_lstData.begin(); itr != m_lstData.end(); itr++)
	{
		FaceData & pivot_info = *itr;
		if (pivot_info.bIsVisible) // 이미 같은 얼굴이 존재하는 경우 판정 안함
			continue;
		float fSimilar = CalcSimilarity(cur_people, pivot_info);
		if (fMax < fSimilar)
		{
			ret = &pivot_info;
			fMax = fSimilar;
		}
	}

	fSimilarity = fMax;
	return ret;
}

list<FaceData>::iterator CFaceRecogEngine::FindBestSimlarPeopleWithTracking(FaceData & cur_people, float & fSimilarity)
{
	list<FaceData>::iterator ret;
	float fMax = 0;
	for (FaceList::iterator itr = m_lstData.begin(); itr != m_lstData.end(); itr++)
	{
		FaceData & pivot_info = *itr;
		if (pivot_info.bIsVisible) // 이미 같은 얼굴이 존재하는 경우 판정 안함
			continue;
		float fOverlapping = pivot_info.pTrackingFace->Calcuate_Overlapping(&cur_people.faceCorner);

		if (fOverlapping < 0.1)
			continue;
		float fSimilar = CalcSimilarity(cur_people, pivot_info);
		if (fMax < fSimilar)
		{
			ret = itr;
			fMax = fSimilar;
		}
	}

	fSimilarity = fMax;
	return ret;
}

void CFaceRecogEngine::SetFov(int nFov)
{
	m_nFov = nFov;
}
