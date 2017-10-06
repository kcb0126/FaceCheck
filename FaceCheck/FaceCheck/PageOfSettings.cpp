// PageOfSettings.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfSettings.h"
#include "afxdialogex.h"


// CPageOfSettings dialog

IMPLEMENT_DYNAMIC(CPageOfSettings, CPropertyPage)

CPageOfSettings::CPageOfSettings()
	: CPropertyPage(CPageOfSettings::IDD)
{

}

CPageOfSettings::~CPageOfSettings()
{
}

void CPageOfSettings::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfSettings, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPageOfSettings message handlers


BOOL CPageOfSettings::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_panelSettings.Create(CPanelOfSettings::IDD, this);
	m_panelSettings.ShowWindow(SW_SHOW);
	m_panelSettings.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfSettings::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_panelSettings.m_hWnd != NULL)
	{
		m_panelSettings.SetWindowPos(NULL, rect.Width() / 2 - 290, 0, 580, rect.Height(), SWP_NOZORDER);
		m_panelSettings.UpdateWindow();
	}
}


BOOL CPageOfSettings::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CPropertyPage::OnEraseBkgnd(pDC);
}
