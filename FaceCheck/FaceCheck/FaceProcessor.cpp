#include "StdAfx.h"
#include "FaceProcessor.h"
#include "FaceCheck.h"
//--#include "DlgOfPersonInfo.h"
#include <afxhtml.h>
#include <Mmsystem.h>

using namespace KIP;

#define			SOUND_TIME				10000
#define			PLAY_ALARM				0
#define			LOG_PHOTO_WIDTH			100
#define			LOG_PHOTO_HEIGHT		100

BYTE * dup_recogInfo(const BYTE * recogInfo)
{
	if (recogInfo == NULL)
		return NULL;
	DWORD dwSize = *(const DWORD *)recogInfo;
	BYTE * ret = new BYTE[dwSize];
	memcpy(ret, recogInfo, dwSize);
	return ret;
}

FaceProcessor::FaceProcessor(void)
{
	//m_wndOutput = NULL;
	m_nFov = 55;
	m_smartEngine = new CFaceRecogEngine(m_nFov);

	int nRegister = AfxGetApp()->GetProfileInt(_T("Setting"), _T("RegisterTime"), 1);
	int nRecog = AfxGetApp()->GetProfileInt(_T("Setting"), _T("RecogLimitTime"), 5);
	m_smartEngine->SetParam(nRegister, nRecog);

	m_goTotalNum = 0;
	m_watchingNum = 0;
	m_strIntro = _T("");
	m_nSec = GetTickCount();
	m_nStep = 0;
	m_nStartSoundTime = -1;
	m_bPlaySound = FALSE;

	m_nPivotAge = -1;
	m_nPivotGender = -1;

	updateOptions();
}

FaceProcessor::~FaceProcessor(void)
{
	FreeShowPeople();

	if (m_smartEngine != NULL)
		delete (CFaceRecogEngine*)m_smartEngine;
	m_smartEngine = NULL;
}

void FaceProcessor::FreeShowPeople()
{
	for (int i = 0; i < (int)m_showedPeople.size(); i++)
	{
		if (m_showedPeople[i].bRecog != NULL)
			delete[] m_showedPeople[i].bRecog;
		m_showedPeople[i].bRecog = NULL;
		m_showedPeople[i].xImage.Destroy();
	}

	m_showedPeople.clear();
}

void FaceProcessor::clear_data(list<FaceDrawingData> & lst)
{
	for (list<FaceDrawingData>::iterator itr = lst.begin(); itr != lst.end(); itr++)
	{
		if (itr->pRecogInfo)
			delete[] itr->pRecogInfo;
	}

	lst.clear();
}

void * dup_recog_info(void * info)
{
	if (info == NULL)
		return NULL;
	void * ret = NULL;
	DWORD n = *(DWORD*)info;
	ret = new char[n];
	memcpy_s(ret, n, info, n);
	return ret;
}

FaceList& FaceProcessor::GetDetectedFaceInfo()
{
	return m_smartEngine->m_lstDetectedData;
}

FaceList& FaceProcessor::GetFaceInfo()
{
	return m_smartEngine->m_lstData;
}

void FaceProcessor::FindEmployee(FaceList&  people)
{/*--
	vector<int> vec_ind; // Face Count including Employee per frame.

	for (FaceList::iterator itr = people.begin(); itr != people.end(); itr++)
	{
		if (itr->vRecog.empty())
			continue;

		UINT nIndex = NON_EMPLOYEE;
		float fSimilar = 0.f;//see Robin
		for (int j = 0; j < (int)itr->vRecog.size(); j++)
		{
			float fSimilarTemp;
			int nTempIndex = personDB().GetEmployeeIndex((DWORD*)itr->vRecog[j], fSimilarTemp);
			if (nTempIndex != NON_EMPLOYEE)
			{
				if (fSimilarTemp > fSimilar)
				{
					nIndex = nTempIndex;
					fSimilar = fSimilarTemp;
				}
			}
		}

		if (nIndex != NON_EMPLOYEE)
		{
			CString strName = g_pDBManager->getPersonName(personDB()[nIndex].m_nID);

			_tcscpy(itr->szName, strName);
			itr->imgRegistered = personDB().CreatePhoto(nIndex); // add by apollo 2013.8.9
			RGBQUAD rgb0 = { 0 };
			itr->imgRegistered->Thumbnail(LOG_PHOTO_WIDTH, LOG_PHOTO_HEIGHT, rgb0);

			itr->id = personDB()[nIndex].m_nID;
			itr->bIsEmployee = TRUE;
			itr->fSimilar = fSimilar;
		}
	}--*/
}

