
// FaceCheckDlg.h : header file
//

#pragma once
#include "BitmapButtonPlus.h"
#include "LabelTrans.h"
#include "afxwin.h"


// CFaceCheckDlg dialog
class CFaceCheckDlg : public CDialogEx
{
// Construction
public:
	CFaceCheckDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FACECHECK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

// Background bitmap
private:
	CBitmap m_bmpHome;
public:
	CBitmapButtonPlus m_btnPower;
	CLabelTrans m_lblUsername;
	CLabelTrans m_lblPassword;
	CEdit m_edtUsername;
	CEdit m_edtPassword;
	CBitmapButtonPlus m_btnLogin;
	afx_msg void OnBnClickedButton1();
	CString m_strUsername;
	CString m_strPassword;
	virtual void OnOK();
	virtual void OnCancel();
};
