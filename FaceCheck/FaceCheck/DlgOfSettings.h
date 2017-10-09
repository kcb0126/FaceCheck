#pragma once


// CPanelOfSettings dialog

class CPanelOfSettings : public CPropertyPage
{
	DECLARE_DYNAMIC(CPanelOfSettings)

public:
	CPanelOfSettings();
	virtual ~CPanelOfSettings();

// Dialog Data
	enum { IDD = IDD_PANEL_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
