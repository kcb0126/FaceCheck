// UserManageList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "UserManageList.h"
#include "afxdialogex.h"


// CUserManageList dialog

IMPLEMENT_DYNAMIC(CUserManageList, CPropertyPage)

CUserManageList::CUserManageList()
	: CPropertyPage(CUserManageList::IDD)
{

}

CUserManageList::~CUserManageList()
{
	// Don't need to delete m_pListOfUserManage;
}

void CUserManageList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserManageList, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CUserManageList message handlers


void CUserManageList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pListOfUserManage != NULL)
	{
		m_pListOfUserManage->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	}
}


int CUserManageList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfUserManage);
	m_pListOfUserManage = (CListOfUserManage*)pObject->CreateObject();
	if (!m_pListOfUserManage->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfUserManage");
		return -1;
	}

	m_pListOfUserManage->ShowWindow(SW_SHOW);
	m_pListOfUserManage->UpdateWindow();

	return 0;
}