void FaceProcessor::updateFaceData(time_t time, int &total, int &watching)
{
	CSingleLock _dataLock(&m_secData, TRUE);

	//가족DB에 있는 인물인가?
	FaceList& list = GetDetectedFaceInfo();
	int nIndex = list.size();
	if (nIndex >= 1)
		FindEmployee(list);

	//얼굴추적
	m_smartEngine->face_track(time, total, watching);
}

void FaceProcessor::RefreshData(FaceData& errorData, FaceData& correctData)
{/*--
	UINT nIndex = NON_EMPLOYEE;
	float fSimilar = 0.f;//see robin

	for (int j = 0; j < (int)errorData.vRecog.size(); j++)
	{
		float fSimilarTemp;
		int nTempID = personDB().GetEmployeeIndex((DWORD*)errorData.vRecog[j], fSimilarTemp);
		if (nTempID != NON_EMPLOYEE)
		{
			if (fSimilarTemp > fSimilar)
			{
				fSimilar = fSimilarTemp;
				nIndex = nTempID;
			}
		}
	}

	if (nIndex != NON_EMPLOYEE)
	{
		CString strName = g_pDBManager->getPersonName(personDB()[nIndex].m_nID);

		if (_tcscmp(strName, correctData.szName) == 0)
			errorData.bIsEmployee = FALSE;
		else
		{
			_tcscpy(errorData.szName, strName);
			errorData.id = personDB()[nIndex].m_nID;;
		}
	}
	else
		errorData.bIsEmployee = FALSE;--*/
}

void FaceProcessor::ReArrangeFaceData()
{
	CSingleLock lock(&m_secData, TRUE);
	FaceList& list = GetFaceInfo();

	for (FaceList::iterator itr = list.begin(); itr != list.end(); itr++)
	{
		FaceList::iterator itrTemp = itr;
		for (itrTemp++; itrTemp != list.end(); itrTemp++)
		{
			if (itr == itrTemp || itr->bIsEmployee == FALSE || itrTemp->bIsEmployee == FALSE)
				continue;

			if (_tcscmp(itr->szName, itrTemp->szName) == 0)
			{
				if (itr->fSimilar < itrTemp->fSimilar)
					RefreshData(*itr, *itrTemp);
				else
					RefreshData(*itrTemp, *itr);
			}
		}
	}
}

void FaceProcessor::processFrame(const KipImageInfo * pFrame)
{
	if (m_smartEngine == NULL)
		return;

	time_t tTime;
	time(&tTime);

	m_smartEngine->face_detect(pFrame, tTime);
	updateFaceData(tTime, m_goTotalNum, m_watchingNum);
	ReArrangeFaceData();
	//	showMessage();
	OutputLogData();
}

