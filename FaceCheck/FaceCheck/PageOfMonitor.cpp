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
}


BEGIN_MESSAGE_MAP(CPageOfMonitor, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageOfMonitor message handlers


BOOL CPageOfMonitor::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_cameraViewContainer.Create(CCameraViewContainer::IDD, this);
	m_cameraViewContainer.ShowWindow(SW_SHOW);
	m_cameraViewContainer.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfMonitor::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	if (m_cameraViewContainer.m_hWnd == NULL) {
		return;
	}
	CRect rect;
	GetClientRect(&rect);

	m_cameraViewContainer.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	m_cameraViewContainer.SetScreenMode(0);
	m_cameraViewContainer.UpdateWindow();
}
