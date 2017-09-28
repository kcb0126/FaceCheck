#pragma once
#include "Resource.h"

// CCellOfMonitorHistory dialog

class CCellOfMonitorHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfMonitorHistory)

public:
	CCellOfMonitorHistory();
	virtual ~CCellOfMonitorHistory();

// Dialog Data
	enum { IDD = IDD_CELL_MONITORHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
