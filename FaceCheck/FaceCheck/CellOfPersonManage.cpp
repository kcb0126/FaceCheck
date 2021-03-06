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
	, m_nNo(0)
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
	DDX_Text(pDX, IDC_STATIC_NO, m_nNo);
	DDX_Control(pDX, IDC_STATIC_NO, m_lblNo);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CCellOfPersonManage, CPropertyPage)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CCellOfPersonManage::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CCellOfPersonManage::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CCellOfPersonManage message handlers


BOOL CCellOfPersonManage::OnEraseBkgnd(CDC* pDC)
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


void CCellOfPersonManage::OnBnClickedButtonEdit()
{
	CPersonInfo dlgPersonInfo;
	dlgPersonInfo.SetPersonNo(this->m_nNo);
	dlgPersonInfo.DoModal();
}


void CCellOfPersonManage::OnBnClickedButtonDelete()
{
	int nResult = MessageBox(_T("Are you sure you want to delete this person?"), _T("Delete a person"), MB_YESNO | MB_ICONWARNING);
	
	if (nResult == IDNO)
		return;

	CString strQuery;

	personDB().DeletePerson(m_nID);

	//		g_pDBManager->deletePerson(nIndex);                                          /////
	//		g_pDBManager->updateUserId(nIndex, NON_EMPLOYEE);                            //////

	strQuery.Format(_T("CALL DELETE_PERSON(%d)"), m_nID);

	g_pDBManager->runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	g_pPersonManageList->RefreshList();
}
