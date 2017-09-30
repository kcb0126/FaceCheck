#pragma once


// CCellOfPersonHistory dialog

class CCellOfPersonHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfPersonHistory)

public:
	CCellOfPersonHistory();
	virtual ~CCellOfPersonHistory();

// Dialog Data
	enum { IDD = IDD_CELL_PERSONHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
