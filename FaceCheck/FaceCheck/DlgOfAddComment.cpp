// DlgOfAddComment.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "DlgOfAddComment.h"
#include "afxdialogex.h"


// CDlgOfAddComment dialog

IMPLEMENT_DYNAMIC(CDlgOfAddComment, CDialogEx)

CDlgOfAddComment::CDlgOfAddComment(int nIDX, CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgOfAddComment::IDD, pParent)
, m_strComment(_T(""))
{
	m_strComment = _T("");
	m_nIDX = nIDX;
}

CDlgOfAddComment::~CDlgOfAddComment()
{
}

void CDlgOfAddComment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_strComment);
}


BEGIN_MESSAGE_MAP(CDlgOfAddComment, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgOfAddComment::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgOfAddComment message handlers


void CDlgOfAddComment::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_strComment != _T(""))
	{
		g_pDBManager->addComment(m_nIDX, m_strComment);
	}

	g_pMonitorHistory->RefreshList();
	CDialogEx::OnOK();
}


BOOL CDlgOfAddComment::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CEdit*)(GetDlgItem(IDC_EDIT_COMMENT)))->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
