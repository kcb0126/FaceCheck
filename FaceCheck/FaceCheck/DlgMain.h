#pragma once
#include "BitmapButtonPlus.h"


// CDlgMain dialog

#define TAB_MONITOR			0
#define TAB_PERSONMANAGE	1
#define TAB_PERSONHISTORY	2
#define TAB_USERMANAGE		3
#define TAB_USERHISTORY		4
#define TAB_SETTINGS		5

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMain();

// Dialog Data
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	CBitmapButtonPlus m_btnMonitor;
	CBitmapButtonPlus m_btnPersonmanage;
	CBitmapButtonPlus m_btnPersonhistory;
	CBitmapButtonPlus m_btnUsermanage;
	CBitmapButtonPlus m_btnUserhistory;
	CBitmapButtonPlus m_btnSettings;

public:
	void SetTab(int nTabIndex);
	afx_msg void OnBnClickedBtnMonitor();
	afx_msg void OnBnClickedBtnPersonmanage();
	afx_msg void OnBnClickedBtnPersonhistory();
	afx_msg void OnBnClickedBtnUsermange();
	afx_msg void OnBnClickedBtnUserhistory();
	afx_msg void OnBnClickedBtnSettings();
};
