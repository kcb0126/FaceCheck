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
END_MESSAGE_MAP()


// CPageOfPersonManage message handlers


BOOL CPageOfPersonManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_personManageList.Create(CPersonManageList::IDD, this);
	m_personManageList.ShowWindow(SW_SHOW);
	m_personManageList.UpdateWindow();

	m_personInfo.Create(CPersonInfo::IDD, this);
	m_personInfo.ShowWindow(SW_SHOW);
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
		m_personManageList.SetWindowPos(NULL, 0, 0, rect.Width() / 2, rect.Height(), SWP_NOZORDER);
		m_personManageList.UpdateWindow();
	}

	if (m_personInfo.m_hWnd != NULL)
	{
		m_personInfo.SetWindowPos(NULL, rect.Width() / 2, 0, rect.Width() / 2, rect.Height(), SWP_NOZORDER);
		m_personInfo.UpdateWindow();
	}
}
