#pragma once
#include "UserManageList.h"
#include "UserInfo.h"

// CPageOfUserManage dialog

class CPageOfUserManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfUserManage)

public:
	CPageOfUserManage();
	virtual ~CPageOfUserManage();

// Dialog Data
	enum { IDD = IDD_PAGE_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CUserManageList m_userManageList;
	CUserInfo m_userInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
