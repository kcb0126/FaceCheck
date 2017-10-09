#pragma once
#include "DlgOfSettings.h"

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
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
//	CDlgOfSettings m_panelSettings;
};
