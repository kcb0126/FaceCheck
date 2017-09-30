// PersonManageList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonManageList.h"
#include "afxdialogex.h"


// CPersonManageList dialog

IMPLEMENT_DYNAMIC(CPersonManageList, CPropertyPage)

CPersonManageList::CPersonManageList()
	: CPropertyPage(CPersonManageList::IDD)
{

}

CPersonManageList::~CPersonManageList()
{
	// Don't need to delete m_pListOfPersonManage;
}

void CPersonManageList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPersonManageList, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPersonManageList message handlers


void CPersonManageList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pListOfPersonManage != NULL)
	{
		m_pListOfPersonManage->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	}
}


int CPersonManageList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfPersonManage);
	m_pListOfPersonManage = (CListOfPersonManage*)pObject->CreateObject();
	if (!m_pListOfPersonManage->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfPersonManage");
		return -1;
	}

	m_pListOfPersonManage->ShowWindow(SW_SHOW);
	m_pListOfPersonManage->UpdateWindow();

	return 0;
}
