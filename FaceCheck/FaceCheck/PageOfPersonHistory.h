#pragma once
#include "PersonHistoryList.h"


// CPageOfPersonHistory dialog

class CPageOfPersonHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfPersonHistory)

public:
	CPageOfPersonHistory();
	virtual ~CPageOfPersonHistory();

// Dialog Data
	enum { IDD = IDD_PAGE_PERSONHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CPersonHistoryList m_personHistoryList;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
