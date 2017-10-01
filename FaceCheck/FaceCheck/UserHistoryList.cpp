// UserHistoryList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "UserHistoryList.h"
#include "afxdialogex.h"


// CUserHistoryList dialog

IMPLEMENT_DYNAMIC(CUserHistoryList, CPropertyPage)

CUserHistoryList::CUserHistoryList()
	: CPropertyPage(CUserHistoryList::IDD)
{

}

CUserHistoryList::~CUserHistoryList()
{
}

void CUserHistoryList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserHistoryList, CPropertyPage)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUserHistoryList message handlers


int CUserHistoryList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfUserHistory);
	m_pListOfUserHistory = (CListOfUserHistory*)pObject->CreateObject();
	if (!m_pListOfUserHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfUserHistory");
		return -1;
	}

	m_pListOfUserHistory->ShowWindow(SW_SHOW);
	m_pListOfUserHistory->UpdateWindow();

	return 0;
}


void CUserHistoryList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (!m_pListOfUserHistory != NULL)
	{
		m_pListOfUserHistory->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	}
}
