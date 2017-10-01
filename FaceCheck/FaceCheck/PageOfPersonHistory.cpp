// PageOfPersonHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfPersonHistory.h"
#include "afxdialogex.h"


// CPageOfPersonHistory dialog

IMPLEMENT_DYNAMIC(CPageOfPersonHistory, CPropertyPage)

CPageOfPersonHistory::CPageOfPersonHistory()
	: CPropertyPage(CPageOfPersonHistory::IDD)
{

}

CPageOfPersonHistory::~CPageOfPersonHistory()
{
}

void CPageOfPersonHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfPersonHistory, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageOfPersonHistory message handlers


BOOL CPageOfPersonHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_personHistoryList.Create(CPersonHistoryList::IDD, this);
	m_personHistoryList.ShowWindow(SW_SHOW);
	m_personHistoryList.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfPersonHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_personHistoryList.m_hWnd != NULL)
	{
		m_personHistoryList.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
		m_personHistoryList.UpdateWindow();
	}
}
