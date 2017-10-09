#pragma once
#include "afxwin.h"


// CDlgOfWarning dialog

class CDlgOfWarning : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOfWarning)

public:
	CDlgOfWarning(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOfWarning();

public:
	int m_nWarningType;                    // 0: Forbidden Age, 1: Check IDCard

	BOOL m_bNowWarning;


// Dialog Data
	enum { IDD = IDD_DLG_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();

public:
	void StartWarning();
	CButton m_btnWarning;
};
