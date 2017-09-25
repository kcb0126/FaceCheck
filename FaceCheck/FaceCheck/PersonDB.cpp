#include "stdafx.h"

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <share.h>
#include <sys/stat.h>

#include "PersonDB.h"
//#include "myGlobal.h"
#include "types.h"
//////////////////////////////////////////////
// CMugshot
CMugshot& CMugshot::operator= (const CMugshot& right)
{
	if (this != &right)
	{
		Clear();

		m_nIDX = right.m_nIDX;

		if (right.m_photo.m_pbyBuf != NULL)
		{
			m_photo.m_nBpp = right.m_photo.m_nBpp;
			m_photo.m_nEffWidth = right.m_photo.m_nEffWidth;
			m_photo.m_nHeight = right.m_photo.m_nHeight;
			m_photo.m_pbyBuf = new BYTE[m_photo.m_nEffWidth * m_photo.m_nHeight];
			memcpy(m_photo.m_pbyBuf, right.m_photo.m_pbyBuf, m_photo.m_nEffWidth * m_photo.m_nHeight);
		}

		if (right.m_pdwFeature != NULL)
		{
			int nFeatureSize = right.m_pdwFeature[0] / 4;
			m_pdwFeature = new DWORD[nFeatureSize];
			memcpy(m_pdwFeature, right.m_pdwFeature, right.m_pdwFeature[0]);
		}
	}

	return *this;
}
void CMugshot::Clear()
{
	m_nIDX = -1;
	m_photo.m_nBpp = 8;
	m_photo.m_nEffWidth = 0;
	m_photo.m_nHeight = 0;

	if (m_photo.m_pbyBuf != NULL)
		delete[] m_photo.m_pbyBuf;
	m_photo.m_pbyBuf = NULL;

	if (m_pdwFeature != NULL)
		delete[] m_pdwFeature;
	m_pdwFeature = NULL;
}

//////////////////////////////////////////////
// CPerson
CPerson::CPerson()
{
	m_nID = NON_EMPLOYEE;
}

CPerson::CPerson(const CPerson& other)
{
	m_nID = NON_EMPLOYEE;
	*this = other;
}

CPerson::~CPerson()
{
	Clear();
}

CPerson&	CPerson::operator= (const CPerson& right)
{
	if (this != &right)
	{
		Clear();
		m_strName = right.m_strName;
		//_tcscpy(m_szName, right.m_szName);
		//_tcscpy(m_szURL, right.m_szURL);
		m_nID = right.m_nID;
		m_vecMugshot = right.m_vecMugshot;
	}

	return *this;
}
void CPerson::Add(CMugshot& mugshot)
{
	CMugshot newMugshot = mugshot;
	m_vecMugshot.push_back(mugshot);
	return;
}

BOOL CPerson::Delete(int nMugIdx)
{
	vector<CMugshot>::iterator itr;

	for (itr = m_vecMugshot.begin(); itr != m_vecMugshot.end(); itr++)
	{
		if (itr->m_nIDX == nMugIdx)
		{
			m_vecMugshot.erase(itr);
			return TRUE;
		}
	}
	return FALSE;
}

void CPerson::Clear()
{
	m_nID = NON_EMPLOYEE;
	m_vecMugshot.clear();
}

static CPersonDB * g_pPersonDB = NULL;
//////////////////////////////////////////////////////////////////////////
//    class CPersonDB
CPersonDB::CPersonDB(CString& strDBDirPath)
{
	char szLicenseID[0x100] = { 0 };
	char szLicenseKey[0x100] = { 0 };

	m_hDetector = KipFD_Create(FACE_DETECT_ID, FACE_DETECT_KEY);

	m_fltDiffThres = 0.13f;

	g_pPersonDB = this;
}
CPersonDB::CPersonDB()
{
	char szLicenseID[0x100] = { 0 };
	char szLicenseKey[0x100] = { 0 };

	//if(licenseChecker()->GetModuleLicenseKey(_T("FaceDetection"), szLicenseID, szLicenseKey))
	m_hDetector = KipFD_Create(FACE_DETECT_ID, FACE_DETECT_KEY);
	//else
	//	m_hDetector = NULL;

	m_fltDiffThres = 0.13f;
	g_pPersonDB = this;
}

CPersonDB::~CPersonDB()
{
	KipFD_Destroy(m_hDetector);
}

UINT CPersonDB::Add(CPerson& person)
{
	CSingleLock _lock(&m_crtSect, TRUE);

	m_vPerson.push_back(person);
	return person.m_nID;
}

