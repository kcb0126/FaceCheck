#pragma once
#include "ListOfPersonManage.h"

// CPersonManageList dialog

class CPersonManageList : public CPropertyPage
{
	DECLARE_DYNAMIC(CPersonManageList)

public:
	CPersonManageList();
	virtual ~CPersonManageList();

// Dialog Data
	enum { IDD = IDD_PERSONMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListOfPersonManage* m_pListOfPersonManage = NULL;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
