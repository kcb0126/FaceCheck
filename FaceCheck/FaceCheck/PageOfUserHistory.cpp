// PageOfUserHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfUserHistory.h"
#include "afxdialogex.h"


// CPageOfUserHistory dialog

IMPLEMENT_DYNAMIC(CPageOfUserHistory, CPropertyPage)

CPageOfUserHistory::CPageOfUserHistory()
	: CPropertyPage(CPageOfUserHistory::IDD)
{

}

CPageOfUserHistory::~CPageOfUserHistory()
{
}

void CPageOfUserHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfUserHistory, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageOfUserHistory message handlers


BOOL CPageOfUserHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_userHistoryList.Create(CUserHistoryList::IDD, this);
	m_userHistoryList.ShowWindow(SW_SHOW);
	m_userHistoryList.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfUserHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_userHistoryList.m_hWnd != NULL)
	{
		m_userHistoryList.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
		m_userHistoryList.UpdateWindow();
	}
}
