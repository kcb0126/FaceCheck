// MonitorHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "MonitorHistory.h"
#include "afxdialogex.h"


// CMonitorHistory dialog

IMPLEMENT_DYNAMIC(CMonitorHistory, CPropertyPage)

CMonitorHistory::CMonitorHistory()
	: CPropertyPage(CMonitorHistory::IDD)
{

}

CMonitorHistory::~CMonitorHistory()
{
	// Don't need to delete m_pListOfMonitorHistory;
}

void CMonitorHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonitorHistory, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMonitorHistory message handlers


BOOL CMonitorHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMonitorHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pListOfMonitorHistory != NULL)
	{
		m_pListOfMonitorHistory->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() - 100, SWP_NOZORDER);
	}
}


int CMonitorHistory::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfMonitorHistory);
	m_pListOfMonitorHistory = (CListOfMonitorHistory*)pObject->CreateObject();
	//	m_pListOfMonitorHistory = new CListOfMonitorHistory;
	if (!m_pListOfMonitorHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create ListOfMonitorHistory");
		return -1;
	}

	m_pListOfMonitorHistory->ShowWindow(SW_SHOW);
	m_pListOfMonitorHistory->UpdateWindow();

	return 0;
}
