#pragma once


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
};
