#pragma once

#include "afxmt.h"
#include <vector>
#include<map>

#include "myDef.h"
#include "ximage.h"
#include "KipFaceDetector.h"
#include "licenseDef.h"

typedef void * KipEngineHandle;

using namespace std;
//using namespace KIP;

//#define NON_EMPLOYEE 0xffffffff					////종업원이 아닌 사람
#define NON_EMPLOYEE -1

class CMugshot
{
public:
	int	m_nIDX;
	struct PHOTO
	{
		unsigned int	m_nBpp;
		unsigned int	m_nEffWidth;
		unsigned int	m_nHeight;
		BYTE*			m_pbyBuf;
	} m_photo;

	DWORD* m_pdwFeature;

public:
	CMugshot()
	{
		m_nIDX = -1;
		m_photo.m_nBpp = 8;
		m_photo.m_nEffWidth = 0;
		m_photo.m_nHeight = 0;
		m_photo.m_pbyBuf = NULL;
		m_pdwFeature = NULL;
	}
	virtual ~CMugshot()
	{
		Clear();
	}

	CMugshot(const CMugshot& other)
	{
		m_nIDX = -1;
		m_photo.m_nBpp = 8;
		m_photo.m_nEffWidth = 0;
		m_photo.m_nHeight = 0;
		m_photo.m_pbyBuf = NULL;
		m_pdwFeature = NULL;
		*this = other;
	}

	CMugshot&	operator= (const CMugshot& right);
protected:
	void Clear();
};

//Pernson Data
class CPerson
{
	//Property
public:
	UINT				m_nID;
	CString				m_strName;
	//TCHAR				m_szURL[MAX_PATH];

	vector<CMugshot>	m_vecMugshot;
	//Method
public:
	CPerson();
	CPerson(const CPerson& other);
	virtual ~CPerson();

	CPerson&	operator= (const CPerson& right);
	//protected:
	void		Clear();
	void		Add(CMugshot& mugshot);
	int			Delete(int nMugIdx);

};

typedef pair<UINT, UINT> PAIR_UINT;

class CPersonDB
{
	//Property
private:

	CCriticalSection	m_crtSect;
	KipEngineHandle		m_hDetector;

	float				m_fltDiffThres;
	float				m_fThreshold_min;
	float				m_fThreshold_max;


	//Method
public:

	vector<CPerson>		m_vPerson;

	CPersonDB();
	CPersonDB(CString& strDBDirPath);
	virtual ~CPersonDB();

	void		getThresholdValue(int nLevel);
	UINT		GetEmployeeIndex(DWORD* pdwFeature, float& fSimilar);
	UINT		Size() { return m_vPerson.size(); }
	UINT		Add(CPerson& person);

	int			DeleteMugshot(int nPersonId, int nMugIdx);	//delete mugshot
	int			DeletePerson(int nPersonId);				//delete person

	int			IsExist(int nPersonId);
	CxImage*	CreatePhoto(UINT id);

	CPerson& operator[](UINT index)
	{
		return m_vPerson[index];
	}

	void		Clear();
};

CPersonDB & personDB();