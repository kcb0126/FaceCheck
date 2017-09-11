
// FaceCheckDlg.h : header file
//

#pragma once
#include "BitmapButtonPlus.h"


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
};
