#pragma once
#include "CameraViewContainer.h"
#include "MonitorHistory.h"
#include "afxwin.h"

// CPageOfMonitor dialog

class CPageOfMonitor : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageOfMonitor)

public:
	CPageOfMonitor();
	virtual ~CPageOfMonitor();

// Dialog Data
	enum { IDD = IDD_PAGE_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CCameraViewContainer m_cameraViewContainer;
	CMonitorHistory m_monitorHistory;

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CComboBox m_comboScreenMode;
	afx_msg void OnCbnSelchangeComboScreenmode();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
