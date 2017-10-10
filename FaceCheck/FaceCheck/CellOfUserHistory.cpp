// CellOfUserHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfUserHistory.h"
#include "afxdialogex.h"


// CCellOfUserHistory dialog

IMPLEMENT_DYNAMIC(CCellOfUserHistory, CPropertyPage)

CCellOfUserHistory::CCellOfUserHistory()
	: CPropertyPage(CCellOfUserHistory::IDD)
	, m_strUsername(_T(""))
	, m_strAction(_T(""))
	, m_strTime(_T(""))
	, m_strContent(_T(""))
{

}

CCellOfUserHistory::~CCellOfUserHistory()
{
}

void CCellOfUserHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_STATIC_ACTION, m_strAction);
	DDX_Text(pDX, IDC_STATIC_TIME, m_strTime);
	DDX_Text(pDX, IDC_STATIC_CONTENT, m_strContent);
	DDX_Control(pDX, IDC_STATIC_USERNAME, m_lblUsername);
	DDX_Control(pDX, IDC_STATIC_ACTION, m_lblAction);
	DDX_Control(pDX, IDC_STATIC_TIME, m_lblTime);
	DDX_Control(pDX, IDC_STATIC_CONTENT, m_lblContent);
	DDX_Control(pDX, IDC_STATIC_NO, m_lblNo);
}


BEGIN_MESSAGE_MAP(CCellOfUserHistory, CPropertyPage)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCellOfUserHistory message handlers


BOOL CCellOfUserHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_lblNo.SetTextColor(RGB(255, 255, 255));
	m_lblUsername.SetTextColor(RGB(255, 255, 255));
	m_lblAction.SetTextColor(RGB(255, 255, 255));
	m_lblTime.SetTextColor(RGB(255, 255, 255));
	m_lblContent.SetTextColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CCellOfUserHistory::OnEraseBkgnd(CDC* pDC)
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
