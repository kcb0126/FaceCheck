// UserInfo.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "UserInfo.h"
#include "afxdialogex.h"
#include "myGlobal.h"

CUserInfo* g_pUserInfo;

// CUserInfo dialog

IMPLEMENT_DYNAMIC(CUserInfo, CDialogEx)

CUserInfo::CUserInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserInfo::IDD, pParent)
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
	, m_strConfirmPassword(_T(""))
	, m_strPhone(_T(""))
{

}

CUserInfo::~CUserInfo()
{
}

void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_CONFIRM, m_strConfirmPassword);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Control(pDX, IDC_COMBO_USERGROUP, m_comboUserGroup);
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUserInfo::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUserInfo message handlers


void CUserInfo::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (CheckData() == FALSE)
		return;

	CString strQuery;
	CString strTemp;

	if (m_nMode == MODE_USER_ADD)
	{
		if (CheckDuplicate() == FALSE)
			return;

		int nPriv = m_comboUserGroup.GetItemData(m_comboUserGroup.GetCurSel());
		g_pDBManager->insertUser(m_strUsername, m_strPassword, nPriv, g_strUsername, m_strPhone);

		g_pDBManager->insertUserHistory(_T("added a user"), m_strUsername);
	}
	else if (m_nMode == MODE_USER_MODIFY)
	{
		int nPriv = m_comboUserGroup.GetItemData(m_comboUserGroup.GetCurSel());
		g_pDBManager->updateUser(m_strUsername, m_strPassword, nPriv, m_strOldname, m_strPhone);

		g_pDBManager->insertUserHistory(_T("modified a user"), m_strOldname + _T(" to ") + m_strUsername);
	}
	g_pUserManageList->RefreshList();

	CDialogEx::OnOK();
}


void CUserInfo::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

BOOL CUserInfo::CheckData()
{
	if (m_strPassword != m_strConfirmPassword)
	{
		MessageBox(_T("The password dismatches."), _T("Message"));
		return FALSE;
	}

	if (m_comboUserGroup.GetCurSel() == CB_ERR)
	{
		MessageBox(_T("Please select the privilege."), _T("Message"));
		return FALSE;
	}
	return TRUE;
}

BOOL CUserInfo::CheckDuplicate()
{
	CString strQuery;

	strQuery.Format(_T("SELECT * FROM user_list WHERE username = '%s'"), m_strUsername);
	MYSQL_RES* result = g_pDBManager->runQuery(CW2A(strQuery.GetBuffer()));

	if (result == NULL)
	{
		MessageBox(_T("Error occured from adding a user"), _T("Message"));
		return FALSE;
	}

	if (result->row_count > 0 && m_strUsername != m_strOldname)
	{
		MessageBox(_T("The username is already exists.Please enter another name"), _T("Message"));
		g_pDBManager->freeSQLResult(result);
		return FALSE;
	}

	g_pDBManager->freeSQLResult(result);

	return TRUE;
}

void CUserInfo::InitializeMembers()
{
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM user_privilege_type"));
	MYSQL_RES* result = 0;
	result = g_pDBManager->runQuery(CW2A(strQuery.GetBuffer()));

	if (result == NULL)
	{
		MessageBox(_T("Error occured in init user add dlg"), _T("Message"));
	}

	CString strTemp;
	while (MYSQL_ROW record = g_pDBManager->fetch_row(result))
	{
		strTemp = record[1];
		int idx = m_comboUserGroup.AddString(strTemp);
		m_comboUserGroup.SetItemData(idx, atoi(record[0]));
	}
	g_pDBManager->freeSQLResult(result);

	m_comboUserGroup.SetCurSel(m_nPrivilege);

	m_strUsername = L"";
	m_strPassword = L"";
	m_strConfirmPassword = L"";
	m_strPhone = L"";
	UpdateData(FALSE);
}

void CUserInfo::SetUserID(int nID)
{

}

BOOL CUserInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeMembers();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
