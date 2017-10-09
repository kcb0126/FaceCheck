#pragma once
#include "PersonManageList.h"
#include "PersonInfo.h"

// CPageOfPersonManage dialog

class CPageOfPersonManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfPersonManage)

public:
	CPageOfPersonManage();
	virtual ~CPageOfPersonManage();

// Dialog Data
	enum { IDD = IDD_PAGE_PERSONMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CPersonManageList m_personManageList;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
