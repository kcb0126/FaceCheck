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
	if (m_pListOfMonitorHistory != NULL)
	{
		delete m_pListOfMonitorHistory;
		m_pListOfMonitorHistory = NULL;
	}
}

void CMonitorHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonitorHistory, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMonitorHistory message handlers


BOOL CMonitorHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfMonitorHistory);
	m_pListOfMonitorHistory = (CListOfMonitorHistory*)pObject->CreateObject();

	if (!m_pListOfMonitorHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create ListOfMonitorHistory");
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMonitorHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	
	m_pListOfMonitorHistory->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() - 100, SWP_NOZORDER);
}
