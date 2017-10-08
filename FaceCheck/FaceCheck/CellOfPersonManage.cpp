// CellOfPersonManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfPersonManage.h"
#include "afxdialogex.h"
#include "ListOfPersonManage.h"
#include "myGlobal.h"

// CCellOfPersonManage dialog

IMPLEMENT_DYNAMIC(CCellOfPersonManage, CPropertyPage)

CCellOfPersonManage::CCellOfPersonManage()
	: CPropertyPage(CCellOfPersonManage::IDD)
{

}

CCellOfPersonManage::~CCellOfPersonManage()
{
}

void CCellOfPersonManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_lblName);
	DDX_Control(pDX, IDC_STATIC_NICKNAME1, m_lblNickname1);
	DDX_Control(pDX, IDC_STATIC_NICKNAME, m_lblNickname);
	DDX_Control(pDX, IDC_STATIC_GENDER, m_lblGender);
	DDX_Control(pDX, IDC_STATIC_BIRTHDAY1, m_lblBirthday1);
	DDX_Control(pDX, IDC_STATIC_BIRTHDAY, m_lblBirthday);
	DDX_Control(pDX, IDC_STATIC_GUESTTYPE1, m_lblGuesttype1);
	DDX_Control(pDX, IDC_STATIC_GUESTTYPE, m_lblGuesttype);
	DDX_Control(pDX, IDC_STATIC_SAFETYTYPE1, m_lblSafetytype1);
	DDX_Control(pDX, IDC_STATIC_SAFETYTYPE, m_lblSafetytype);
	DDX_Control(pDX, IDC_STATIC_BLOCKED, m_lblBlocked);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_staticPhoto);
}


BEGIN_MESSAGE_MAP(CCellOfPersonManage, CPropertyPage)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CCellOfPersonManage::OnBnClickedButtonEdit)
END_MESSAGE_MAP()


// CCellOfPersonManage message handlers


BOOL CCellOfPersonManage::OnEraseBkgnd(CDC* pDC)
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


BOOL CCellOfPersonManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_lblName.SetTextColor(RGB(255, 255, 255));
	m_lblNickname1.SetTextColor(RGB(255, 255, 255));
	m_lblNickname.SetTextColor(RGB(255, 255, 255));
	m_lblGender.SetTextColor(RGB(255, 255, 255));
	m_lblBirthday1.SetTextColor(RGB(255, 255, 255));
	m_lblBirthday.SetTextColor(RGB(255, 255, 255));
	m_lblGuesttype1.SetTextColor(RGB(255, 255, 255));
	m_lblGuesttype.SetTextColor(RGB(255, 255, 255));
	m_lblSafetytype1.SetTextColor(RGB(255, 255, 255));
	m_lblSafetytype.SetTextColor(RGB(255, 255, 255));
	m_lblBlocked.SetTextColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCellOfPersonManage::OnBnClickedButtonEdit()
{
	g_pPersonManageList->EnableWindow(FALSE);
	g_pPersonInfo->SetPersonID(this->m_nID);
	g_pPersonInfo->ShowWindow(SW_SHOW);
}
