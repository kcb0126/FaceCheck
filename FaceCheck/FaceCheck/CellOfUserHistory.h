#pragma once
#include "Resource.h"


// CCellOfUserHistory dialog

class CCellOfUserHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfUserHistory)

public:
	CCellOfUserHistory();
	virtual ~CCellOfUserHistory();

// Dialog Data
	enum { IDD = IDD_CELL_USERHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
