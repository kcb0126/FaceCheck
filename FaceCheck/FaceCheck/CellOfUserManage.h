#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "LabelTrans.h"

// CCellOfUserManage dialog

class CCellOfUserManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfUserManage)

public:
	CCellOfUserManage();
	virtual ~CCellOfUserManage();

// Dialog Data
	enum { IDD = IDD_CELL_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CString m_strUsername;
	CString m_strPrivilege;
	CString m_strCreator;
	CString m_strPhoneNo;
	CString m_strBlocked;
	CLabelTrans m_staticUsername;
	CLabelTrans m_staticPrivilege;
	CLabelTrans m_staticCreatedBy;
	CLabelTrans m_staticCreator;
	CLabelTrans m_staticPhoneNo1;
	CLabelTrans m_staticPhoneNo;
	CLabelTrans m_staticBlocked;

public:
	int m_nIndex;
	afx_msg void OnBnClickedButtonEdit();
};
