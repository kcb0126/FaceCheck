// PageOfMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfMonitor.h"
#include "afxdialogex.h"

// CPageOfMonitor dialog

IMPLEMENT_DYNAMIC(CPageOfMonitor, CPropertyPage)

CPageOfMonitor::CPageOfMonitor()
	: CPropertyPage(CPageOfMonitor::IDD)
{

}

CPageOfMonitor::~CPageOfMonitor()
{
}

void CPageOfMonitor::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCREENMODE, m_comboScreenMode);
}


BEGIN_MESSAGE_MAP(CPageOfMonitor, CPropertyPage)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_SCREENMODE, &CPageOfMonitor::OnCbnSelchangeComboScreenmode)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPageOfMonitor message handlers


BOOL CPageOfMonitor::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_cameraViewContainer.Create(CCameraViewContainer::IDD, this);
	m_cameraViewContainer.ShowWindow(SW_SHOW);
	m_cameraViewContainer.UpdateWindow();

	m_monitorHistory.Create(CMonitorHistory::IDD, this);
	m_monitorHistory.ShowWindow(SW_SHOW);
	m_monitorHistory.UpdateWindow();


	m_comboScreenMode.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfMonitor::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_cameraViewContainer.m_hWnd != NULL)
	{
		m_cameraViewContainer.SetWindowPos(NULL, 0, 0, rect.Width() - 480, rect.Height() - 25, SWP_NOZORDER);
		m_cameraViewContainer.SetScreenMode(0);
		m_cameraViewContainer.UpdateWindow();
	}

	if (m_monitorHistory.m_hWnd != NULL)
	{
		m_monitorHistory.SetWindowPos(NULL, rect.Width() - 480, 0, 480, rect.Height(), SWP_NOZORDER);
		m_monitorHistory.UpdateWindow();
	}

	if (m_comboScreenMode.m_hWnd != NULL)
	{
		m_comboScreenMode.SetWindowPos(NULL, rect.Width() / 2 - 270, rect.Height() - 22, 60, 10, SWP_NOZORDER);
	}
}


void CPageOfMonitor::OnCbnSelchangeComboScreenmode()
{
	m_cameraViewContainer.m_bSingleView = FALSE;
	m_cameraViewContainer.SetScreenMode(m_comboScreenMode.GetCurSel());
}


BOOL CPageOfMonitor::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	if (!pDC)return FALSE;

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpDarkGray;
	bmpDarkGray.LoadBitmap(IDB_DARKGRAY);
	pOldBitmap = dc.SelectObject(&bmpDarkGray);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	return TRUE;
}
