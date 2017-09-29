#pragma once


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
};
