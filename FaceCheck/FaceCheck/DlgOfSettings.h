#pragma once


// CDlgOfSettings dialog

class CDlgOfSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOfSettings)

public:
	CDlgOfSettings(CWnd* pParent = NULL);
	virtual ~CDlgOfSettings();

// Dialog Data
	enum { IDD = IDD_PANEL_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	void SetMyLayout(void);
	int SetAutorun(BOOL bAutorun);
	BOOL isDataValid();
	CString getString(int nLevel);

	void exportSettings();
	void importSettings();

	afx_msg void OnNMCustomdrawSliderSettingsThresholdlevel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSettingsApply();
	afx_msg void OnBnClickedButtonSettingsDefault();
	afx_msg void OnDeltaposSpinSettingsSynctime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSettingsExport();
	afx_msg void OnBnClickedButtonSettingsImport();
	CString m_strAddress;
	CString m_strDBName;
	CString m_strPassword;
	CString m_strPlace;
	int m_nPort;
	int m_nSyncPeriod;
	CString m_strLevel;
	CSliderCtrl m_slider;
	CString m_strUsername;
	CSpinButtonCtrl m_spinChangePeriod;
	int m_nFov;
	BOOL m_fAutorun;
};
