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
	DDX_Control(pDX, IDC_STATIC_NAME, m_lblName);
	DDX_Control(pDX, IDC_STATIC_AGEGENDER, m_lblAgeGender);
	DDX_Control(pDX, IDC_STATIC_ACCESSED, m_lblAccessed);
	DDX_Control(pDX, IDC_STATIC_ACCESSEDWHEN, m_lblAccessedWhen);
	DDX_Control(pDX, IDC_STATIC_STATUSLABEL, m_lblStatus1);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_lblStatus);
}


BEGIN_MESSAGE_MAP(CCellOfMonitorHistory, CPropertyPage)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCellOfMonitorHistory message handlers


BOOL CCellOfMonitorHistory::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpLightGray;
	bmpLightGray.LoadBitmap(IDB_LIGHTGRAY);
	pOldBitmap = dc.SelectObject(&bmpLightGray);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	return TRUE;
}
