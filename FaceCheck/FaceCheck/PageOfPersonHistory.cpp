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
	ON_WM_ERASEBKGND()
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
		m_personHistoryList.SetWindowPos(NULL, rect.Width() / 2 - 290, 0, 580, rect.Height(), SWP_NOZORDER);
		m_personHistoryList.UpdateWindow();
	}
}


BOOL CPageOfPersonHistory::OnEraseBkgnd(CDC* pDC)
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
