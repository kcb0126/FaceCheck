#pragma once


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
};
