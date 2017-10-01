#pragma once
#include "ListOfUserHistory.h"


// CUserHistoryList dialog

class CUserHistoryList : public CPropertyPage
{
	DECLARE_DYNAMIC(CUserHistoryList)

public:
	CUserHistoryList();
	virtual ~CUserHistoryList();

// Dialog Data
	enum { IDD = IDD_USERHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListOfUserHistory* m_pListOfUserHistory = NULL;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
