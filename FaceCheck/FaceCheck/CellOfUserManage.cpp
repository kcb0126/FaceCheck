// CellOfUserManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfUserManage.h"
#include "afxdialogex.h"


// CCellOfUserManage dialog

IMPLEMENT_DYNAMIC(CCellOfUserManage, CPropertyPage)

CCellOfUserManage::CCellOfUserManage()
	: CPropertyPage(CCellOfUserManage::IDD)
	, m_strUsername(_T(""))
	, m_strPrivilege(_T(""))
	, m_strCreator(_T(""))
	, m_strPhoneNo(_T(""))
	, m_strBlocked(_T(""))
{

}

CCellOfUserManage::~CCellOfUserManage()
{
}

void CCellOfUserManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_STATIC_PRIVILEGE, m_strPrivilege);
	DDX_Text(pDX, IDC_STATIC_CREATOR, m_strCreator);
	DDX_Text(pDX, IDC_STATIC_PHONENO, m_strPhoneNo);
	DDX_Text(pDX, IDC_STATIC_BLOCKED, m_strBlocked);
	DDX_Control(pDX, IDC_STATIC_USERNAME, m_staticUsername);
	DDX_Control(pDX, IDC_STATIC_PRIVILEGE, m_staticPrivilege);
	DDX_Control(pDX, IDC_STATIC_CREATEDBY, m_staticCreatedBy);
	DDX_Control(pDX, IDC_STATIC_CREATOR, m_staticCreator);
	DDX_Control(pDX, IDC_STATIC_PHONENO1, m_staticPhoneNo1);
	DDX_Control(pDX, IDC_STATIC_PHONENO, m_staticPhoneNo);
	DDX_Control(pDX, IDC_STATIC_BLOCKED, m_staticBlocked);
}


BEGIN_MESSAGE_MAP(CCellOfUserManage, CPropertyPage)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCellOfUserManage message handlers


BOOL CCellOfUserManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_staticUsername.SetTextColor(RGB(255, 255, 255));
	m_staticPrivilege.SetTextColor(RGB(255, 255, 255));
	m_staticCreatedBy.SetTextColor(RGB(255, 255, 255));
	m_staticCreator.SetTextColor(RGB(255, 255, 255));
	m_staticPhoneNo1.SetTextColor(RGB(255, 255, 255));
	m_staticPhoneNo.SetTextColor(RGB(255, 255, 255));
	m_staticBlocked.SetTextColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CCellOfUserManage::OnEraseBkgnd(CDC* pDC)
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
