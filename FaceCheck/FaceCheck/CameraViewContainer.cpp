// CameraViewContainer.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CameraViewContainer.h"
#include "afxdialogex.h"
#include "myGlobal.h"


#define		MESSAGE_OPEN_DEFAULT_CAMERA			WM_USER + 400
#define		UM_WINDOWS_CREATED					WM_USER + 101

int CCameraViewContainer::m_nBorderW = 1;
int CCameraViewContainer::m_nBorderH = 1;

CCameraViewContainer* g_pCameraContainer;
// CCameraViewContainer dialog

IMPLEMENT_DYNAMIC(CCameraViewContainer, CDialogEx)

CCameraViewContainer::CCameraViewContainer(CWnd* pParent /*=NULL*/)
: CDialogEx(CCameraViewContainer::IDD, pParent)
{
	m_nCurrentMode = 0;
	m_bSingleView = FALSE;
	m_nSelectedView = 0;
	g_pCameraContainer = this;
}

CCameraViewContainer::~CCameraViewContainer()
{
	DestroyCamera();
}

void CCameraViewContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraViewContainer, CDialogEx)
	ON_MESSAGE(UM_WINDOWS_CREATED, OnWindowsCreated)
	ON_MESSAGE(MESSAGE_OPEN_DEFAULT_CAMERA, OnMessageOpenDefaultCamera)
	ON_MESSAGE(MESSAGE_SELECTED_VIDEO_VIEW, OnMessageSelectedVideoView)
	ON_MESSAGE(MESSAGE_SINGLE_VIDEO_VIEW, OnMessageSingleVideoView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// set screen layout according to the mode:화면방식에 따라 화면배치를 진행한다
void CCameraViewContainer::SetScreenMode(int arg_nMode)
{
	//if (m_nCurrentMode == arg_nMode)
	//	return;	

	CRect rcRect;
	GetClientRect(&rcRect);

	// set current screen mode:현재 화면방식 설정한다
	m_nCurrentMode = arg_nMode;

	// calculate position and set it:위치계산하고 설정한다
	m_cameraLayout.CalculatePos(rcRect.Width(), rcRect.Height(), m_nCurrentMode);

	if (m_bSingleView)
		m_cameraLayout.rc_cameraViews[m_nSelectedView] = rcRect;

	for (int i = 0; i < MAX_CAMERA_NUM; i++)
	{
		m_cameraViews[i].ShowWindow(SW_HIDE);
	}

	if (m_bSingleView)
	{
		m_cameraLayout.rc_cameraViews[m_nSelectedView].left = m_cameraLayout.m_nSpaceWidth;
		m_cameraLayout.rc_cameraViews[m_nSelectedView].right = rcRect.right - m_cameraLayout.m_nSpaceWidth;
		m_cameraLayout.rc_cameraViews[m_nSelectedView].top = m_cameraLayout.m_nSpaceWidth;
		m_cameraLayout.rc_cameraViews[m_nSelectedView].bottom = rcRect.bottom - m_cameraLayout.m_nSpaceWidth;
		m_cameraViews[m_nSelectedView].MoveWindow(m_cameraLayout.rc_cameraViews[m_nSelectedView]);
		m_cameraViews[m_nSelectedView].ShowWindow(SW_SHOW);
	}
	else
	{
		for (int i = 0; i < m_cameraLayout.GetCameraNum(m_nCurrentMode); i++)
		{
			m_cameraViews[i].MoveWindow(m_cameraLayout.rc_cameraViews[i]);
			m_cameraViews[i].ShowWindow(SW_SHOW);
		}
	}

	UpdateView();
}


// Initialize members:성원들을 초기화한다
void CCameraViewContainer::InitializeMembers(void)
{
	m_nCurrentMode = 1;
	m_nCurrentMode = 0;

	for (int i = 0; i < MAX_CAMERA_NUM; i++)
	{
		m_cameraViews[i].Create(IDD_CAMERA_VIEW, this);
		m_cameraViews[i].m_nViewIndex = i;
		m_cameraViews[i].ShowWindow(SW_HIDE);
	}

}


BOOL CCameraViewContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeMembers();
	SetScreenMode(0);
	PostMessage(UM_WINDOWS_CREATED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CCameraViewContainer::OnWindowsCreated(WPARAM wParam, LPARAM lParam)
{
	//	Licence 처리를 진행한다.

	// 	CString strLicense = AfxGetApp()->GetProfileString(_T("License"), _T("LicenseKey"), _T(""));
	// 	WideCharToMultiByte(CP_ACP, 0, strLicense.GetBuffer(), strLicense.GetLength()+1, theLKEY, 100, NULL, NULL);
	// 
	// 	CMachineNumber clsNumber;
	// 	strcpy(theMachineNumber , clsNumber.GetUniquekey(PROJECT_NAME).c_str());
	// 	CLicenseKey		clsLicense;
	// 
	// 	if (clsLicense.Verify(theMachineNumber , theLKEY) == false)
	// 	{
	// 		CGSTVRestration licDlg;
	// 
	// 		if(licDlg.DoModal() == IDOK)
	// 			AfxMessageBox(_T("Welcome to People Counting Client."));
	// 		else
	// 		{
	// 			PostQuitMessage(0);
	// 			return 0;
	// 		}
	// 	}

	SendMessage(MESSAGE_OPEN_DEFAULT_CAMERA, 0, 0);

	return S_OK;
}

HRESULT CCameraViewContainer::OnMessageOpenDefaultCamera(WPARAM wparam, LPARAM lparam)
{
	for (int i = 0; i < MAX_CAMERA_NUM; i++)
		m_cameraViews[i].OpenDefaultCamera();

	return S_OK;
}

void CCameraViewContainer::DestroyCamera()
{
	for (int i = 0; i < MAX_CAMERA_NUM; i++)
		m_cameraViews[i].StopCamera();
}

HRESULT CCameraViewContainer::OnMessageSingleVideoView(WPARAM wparam, LPARAM lparam)
{
	int view_id = (int)wparam;

	m_nSelectedView = view_id;

	m_bSingleView = !m_bSingleView;

	CRect rcClient;
	GetClientRect(&rcClient);
	SetScreenMode(m_nCurrentMode);

	return S_OK;
}

HRESULT CCameraViewContainer::OnMessageSelectedVideoView(WPARAM wparam, LPARAM lparam)
{
	int view_id = (int)wparam;

	if (view_id != m_nSelectedView || lparam)
	{
		m_nSelectedView = view_id;
		UpdateView();

		//CString strCamera = m_cameraViews[view_id].GetCameraTypeName();
		//CString strDescription;
		//strDescription.Format(str, m_nSelectedView + 1, (LPCTSTR)strCamera);

		//pFrameWnd->GetTrayView()->m_dlgVideoView.m_stViewDescription.SetWindowText(strDescription);
	}

	return S_OK;
}

void CCameraViewContainer::UpdateView()
{
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
}

void CCameraViewContainer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CRect rcClient;
	GetClientRect(&rcClient);

	dc.FillSolidRect(&rcClient, RGB(0, 0, 0));

	if (m_nSelectedView != -1)
	{
		int nHoriCamNum = 0;
		int nVertCamNum = 0;

		if (!m_bSingleView)
		{
			switch (m_nCurrentMode)
			{
			case 0:
				nHoriCamNum = 1; nVertCamNum = 1;
				break;
			case 1:
				nHoriCamNum = 2; nVertCamNum = 2;
				break;
			case 2:
				nHoriCamNum = 3; nVertCamNum = 2;
				break;
			case 3:
				nHoriCamNum = 2; nVertCamNum = 3;
				break;
			case 4:
				nHoriCamNum = 3; nVertCamNum = 3;
				break;
			case 5:
				nHoriCamNum = 4; nVertCamNum = 4;
				break;
			default:
				nHoriCamNum = 1; nVertCamNum = 1;
			}
		}

		CRect rcSelect;
		rcSelect.left = m_cameraLayout.rc_cameraViews[m_nSelectedView].left - m_nBorderW;
		rcSelect.top = m_cameraLayout.rc_cameraViews[m_nSelectedView].top - m_nBorderH;
		rcSelect.right = m_cameraLayout.rc_cameraViews[m_nSelectedView].right;//+ m_nBorderW;
		rcSelect.bottom = m_cameraLayout.rc_cameraViews[m_nSelectedView].bottom;// + m_nBorderH;

		//dc.FillSolidRect(&rcSelect, RGB(255, 0, 0));
		CPen myPen;
		myPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		dc.SelectObject(&myPen);

		dc.MoveTo(rcSelect.left, rcSelect.top);
		dc.LineTo(rcSelect.left, rcSelect.bottom);
		dc.LineTo(rcSelect.right, rcSelect.bottom);
		dc.LineTo(rcSelect.right, rcSelect.top);
		dc.LineTo(rcSelect.left, rcSelect.top);
	}
}


BOOL CCameraViewContainer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	return CDialogEx::OnEraseBkgnd(pDC);
}
