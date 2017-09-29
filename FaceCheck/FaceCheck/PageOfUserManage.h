#pragma once


// CPageOfUserManage dialog

class CPageOfUserManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfUserManage)

public:
	CPageOfUserManage();
	virtual ~CPageOfUserManage();

// Dialog Data
	enum { IDD = IDD_PAGE_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
