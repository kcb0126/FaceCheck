#pragma once
#include "ListOfUserManage.h"


// CUserManageList dialog

class CUserManageList : public CPropertyPage
{
	DECLARE_DYNAMIC(CUserManageList)

public:
	CUserManageList();
	virtual ~CUserManageList();

// Dialog Data
	enum { IDD = IDD_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListOfUserManage* m_pListOfUserManage = NULL;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
