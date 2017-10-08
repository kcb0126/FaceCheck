// PageOfPersonManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfPersonManage.h"
#include "afxdialogex.h"


// CPageOfPersonManage dialog

IMPLEMENT_DYNAMIC(CPageOfPersonManage, CPropertyPage)

CPageOfPersonManage::CPageOfPersonManage()
	: CPropertyPage(CPageOfPersonManage::IDD)
{

}

CPageOfPersonManage::~CPageOfPersonManage()
{
}

void CPageOfPersonManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfPersonManage, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPageOfPersonManage message handlers


BOOL CPageOfPersonManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_personManageList.Create(CPersonManageList::IDD, this);
	m_personManageList.ShowWindow(SW_SHOW);
	m_personManageList.UpdateWindow();

	m_personInfo.Create(CPersonInfo::IDD, this);
	m_personInfo.ShowWindow(SW_HIDE);
	m_personInfo.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageOfPersonManage::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_personManageList.m_hWnd != NULL)
	{
		m_personManageList.SetWindowPos(NULL, rect.Width() / 2 - 277, 0, 553, rect.Height(), SWP_NOZORDER);
		m_personManageList.UpdateWindow();
	}

	if (m_personInfo.m_hWnd != NULL)
	{
		m_personInfo.SetWindowPos(NULL, rect.Width() / 2 + 277, 0, rect.Width() / 2, rect.Height(), SWP_NOZORDER);
		m_personInfo.UpdateWindow();
	}
}


BOOL CPageOfPersonManage::OnEraseBkgnd(CDC* pDC)
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
