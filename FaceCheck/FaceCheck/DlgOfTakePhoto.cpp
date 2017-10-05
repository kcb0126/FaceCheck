// DlgOfTakePhoto.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "DlgOfTakePhoto.h"
#include "afxdialogex.h"


// CDlgOfTakePhoto dialog

IMPLEMENT_DYNAMIC(CDlgOfTakePhoto, CDialogEx)

CDlgOfTakePhoto::CDlgOfTakePhoto(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgOfTakePhoto::IDD, pParent)
{

}

CDlgOfTakePhoto::~CDlgOfTakePhoto()
{
	if (m_pCameraViewContainer != NULL) {
		delete m_pCameraViewContainer;
		m_pCameraViewContainer = NULL;
	}
}

void CDlgOfTakePhoto::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOfTakePhoto, CDialogEx)
END_MESSAGE_MAP()

BOOL CDlgOfTakePhoto::OnInitDialog() {
	CDialogEx::OnInitDialog();
	InitializeMembers();
	return TRUE;
}

void CDlgOfTakePhoto::InitializeMembers()
{
	m_pCameraViewContainer = new CCameraViewContainer;
	m_pCameraViewContainer->Create(CCameraViewContainer::IDD, this);
	m_pCameraViewContainer->ShowWindow(SW_SHOW);
	m_pCameraViewContainer->UpdateWindow();
	for (int i = 0; i < 16; i++) {
		m_pCameraViewContainer->m_cameraViews[i].m_bIsDlgOfTakePhoto = TRUE;
	}
	SetMyLayout();
}

void CDlgOfTakePhoto::SetMyLayout()
{
	CRect rect;
	GetClientRect(&rect);

	m_pCameraViewContainer->SetWindowPos(NULL
		, 10
		, 50
		, rect.Width() - 20
		, rect.Height() - 60
		, SWP_NOZORDER);
	m_pCameraViewContainer->SetScreenMode(m_pCameraViewContainer->m_nCurrentMode);
}

// CDlgOfTakePhoto message handlers
