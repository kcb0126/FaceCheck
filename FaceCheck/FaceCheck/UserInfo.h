#pragma once
#include "afxwin.h"


// CUserInfo dialog

class CUserInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfo)

public:
	CUserInfo(CWnd* pParent = NULL);
	virtual ~CUserInfo();

// Dialog Data
	enum { IDD = IDD_USERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strUsername;
	CString m_strPassword;
	CString m_strConfirmPassword;
	CString m_strPhone;

public:
	int m_nMode;
	int m_nPrivilege;
	CString m_strOldname;
	CComboBox m_comboUserGroup;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	BOOL CheckData();
	BOOL CheckDuplicate();
	void InitializeMembers();
	void SetUserID(int nID);
	virtual BOOL OnInitDialog();
};
