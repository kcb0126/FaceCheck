// CellOfMonitorHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfMonitorHistory.h"
#include "afxdialogex.h"


// CCellOfMonitorHistory dialog

IMPLEMENT_DYNAMIC(CCellOfMonitorHistory, CPropertyPage)

CCellOfMonitorHistory::CCellOfMonitorHistory()
	: CPropertyPage(CCellOfMonitorHistory::IDD)
	, m_strName(_T(""))
	, m_strAgeNGender(_T(""))
	, m_strAccessedwhen(_T(""))
	, m_strStatus(_T(""))
{

}

CCellOfMonitorHistory::~CCellOfMonitorHistory()
{
}

void CCellOfMonitorHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_staticPhoto);
	DDX_Control(pDX, IDC_STATIC_PHOTO_REGISTERED, m_staticPhotoRegistered);
	DDX_Text(pDX, IDC_STATIC_NAME, m_strName);
	DDX_Text(pDX, IDC_STATIC_AGEGENDER, m_strAgeNGender);
	DDX_Text(pDX, IDC_STATIC_ACCESSEDWHEN, m_strAccessedwhen);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
}


BEGIN_MESSAGE_MAP(CCellOfMonitorHistory, CPropertyPage)
END_MESSAGE_MAP()


// CCellOfMonitorHistory message handlers
