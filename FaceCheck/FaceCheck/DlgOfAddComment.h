#pragma once
#include "afxwin.h"

// CDlgOfAddComment dialog

class CDlgOfAddComment : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOfAddComment)

public:
	CDlgOfAddComment(int nIDX, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOfAddComment();

// Dialog Data
	enum { IDD = IDD_DLG_ADDCOMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	int m_nIDX;
	CString m_strComment;
};
