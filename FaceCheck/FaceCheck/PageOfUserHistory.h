#pragma once
#include "UserHistoryList.h"

// CPageOfUserHistory dialog

class CPageOfUserHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfUserHistory)

public:
	CPageOfUserHistory();
	virtual ~CPageOfUserHistory();

// Dialog Data
	enum { IDD = IDD_PAGE_USERHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CUserHistoryList m_userHistoryList;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
