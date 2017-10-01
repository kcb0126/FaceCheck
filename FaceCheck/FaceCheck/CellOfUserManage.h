#pragma once
#include "Resource.h"


// CCellOfUserManage dialog

class CCellOfUserManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfUserManage)

public:
	CCellOfUserManage();
	virtual ~CCellOfUserManage();

// Dialog Data
	enum { IDD = IDD_CELL_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