int CPersonDB::DeleteMugshot(int nPersonId, int nMugIdx)
{
	CSingleLock _lock(&m_crtSect, TRUE);

	vector<CPerson>::iterator personItr;

	int idx = 0;
	for (personItr = m_vPerson.begin(); personItr != m_vPerson.end(); personItr++)
	{
		if (personItr->m_nID == nPersonId)
		{
			if (personItr->Delete(nMugIdx) == FALSE)
				return -1;

			return idx;
		}
		idx++;
	}

	return -1;
}

int CPersonDB::DeletePerson(int nPersonId)
{
	CSingleLock _lock(&m_crtSect, TRUE);

	vector<CPerson>::iterator personItr;

	int idx = 0;
	for (personItr = m_vPerson.begin(); personItr != m_vPerson.end(); personItr++)
	{
		if (personItr->m_nID == nPersonId)
		{
			m_vPerson.erase(personItr);
			return idx;
		}
		idx++;
	}

	return -1;
}

void CPersonDB::getThresholdValue(int nLevel)
{
	CSingleLock _lock(&m_crtSect, TRUE);
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

UINT	CPersonDB::GetEmployeeIndex(DWORD* pdwFeature, float& fSimilar)
{
	CSingleLock _lock(&m_crtSect, TRUE);

	UINT nRet = NON_EMPLOYEE;

	PVOID	templatePtrArr[50];

	templatePtrArr[0] = pdwFeature;

	float	fltMaxSim = 0.0f;
	float	fltSecondSim = 0.0f;
	float	fltThirdSim = 0.0f;
	UINT	nFirstCandidate = NON_EMPLOYEE;
	UINT	nSecondCandidate = NON_EMPLOYEE;
	UINT	nThirdCandidate = NON_EMPLOYEE;

	for (UINT j = 0; j<(m_vPerson.size()); j++)
	{
		int face_count = (int)m_vPerson[j].m_vecMugshot.size();
		for (int k = 0; k<face_count; k++)
		{
			templatePtrArr[k + 1] = m_vPerson[j].m_vecMugshot[k].m_pdwFeature;
		}

		float fltSim;
		KipFC_CompareCluster(m_hDetector, templatePtrArr, face_count + 1, &fltSim);
		{
			if (fltSim > fltMaxSim)
			{
				fltThirdSim = fltSecondSim;
				nThirdCandidate = nSecondCandidate;
				fltSecondSim = fltMaxSim;
				nSecondCandidate = nFirstCandidate;
				fltMaxSim = fltSim;
				nFirstCandidate = j;
			}
			else if (fltSim > fltSecondSim)
			{
				fltThirdSim = fltSecondSim;
				nThirdCandidate = nSecondCandidate;
				fltSecondSim = fltSim;
				nSecondCandidate = j;
			}
			else if (fltSim > fltThirdSim)
			{
				fltThirdSim = fltSim;
				nThirdCandidate = j;
			}
		}
	}

	if (fltMaxSim > m_fThreshold_max)
	{
		fSimilar = fltMaxSim;
		return nFirstCandidate;//m_vPerson[nFirstCandidate].m_nID;
	}
	else if (fltMaxSim > m_fThreshold_min)
	{
		if (fltMaxSim - (fltMaxSim + fltSecondSim + fltThirdSim) / 3.f > m_fltDiffThres)
		{
			fSimilar = fltMaxSim;
			return nFirstCandidate;//m_vPerson[nFirstCandidate].m_nID;
		}
	}

	return NON_EMPLOYEE;
}

void CPersonDB::Clear()
{
	m_vPerson.clear();
	//m_mapID_Index.clear();
}

int CPersonDB::IsExist(int nPersonId)
{
	CSingleLock _lock(&m_crtSect, TRUE);

	int nCount = 0;

	for (UINT j = 0; j < m_vPerson.size(); j++)
	{
		if (m_vPerson[j].m_nID == nPersonId)
			return nCount;

		nCount++;
	}

	return -1;
}

CxImage * CPersonDB::CreatePhoto(UINT index)
{
	CSingleLock _lock(&m_crtSect, TRUE);
	CMugshot * pMugshot = NULL;

	if (m_vPerson[index].m_vecMugshot.empty() == false)
		pMugshot = &m_vPerson[index].m_vecMugshot[0];

	if (pMugshot == NULL)
		return NULL;

	CxImage * img = new CxImage();
	img->CreateFromArray(pMugshot->m_photo.m_pbyBuf, CUSTOMER_PHOTO_WIDTH, CUSTOMER_PHOTO_HEIGHT, pMugshot->m_photo.m_nBpp, pMugshot->m_photo.m_nEffWidth, FALSE);
	return img;
}

CPersonDB & personDB()
{
	return *g_pPersonDB;
}
