// PageOfUserManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfUserManage.h"
#include "afxdialogex.h"


// CPageOfUserManage dialog

IMPLEMENT_DYNAMIC(CPageOfUserManage, CPropertyPage)

CPageOfUserManage::CPageOfUserManage()
	: CPropertyPage(CPageOfUserManage::IDD)
{

}

CPageOfUserManage::~CPageOfUserManage()
{
}

void CPageOfUserManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfUserManage, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPageOfUserManage message handlers


BOOL CPageOfUserManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_userManageList.Create(CUserManageList::IDD, this);
	m_userManageList.ShowWindow(SW_SHOW);
	m_userManageList.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfUserManage::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_userManageList.m_hWnd != NULL)
	{
		m_userManageList.SetWindowPos(NULL, rect.Width() / 2 - 430, 0, 860, rect.Height(), SWP_NOZORDER);
		m_userManageList.UpdateWindow();
	}
}


BOOL CPageOfUserManage::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	if (!pDC)return FALSE;

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