void FaceProcessor::showMessage()
{
	if (m_strIntro.IsEmpty() == FALSE)
		return;

	CSingleLock lock(&m_secData, TRUE);
	CSingleLock _lock(&m_secOptions, TRUE);

	FaceList& list = GetFaceInfo();

	if (list.size() <= 0)
		return;

	vector<int> vec_ind;
	int  nIndex = 0;

	for (FaceList::iterator itr = list.begin(); itr != list.end(); itr++)
	{
		if (itr->bIsVisible == FALSE || itr->bIsOneSecond == FALSE)
		{
			nIndex++;
			continue;
		}

		vec_ind.push_back(nIndex);
		nIndex++;
	}

	int nSize = 0;

	if (vec_ind.empty())
		return;

	FaceList::iterator itrResult = list.begin();
	for (int i = 0; i < (int)vec_ind.size(); i++)
	{
		FaceList::iterator itr = list.begin();
		for (int j = 0; j < vec_ind[i]; j++)
			itr++;

		int nTemp = (itr->bound.right - itr->bound.left) * (itr->bound.bottom - itr->bound.top);
		if (nTemp > nSize)
		{
			nSize = nTemp;
			itrResult = itr;
		}
	}

	if (itrResult->bIsOneSecond == FALSE)
		return;

	if (itrResult->bIsEmployee)
	{
		if (m_strMsgRegistered.Find(_T("%s")) >= 0)
			m_strIntro.Format(m_strMsgRegistered, itrResult->szName);
		else
			m_strIntro = m_strMsgRegistered;
	}
	else
		m_strIntro = m_strMsgUnregistered;

	//PlaySound ____2013/07/03  chs add
	/*
	int nTemp = GetTickCount();
	if (m_bPlaySound == FALSE)
	{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1) , NULL , SND_ASYNC | SND_RESOURCE);
	m_bPlaySound = TRUE;
	m_nStartSoundTime = nTemp;
	}
	else if (m_bPlaySound == TRUE && nTemp - m_nStartSoundTime >= SOUND_TIME)
	m_bPlaySound = FALSE;
	*/
}

void FaceProcessor::showURL()
{
	CSingleLock lock(&m_secData, TRUE);
	CSingleLock _lock(&m_secOptions, TRUE);

	FaceList& list = GetFaceInfo();

	if (list.size() <= 0)
		return;

	vector<int> vec_ind;
	int  nIndex = 0;

	for (FaceList::iterator itr = list.begin(); itr != list.end(); itr++)
	{
		if (itr->bIsVisible == FALSE || itr->bIsEmployee == FALSE || itr->bIsOneSecond == FALSE)
		{
			nIndex++;
			continue;
		}

		vec_ind.push_back(nIndex);
		nIndex++;
	}

	int nSize = 0;

	if (vec_ind.size() > 0)
	{
		//등록된 가족이 있는 경우 얼굴이 제일 큰 사람의 URL을 표시

		FaceList::iterator itrResult = list.begin();
		for (int i = 0; i < (int)vec_ind.size(); i++)
		{
			FaceList::iterator itr = list.begin();
			for (int j = 0; j < vec_ind[i]; j++)
				itr++;

			int nTemp = (itr->bound.right - itr->bound.left) * (itr->bound.bottom - itr->bound.top);
			if (nTemp > nSize)
			{
				nSize = nTemp;
				itrResult = itr;
			}
		}

		if (itrResult->bIsOneSecond == TRUE)
		{
			m_strIntro.Format(_T("Welcome %s!!!"), itrResult->szName);

			//PlaySound ____2013/07/03  chs add
			int nTemp = GetTickCount();
			if (m_bPlaySound == FALSE)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_WARNING), NULL, SND_ASYNC | SND_RESOURCE);
				m_bPlaySound = TRUE;
				m_nStartSoundTime = nTemp;
			}
			else if (m_bPlaySound == TRUE && nTemp - m_nStartSoundTime >= SOUND_TIME)
				m_bPlaySound = FALSE;
		}

		//		m_wndOutput->showURL((LPCTSTR)itrResult->szURL);
	}
	else
	{
		//화면에 등록된 사람이 없는 경우 얼굴이 제일 큰 사람이 성인남자인가 성인녀자인가 아이인가 판별하여 URL 표시

		int nRemarkCount = 0;
		FaceList::iterator itrResult = list.begin();
		for (FaceList::iterator itr = list.begin(); itr != list.end(); itr++)
		{
			if (itr->bIsOneSecond == FALSE || itr->bIsVisible == FALSE || itr->bIsEmployee == TRUE)
				continue;

			int nTemp = (itr->bound.right - itr->bound.left) * (itr->bound.bottom - itr->bound.top);
			if (nTemp > nSize)
			{
				nSize = nTemp;
				itrResult = itr;
			}

			nRemarkCount++;
		}
		/*
		if (nRemarkCount > 0)
		{
		if (itrResult->age >= m_nLimitAdult)
		{
		if (itrResult->gender >= 50)
		m_wndOutput->showURL(m_strManURL);
		else
		m_wndOutput->showURL(m_strWomanURL);
		}
		else
		m_wndOutput->showURL(m_strChildrenURL);
		}
		*/
	}
}

