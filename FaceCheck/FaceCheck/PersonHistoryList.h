#pragma once
#include "ListOfPersonHistory.h"

// CPersonHistoryList dialog

class CPersonHistoryList : public CPropertyPage
{
	DECLARE_DYNAMIC(CPersonHistoryList)

public:
	CPersonHistoryList();
	virtual ~CPersonHistoryList();

// Dialog Data
	enum { IDD = IDD_PERSONHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListOfPersonHistory* m_pListOfPersonHistory = NULL;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
