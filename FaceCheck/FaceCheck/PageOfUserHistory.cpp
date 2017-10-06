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
	ON_WM_ERASEBKGND()
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
		m_userHistoryList.SetWindowPos(NULL, rect.Width() / 2 - 570, 0, 1140, rect.Height(), SWP_NOZORDER);
		m_userHistoryList.UpdateWindow();
	}
}

BOOL CPageOfUserHistory::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpLightGray;
	bmpLightGray.LoadBitmap(IDB_LIGHTGRAY);
	pOldBitmap = dc.SelectObject(&bmpLightGray);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	return TRUE;
}
