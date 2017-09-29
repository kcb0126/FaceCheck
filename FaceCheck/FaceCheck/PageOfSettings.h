#pragma once


// CPageOfSettings dialog

class CPageOfSettings : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfSettings)

public:
	CPageOfSettings();
	virtual ~CPageOfSettings();

// Dialog Data
	enum { IDD = IDD_PAGE_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
