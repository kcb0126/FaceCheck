#pragma once
#include "BitmapButtonPlus.h"


// CDlgMain dialog

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
};
