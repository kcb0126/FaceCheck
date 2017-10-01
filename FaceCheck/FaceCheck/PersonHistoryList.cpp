// PersonHistoryList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonHistoryList.h"
#include "afxdialogex.h"


// CPersonHistoryList dialog

IMPLEMENT_DYNAMIC(CPersonHistoryList, CPropertyPage)

CPersonHistoryList::CPersonHistoryList()
	: CPropertyPage(CPersonHistoryList::IDD)
{

}

CPersonHistoryList::~CPersonHistoryList()
{
}

void CPersonHistoryList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPersonHistoryList, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPersonHistoryList message handlers


void CPersonHistoryList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pListOfPersonHistory != NULL)
	{
		m_pListOfPersonHistory->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	}
}


int CPersonHistoryList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfPersonHistory);
	m_pListOfPersonHistory = (CListOfPersonHistory*)pObject->CreateObject();
	if (!m_pListOfPersonHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfPersonHistory");
		return -1;
	}

	m_pListOfPersonHistory->ShowWindow(SW_SHOW);
	m_pListOfPersonHistory->UpdateWindow();

	return 0;
}
