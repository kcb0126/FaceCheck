#pragma once
#include "resource.h"

// CCellOfPersonManage dialog

class CCellOfPersonManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfPersonManage)

public:
	CCellOfPersonManage();
	virtual ~CCellOfPersonManage();

// Dialog Data
	enum { IDD = IDD_CELL_PERSONMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
