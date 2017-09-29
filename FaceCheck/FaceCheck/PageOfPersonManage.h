#pragma once


// CPageOfPersonManage dialog

class CPageOfPersonManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfPersonManage)

public:
	CPageOfPersonManage();
	virtual ~CPageOfPersonManage();

// Dialog Data
	enum { IDD = IDD_PAGE_PERSONMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