void FaceProcessor::drawOverlay(CDC * pDC, const CRect & rc)
{
	CSingleLock lock(&m_secData, TRUE);
	list<FaceDrawingData> listData = GetPeopleInfo();

	int w = m_image.GetWidth();
	int h = m_image.GetHeight();

	if (w * h == 0)
		return;

	CPen penM(PS_SOLID, 1, RGB(0, 0, 255));
	CPen penF(PS_SOLID, 1, RGB(255, 0, 0));
	CPen penR(PS_SOLID, 1, RGB(0, 255, 0));
	CPen penU(PS_SOLID, 1, RGB(255, 0, 255));
	CPen penT(PS_SOLID, 1, RGB(255, 255, 255));
	CPen penN(PS_SOLID, 1, RGB(255, 0, 0));

	// Initializes a CFont object with the specified characteristics. 
	CFont font;
	VERIFY(font.CreateFont(
		18,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Batang")));                 // lpszFacename

	CFont fontIntro;
	VERIFY(fontIntro.CreateFont(
		72,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("돋음")));                 // lpszFacename

	CFont * oldFont = pDC->SelectObject(&font);
	CPen * oldPen = pDC->SelectObject(&penM);
	pDC->SelectObject(GetStockObject(NULL_BRUSH));

	FreeShowPeople();

	for (list<FaceDrawingData>::const_iterator itr = listData.begin(); itr != listData.end(); itr++)
	{
		const FaceDrawingData & data = *itr;
		if (data.bIsVisible == FALSE)
			continue;

		CRect rcFace(rc.left + data.bound.left * rc.Width() / w, rc.top + data.bound.top * rc.Height() / h,
			rc.left + data.bound.right * rc.Width() / w, rc.top + data.bound.bottom * rc.Height() / h);

		pDC->SetBkMode(TRANSPARENT);

		if (data.bIsOneSecond == TRUE)
		{
			CString strGender;
			if (data.gender < 50 && data.gender != 0)
				strGender.LoadString(IDS_GENDER_FEMALE);
			else
				strGender.LoadString(IDS_GENDER_MALE);

			CString strHumanInfo;
			if (data.bIsEmployee == TRUE)
			{
				pDC->SelectObject(&penR);
				strHumanInfo.Format(_T("%s , %d, %s"), data.szName, data.age, strGender);
			}
			else
			{
				if (data.gender >= 50)
					pDC->SelectObject(&penM);
				else
					pDC->SelectObject(&penF);

				strHumanInfo.Format(_T("%d, %s"), data.age, strGender);
			}

			pDC->Rectangle(rcFace);

			CString strDist;
			strDist.Format(_T("%.2f M"), data.depth);

			pDC->SelectObject(oldFont);
			pDC->SetTextColor(RGB(0, 255, 0));

			CSize sizeText1 = pDC->GetTextExtent(strDist);
			CSize sizeText2 = pDC->GetTextExtent(strHumanInfo);

			pDC->TextOut(int(rcFace.left + (rcFace.right - rcFace.left - sizeText1.cx) / 2.f + 0.5),
				rcFace.top - 5 - sizeText1.cy, strDist);
			pDC->TextOut(int(rcFace.left + (rcFace.right - rcFace.left - sizeText2.cx) / 2.f + 0.5f),
				rcFace.bottom + 5, strHumanInfo);
		}
		else
		{
			pDC->SelectObject(&penU);
			pDC->Rectangle(rcFace);
		}

		if (data.pRecogInfo != NULL)
		{
			ShowPeopleInfo tempdata;
			tempdata.bound = rcFace;
			tempdata.bRecog = new BYTE[DATA_DIM];
			memcpy(tempdata.bRecog, data.pRecogInfo, DATA_DIM);

			m_showedPeople.push_back(tempdata);
		}
	}

	int nTickCount = GetTickCount();

	if (m_strIntro.IsEmpty() == FALSE)
	{
		int nDiffTime = int((nTickCount - m_nSec) / 10.f + 0.5f);
		int nRemain = nDiffTime - m_nStep;

		pDC->SelectObject(fontIntro);
		pDC->SetTextColor(RGB(255, 0, 0));

		CSize sizeText = pDC->GetTextExtent(m_strIntro);

		int nX = rc.right - m_nStep - 10;
		if (nX < -sizeText.cx)
		{
			m_nStep = 0;
			m_nSec = nTickCount;
			//nX = rc.right - m_nStep - 10;
			m_strIntro = _T("");
		}
		else
			m_nStep += nRemain;
		pDC->TextOut(nX, rc.bottom - 80, m_strIntro);
	}
	else
	{
		m_nStep = 0;
		m_nSec = nTickCount;
	}

	pDC->SelectObject(font);
	pDC->SelectObject(oldPen);

	clear_data(listData);
}

list<FaceDrawingData> FaceProcessor::GetPeopleInfo()
{
	// 엔진의 PeopleInfo 자료를 그대로 리용하지 않고 그리기에 필요한 자료들만으로 구성된 FaceDrawingData를 생성한다.
	// 왜냐하면 그리기가 진행되는 동안 엔진내부에서 PeopleInfo가 갱신될때의 충돌을 막기 위해서이다.
	list<FaceDrawingData> drawingData;
	{
		CSingleLock _dataLock(&m_secData, TRUE);
		list<FaceData> peopleInfo = GetFaceInfo();
		for (list<FaceData>::const_iterator itr = peopleInfo.begin(); itr != peopleInfo.end(); itr++)
		{
			const FaceData & info = *itr;
			FaceDrawingData data = { 0 };
			data.depth = info.depth;
			data.bound = info.bound;
			data.gender = info.gender;
			data.age = info.age;
			data.bIsOneSecond = info.bIsOneSecond;
			data.bIsVisible = info.bIsVisible;
			data.bIsEmployee = info.bIsEmployee;
			data.szName = info.szName;
			data.szURL = info.szURL;

			if (data.bIsOneSecond)
			{
				if (!info.vRecog.empty())
				{
					data.pRecogInfo = new BYTE[DATA_DIM];
					memcpy(data.pRecogInfo, info.vRecog[0], DATA_DIM);
				}
			}
			drawingData.push_back(data);
		}
	}
	return drawingData;
}

void FaceProcessor::updateImageSize()
{
	m_smartEngine->updateCameraMatrix(m_image.GetWidth(), m_image.GetHeight(), m_nFov);
}

void FaceProcessor::initialize()
{
	CSingleLock lock(&m_secData, TRUE);
	m_smartEngine->clear();
	m_strIntro = _T("");
	m_nStep = 0;
	m_nSec = 0;
	m_bPlaySound = FALSE;
	m_nStartSoundTime = -1;
	m_nPivotAge = -1;
	m_nPivotGender = -1;

#if PLAY_ALARM
	m_soundPlayer.StartPlayLoop();
#endif
}

void FaceProcessor::setOptions()
{
	// 	CFaceProcessorOptioinsDlg dlg;
	// 	if(dlg.DoModal() == IDOK)
	// 		updateOptions();
}

int FaceProcessor::PtInFace(const CPoint & pt)
{
	CSingleLock lock(&m_secData, TRUE);

	if (m_showedPeople.empty())
		return -1;

	int i;
	for (i = 0; i < (int)m_showedPeople.size(); i++)
	{
		if (m_showedPeople[i].bound.PtInRect(pt) == TRUE)
			break;
	}

	if (i >= (int)m_showedPeople.size())
		return -1;

	return i;
}

void FaceProcessor::onDblClick(const CPoint & pt, const CRect & rc)
{/*--
	CRect rcPhoto;
	int i = 0;

	i = PtInFace(pt);

	if (i == -1)
		return;

	rcPhoto = m_showedPeople[i].bound;

	CRect rcFrame = CalcFrameRect(rc);
	if (rcFrame.Width() * rcFrame.Height() == 0)
		return;

	rcPhoto.left = (rcPhoto.left - rcFrame.left) * m_image.GetWidth() / rcFrame.Width();
	rcPhoto.top = (rcPhoto.top - rcFrame.top) * m_image.GetHeight() / rcFrame.Height();
	rcPhoto.right = (rcPhoto.right - rcFrame.left) * m_image.GetWidth() / rcFrame.Width();
	rcPhoto.bottom = (rcPhoto.bottom - rcFrame.top) * m_image.GetHeight() / rcFrame.Height();

	CxImage imgPhoto;
	m_image.Crop(rcPhoto, &imgPhoto);

	CDlgOfPersonInfo dlgMan;
	dlgMan.m_nMode = MODE_CUSTOMER_ADD; //add from CameraView

	imgPhoto.Resample(REG_IMAGE_W, REG_IMAGE_H, 1, &(dlgMan.m_imgPhoto));

	dlgMan.m_person.m_vecMugshot.resize(1);
	dlgMan.m_person.m_vecMugshot[0].m_pdwFeature = (DWORD*)dup_recogInfo(m_showedPeople[i].bRecog);
	dlgMan.m_person.m_vecMugshot[0].m_photo.m_nBpp = dlgMan.m_imgPhoto.GetBpp();
	dlgMan.m_person.m_vecMugshot[0].m_photo.m_nEffWidth = dlgMan.m_imgPhoto.GetEffWidth();
	dlgMan.m_person.m_vecMugshot[0].m_photo.m_nHeight = dlgMan.m_imgPhoto.GetHeight();
	dlgMan.m_person.m_vecMugshot[0].m_photo.m_pbyBuf = new BYTE[dlgMan.m_imgPhoto.GetEffWidth() *dlgMan.m_imgPhoto.GetHeight()];
	memcpy(dlgMan.m_person.m_vecMugshot[0].m_photo.m_pbyBuf, dlgMan.m_imgPhoto.GetBits(), dlgMan.m_imgPhoto.GetEffWidth() * dlgMan.m_imgPhoto.GetHeight());
	dlgMan.m_person.m_nID = NON_EMPLOYEE;
	dlgMan.m_bPhotoShow = TRUE;

	dlgMan.DoModal();--*/
}

void FaceProcessor::setFov(int nFov)
{
	m_nFov = nFov;
	m_smartEngine->SetFov(nFov);
}

void FaceProcessor::updateOptions()
{/*--
	CSingleLock _lock(&m_secOptions, TRUE);
	m_nLimitAdult = AfxGetApp()->GetProfileInt(_T("Option"), _T("LimitAdult"), 18);
	m_strManURL = AfxGetApp()->GetProfileString(_T("Option"), _T("ManURL"), CFaceCheckApp::GetAppSubFilePath(_T("man.html")));
	m_strWomanURL = AfxGetApp()->GetProfileString(_T("Option"), _T("WomanURL"), CFaceCheckApp::GetAppSubFilePath(_T("woman.html")));
	m_strChildrenURL = AfxGetApp()->GetProfileString(_T("Option"), _T("ChildURL"), CFaceCheckApp::GetAppSubFilePath(_T("child.html")));
	m_nFov = AfxGetApp()->GetProfileInt(_T("FaceOption"), _T("FOV"), 55);
	setFov(m_nFov);

	m_strMsgRegistered.LoadString(IDS_MSG_REGISTERED);
	m_strMsgUnregistered.LoadString(IDS_MSG_UNREGISTERED);
	// 	m_strMsgRegistered = AfxGetApp()->GetProfileString(_T("Option"), _T("RegisteredMsg"), m_strMsgRegistered);
	// 	m_strMsgUnregistered = AfxGetApp()->GetProfileString(_T("Option"), _T("UnregisteredMsg"), m_strMsgUnregistered);

	m_strMsgRegistered.Replace(_T("[NAME]"), _T("%s"));

#if PLAY_ALARM
	TCHAR fileName[MAX_PATH];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	TCHAR * pos = _tcsrchr(fileName, _T('\\'));
	if (pos)
		pos[0] = NULL;
	_tcscat(fileName, _T("\\config.txt"));
	TCHAR strParam[MAX_PATH];

	if (GetPrivateProfileString(_T("Alarm"), _T("Registered"), _T(""), strParam, MAX_PATH, fileName) != 0)
	{
		if (_tcslen(strParam) > 0 && (_tcslen(strParam) < 3 || strParam[1] != _T(':')))
		{
			TCHAR szPath[MAX_PATH];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			TCHAR * pos = _tcsrchr(szPath, _T('\\'));
			if (pos)
				pos[1] = 0;
			_tcscat(szPath, strParam);
		}
		m_strAlarmRegistered = strParam;
	}

	if (GetPrivateProfileString(_T("Alarm"), _T("Unknown"), _T(""), strParam, MAX_PATH, fileName) != 0)
	{
		if (_tcslen(strParam) > 0 && (_tcslen(strParam) < 3 || strParam[1] != _T(':')))
		{
			TCHAR szPath[MAX_PATH];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			TCHAR * pos = _tcsrchr(szPath, _T('\\'));
			if (pos)
				pos[1] = 0;
			_tcscat(szPath, strParam);
		}
		m_strAlarmUnknown = strParam;
	}
#endif // PLAY_ALARM--*/
}

void FaceProcessor::OutputLogData()
{/*--
	CSingleLock lock(&m_secData, TRUE);
	FaceList& list = GetFaceInfo();

	if (list.size() <= 0)
		return;

	int log_type = 0;
	BOOL bOpenDoor = FALSE;
	LPCTSTR lpszName = NULL;
	// 	int max_area = 0;
	// 	int max_age = 0;
	// 	int max_gender = 0;
	// 	int max_fAngle = 0;

	int idxWhite = -1;

	FaceList::iterator itr = list.begin();

	for (UINT i = 0; i < list.size(); i++)
	{
		if (i != 0)
			itr++;

		if (itr->bIsVisible == TRUE && itr->bIsEmployee && itr->bIsOneSecond)
		{
			bOpenDoor = TRUE;
			lpszName = itr->szName;
		}
		if (itr->bIsVisible == FALSE || itr->bIsOneSecond == FALSE)
			continue;

		if (itr->bIsEmployee == FALSE && itr->nOutputData != 0)
			continue;

		if (itr->bIsEmployee == TRUE && itr->nOutputData == 2)
			continue;

		if (g_pMonitorHistoryForm->GetSafeHwnd())
			g_pMonitorHistoryForm->SendMessage(UM_ADD_HISTORY, (WPARAM)(&(*itr)), (LPARAM)(m_nProcessorID));

		itr->nOutputData = itr->bIsEmployee ? 2 : 1;
		if (itr->bIsEmployee)
			log_type = 1;
		else if (log_type == 0)
			log_type = 2;

		itr->imgCamera = NULL;
		itr->imgRegistered = NULL;
	}--*/
}
