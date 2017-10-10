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
	//  DDX_Control(pDX, IDC_STATIC_CREATEDBY, m_staticCreatedBy);
	DDX_Control(pDX, IDC_STATIC_CREATOR, m_staticCreator);
	//  DDX_Control(pDX, IDC_STATIC_PHONENO1, m_staticPhoneNo1);
	DDX_Control(pDX, IDC_STATIC_PHONENO, m_staticPhoneNo);
	DDX_Control(pDX, IDC_STATIC_BLOCKED, m_staticBlocked);
	DDX_Control(pDX, IDC_STATIC_NO, m_lblNo);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CCellOfUserManage, CPropertyPage)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CCellOfUserManage::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CCellOfUserManage::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CCellOfUserManage message handlers


BOOL CCellOfUserManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_staticUsername.SetTextColor(RGB(255, 255, 255));
	m_staticPrivilege.SetTextColor(RGB(255, 255, 255));
	m_staticCreator.SetTextColor(RGB(255, 255, 255));
	m_staticPhoneNo.SetTextColor(RGB(255, 255, 255));
	m_staticBlocked.SetTextColor(RGB(255, 255, 255));
	m_lblNo.SetTextColor(RGB(255, 255, 255));

	m_btnEdit.OnSet();
	m_btnEdit.LoadBitmaps(IDB_EDIT, IDB_EDITDOWN, IDB_EDIT, IDB_EDIT);
	m_btnEdit.SetHoverBitmapID(IDB_EDITHOVER);

	m_btnDelete.OnSet();
	m_btnDelete.LoadBitmaps(IDB_DELETE, IDB_DELETEDOWN, IDB_DELETE, IDB_DELETE);
	m_btnDelete.SetHoverBitmapID(IDB_DELETEHOVER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CCellOfUserManage::OnEraseBkgnd(CDC* pDC)
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


void CCellOfUserManage::OnBnClickedButtonEdit()
{
	CUserInfo dlgUserInfo;
	dlgUserInfo.m_strUsername = m_strUsername;
	dlgUserInfo.m_strOldname = m_strUsername;
	dlgUserInfo.m_strPhone = m_strPhoneNo;
	dlgUserInfo.m_nMode = MODE_USER_MODIFY;
	dlgUserInfo.DoModal();
}


void CCellOfUserManage::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
}
