// CellOfPersonHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfPersonHistory.h"
#include "afxdialogex.h"


// CCellOfPersonHistory dialog

IMPLEMENT_DYNAMIC(CCellOfPersonHistory, CPropertyPage)

CCellOfPersonHistory::CCellOfPersonHistory()
	: CPropertyPage(CCellOfPersonHistory::IDD)
	, m_strTime(_T(""))
	, m_strName(_T(""))
	, m_strGender(_T(""))
	, m_strAge(_T(""))
	, m_strPlace(_T(""))
	, m_strView(_T(""))
	, m_strComment(_T(""))
	, m_nNo(0)
{

}

CCellOfPersonHistory::~CCellOfPersonHistory()
{
}

void CCellOfPersonHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_staticPhoto);
	DDX_Text(pDX, IDC_STATIC_TIME, m_strTime);
	DDX_Text(pDX, IDC_STATIC_NAME, m_strName);
	DDX_Text(pDX, IDC_STATIC_GENDER, m_strGender);
	DDX_Text(pDX, IDC_STATIC_AGE, m_strAge);
	DDX_Text(pDX, IDC_STATIC_PLACE, m_strPlace);
	DDX_Text(pDX, IDC_STATIC_VIEW, m_strView);
	DDX_Text(pDX, IDC_STATIC_COMMENT, m_strComment);
	DDX_Control(pDX, IDC_STATIC_TIME, m_lblTime);
	DDX_Control(pDX, IDC_STATIC_NAME, m_lblName);
	DDX_Control(pDX, IDC_STATIC_GENDER, m_lblGender);
	DDX_Control(pDX, IDC_STATIC_AGE, m_lblAge);
	DDX_Control(pDX, IDC_STATIC_PLACE, m_lblPlace);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_lblView);
	DDX_Control(pDX, IDC_STATIC_COMMENT, m_lblComment);
	DDX_Text(pDX, IDC_STATIC_NO, m_nNo);
	DDX_Control(pDX, IDC_STATIC_NO, m_lblNo);
	DDX_Control(pDX, IDC_STATIC_AGE1, m_lblAge1);
	DDX_Control(pDX, IDC_STATIC_VIEW1, m_lblView1);
}


BEGIN_MESSAGE_MAP(CCellOfPersonHistory, CPropertyPage)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCellOfPersonHistory message handlers


BOOL CCellOfPersonHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_lblTime.SetTextColor(RGB(255, 255, 255));
	m_lblName.SetTextColor(RGB(255, 255, 255));
	m_lblGender.SetTextColor(RGB(255, 255, 255));
	m_lblAge.SetTextColor(RGB(255, 255, 255));
	m_lblPlace.SetTextColor(RGB(255, 255, 255));
	m_lblView.SetTextColor(RGB(255, 255, 255));
	m_lblComment.SetTextColor(RGB(255, 255, 255));
	m_lblNo.SetTextColor(RGB(255, 255, 255));
	m_lblAge1.SetTextColor(RGB(255, 255, 255));
	m_lblView1.SetTextColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CCellOfPersonHistory::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	if (!pDC)return FALSE;

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
