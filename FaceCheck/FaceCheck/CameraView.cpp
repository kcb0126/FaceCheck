// CameraView.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CameraView.h"
#include "afxdialogex.h"

#define		CM_NOTIFY					WM_USER + 300
#define		NO_SIGNAL_TIME				(5000)
#define		CAMERA_RECONNECT_TIME		(300000)

CBitmap * pNullBitmap = NULL;

class CCameraViewContainer;
// CCameraView dialog

IMPLEMENT_DYNAMIC(CCameraView, CDialogEx)

CCameraView::CCameraView(CWnd* pParent /*=NULL*/)
: CDialogEx(CCameraView::IDD, pParent)
{
	m_nViewIndex = -1;
	m_hCamera = NULL;
	m_pProcessor = NULL;
	m_bNoSingal = TRUE;
	m_bDrawable = FALSE;
	m_dwLastUpdateTime = 0;
}

CCameraView::~CCameraView()
{
	CSingleLock _lock(&m_csProcessor, TRUE);
	if (m_pProcessor)
	{
		m_pProcessor->stop();
		delete m_pProcessor;
	}
	m_pProcessor = NULL;
}

void CCameraView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraView, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(UM_FRAME_PROCESSED_NOTIFY, OnProcessedFrame)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SETTINGS_SELECTCAMERA, &CCameraView::OnSettingsSelectcamera)
	ON_COMMAND(ID_SETTINGS_REMOVECAMERA, &CCameraView::OnSettingsRemovecamera)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCameraView message handlers

//Engine 2017.03.04 add by jsc
void CCameraView::OpenDefaultCamera()
{
	if (m_hCamera && !m_bNoSingal)
		return;

	CString strOptions;
	int nCameraType;

	CString strSection;
	strSection.Format(_T("CameraSetting\\%d"), GetCameraId());
	strOptions = AfxGetApp()->GetProfileString(strSection, _T("CameraName"), _T(""));
	nCameraType = AfxGetApp()->GetProfileInt(strSection, _T("CameraType"), -1);

	if (nCameraType == -1 || strOptions == _T(""))
	{
		SetDrawableView(FALSE);
		return;
	}

	if (m_hCamera)
	{
		KipCM_Stop(m_hCamera);
		KipCM_Destroy(m_hCamera);
	}

	m_hCamera = KipCM_Create(nCameraType, strOptions);

	if (m_hCamera == NULL)
	{
		SetDrawableView(FALSE);
		return;
	}

	KipCM_Play(m_hCamera);
	if (KipCM_GetLastError(m_hCamera) < 0)
	{
		KipCM_Destroy(m_hCamera);
		m_hCamera = NULL;

		m_bNoSingal = TRUE;
		SetDrawableView(FALSE);
		return;
	}
	else
	{
		m_bNoSingal = FALSE;
		SetDrawableView(TRUE);
	}

	KipCM_SetFrameCallback(m_hCamera, _Process, (DWORD_PTR)this);
	KipCM_SetNotifyWindow(m_hCamera, GetSafeHwnd(), CM_NOTIFY);

	CSingleLock _lock(&m_csProcessor, TRUE);
	if (m_pProcessor)
		m_pProcessor->stop();
	else
		m_pProcessor = new FaceProcessor;

	m_pProcessor->m_nProcessorID = m_nViewIndex;	//added by KCH
	m_pProcessor->m_hOutWnd = GetSafeHwnd();
	m_pProcessor->start();
}

//Engine 2017.03.04 add by jsc
void CCameraView::SelectCameraByUser()
{
	CString strOptions;
	int nCameraType = -1;
	if (m_hCamera)
	{
		nCameraType = KipCM_GetIntParam(m_hCamera, L"camera_type", -1);
		KipCM_GetStringParam(m_hCamera, L"options", strOptions.GetBufferSetLength(0x100), 0x100);
		KipCM_Destroy(m_hCamera);
		m_hCamera = NULL;
	}

	CString strSelectOptions;
	strSelectOptions.Format(L"-select_title='Monitor - Select Camera' %s", (LPCTSTR)strOptions);

	m_hCamera = KipCM_Create(KIP_CAMERA_SELECT, strSelectOptions);
	if (m_hCamera == NULL && nCameraType != -1)
		m_hCamera = KipCM_Create(nCameraType, strOptions);

	if (m_hCamera == NULL)
	{
		SetDrawableView(FALSE);
		return;
	}
	KipCM_Play(m_hCamera);
	if (KipCM_GetLastError(m_hCamera) < 0)
	{
		KipCM_Destroy(m_hCamera);
		m_hCamera = NULL;

		m_bNoSingal = TRUE;
		SetDrawableView(FALSE);

		return;
	}
	else
	{
		m_bNoSingal = FALSE;
		SetDrawableView(TRUE);
	}

	KipCM_SetFrameCallback(m_hCamera, _Process, (DWORD_PTR)this);
	KipCM_SetNotifyWindow(m_hCamera, GetSafeHwnd(), CM_NOTIFY);

	CSingleLock _lock(&m_csProcessor, TRUE);

	if (m_pProcessor)
		m_pProcessor->stop();
	else
		m_pProcessor = new FaceProcessor();

	m_pProcessor->m_nProcessorID = m_nViewIndex;	//added by KCH
	m_pProcessor->m_hOutWnd = GetSafeHwnd();
	m_pProcessor->start();

	KipCM_GetStringParam(m_hCamera, L"options", strOptions.GetBufferSetLength(0x100), 0x100);
	nCameraType = KipCM_GetIntParam(m_hCamera, L"camera_type", -1);

	CString strSection;
	strSection.Format(_T("CameraSetting\\%d"), GetCameraId());
	AfxGetApp()->WriteProfileInt(strSection, _T("CameraType"), nCameraType);
	AfxGetApp()->WriteProfileString(strSection, _T("CameraName"), strOptions);
}

//Engine 2017.03.04 add by jsc
int CALLBACK CCameraView::_Process(const KipImageInfo *pImage, DWORD_PTR dwUserData)
{
	return ((CCameraView*)dwUserData)->Process(pImage);
}

//Engine 2016.03.04 add by jsc
int CCameraView::Process(const KipImageInfo *pImage)
{
	CSingleLock _lock(&m_csProcessor, TRUE);

	if (m_pProcessor)
		m_pProcessor->pushImageData(pImage);

	return 0;
}

void CCameraView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//	((CCameraViewContainer*)GetParent())->m_nSelectedView = m_nViewIndex;
	GetParent()->SendMessage(MESSAGE_SELECTED_VIDEO_VIEW, m_nViewIndex);
	CDialogEx::OnLButtonDown(nFlags, point);
}

//add by jsc 2016.03.04
void CCameraView::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetSafeHwnd() == NULL)
		return;

	CRect rc;
	GetClientRect(rc);
	CClientDC dc(this);
	if (m_bmpBuffer.GetSafeHandle())
	{
		m_dcBuffer.SelectObject(pNullBitmap);
		m_bmpBuffer.DeleteObject();
	}
	else
		m_dcBuffer.CreateCompatibleDC(&dc);
	m_bmpBuffer.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	pNullBitmap = m_dcBuffer.SelectObject(&m_bmpBuffer);
}


void CCameraView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(rc);

	if (!m_bDrawable && m_bNoSingal)
		DrawNoSignal(&m_dcBuffer);
	else
	{
		m_dcBuffer.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), BLACKNESS);
		CSingleLock _lock(&m_csProcessor, TRUE);
		if (m_pProcessor)
			m_pProcessor->draw(&m_dcBuffer, rc);
	}

	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &m_dcBuffer, 0, 0, SRCCOPY);
}


BOOL CCameraView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CCameraView::StopCamera()
{
	if (m_hCamera)
	{
		KipCM_SetFrameCallback(m_hCamera, NULL, NULL);
		KipCM_SetNotifyWindow(m_hCamera, NULL, CM_NOTIFY);
		KipCM_Stop(m_hCamera);
		KipCM_Destroy(m_hCamera);
		m_hCamera = NULL;
	}

	SetFrameProcessor(NULL);
}

void CCameraView::SetFrameProcessor(FrameProcessor * processor)
{
	CSingleLock _lock(&m_csProcessor, TRUE);

	if (m_pProcessor)
	{
		m_pProcessor->stop();
		m_pProcessor = NULL;
	}

	InterlockedExchange((LONG*)&m_pProcessor, (LONG)processor);
	if (m_pProcessor == NULL)
		return;

	m_pProcessor->m_hOutWnd = GetSafeHwnd();
	m_pProcessor->start();
}

int CCameraView::GetCameraId()
{
	return m_nViewIndex;
}

LRESULT	CCameraView::OnProcessedFrame(WPARAM wParam, LPARAM lParam)
{
	if (!IsWindowVisible())
		return S_FALSE;

	MSG msg;
	while (::PeekMessage(&msg, GetSafeHwnd(), UM_FRAME_PROCESSED_NOTIFY, UM_FRAME_PROCESSED_NOTIFY, PM_REMOVE))
	{
	}

	if (!m_bDrawable)
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		m_dcBuffer.FillSolidRect(rcClient, RGB(0, 0, 0));
	}

	if (m_hCamera && m_bDrawable)
	{
		InterlockedExchange((LONG*)&m_dwLastUpdateTime, GetTickCount());
		InterlockedExchange((LONG*)&m_bNoSingal, FALSE);
		KillTimer(CAMERA_RECONNECT_TIME);
	}
	else if (m_hCamera == NULL)
	{
		InterlockedExchange((LONG*)&m_bNoSingal, TRUE);
		SetTimer(CAMERA_RECONNECT_TIME, CAMERA_RECONNECT_TIME, NULL);
	}

	Invalidate(FALSE);

	return S_OK;
}

void CCameraView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pProcessor)
	{
		CRect rc;
		GetClientRect(rc);

		if (m_pProcessor->PtInFace(point) != -1)
		{
			m_pProcessor->onDblClick(point, rc);
			return;
		}
	}

	GetParent()->SendMessage(MESSAGE_SINGLE_VIDEO_VIEW, m_nViewIndex);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CCameraView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU_SETTING);

	CPoint ptPos;
	GetCursorPos(&ptPos);
	CMenu* pSubMenu = popMenu.GetSubMenu(0);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, ptPos.x, ptPos.y, this);

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CCameraView::OnSettingsSelectcamera()
{
	SelectCameraByUser();
}


void CCameraView::OnSettingsRemovecamera()
{
	RemoveSelectedCameraSetting();
}


void CCameraView::RemoveSelectedCameraSetting(void)
{
	if (m_hCamera == NULL)
		return;

	KipCM_SetFrameCallback(m_hCamera, NULL, NULL);
	KipCM_SetNotifyWindow(m_hCamera, NULL, CM_NOTIFY);
	KipCM_Stop(m_hCamera);
	KipCM_Destroy(m_hCamera);
	m_hCamera = NULL;

	CString strSection;
	strSection.Format(_T("CameraSetting\\%d"), GetCameraId());
	AfxGetApp()->WriteProfileInt(strSection, _T("CameraType"), -1);
	AfxGetApp()->WriteProfileString(strSection, _T("CameraName"), _T(""));

	InterlockedExchange((LONG*)&m_bNoSingal, TRUE);
	SetDrawableView(FALSE);

	//	NotifyUpdatedCamera();
}

void CCameraView::DrawNoSignal(CDC *pDC)
{
	CRect rc;
	GetClientRect(&rc);
	Bitmap bmpBuffer(rc.Width(), rc.Height());

	CString strTitle;
	CString strDescription;
	if (m_bDrawable)
	{
		strTitle.LoadString(IDS_NO_SIGNAL_TITLE);
		strDescription.LoadString(IDS_NO_SIGNAL_DESC);
	}
	else
	{
		strTitle.LoadString(IDS_NO_CAMERA_TITLE);
		strDescription.LoadString(IDS_NO_CAMERA_DESC);
	}
	{
		SolidBrush brushBk(Color::Black);
		Graphics g(&bmpBuffer);
		g.FillRectangle(&brushBk, 0, 0, rc.Width(), rc.Height());

		g.SetInterpolationMode(InterpolationModeHighQuality);
		g.SetSmoothingMode(SmoothingModeAntiAlias);
		Gdiplus::Font fontTitle(_T("Times New Roman"), 20, FontStyleBold, UnitPixel);
		Gdiplus::Font fontDesc(_T("Times New Roman"), 12, FontStyleItalic, UnitPixel);
		SolidBrush brushFont(Color::OrangeRed);
		SolidBrush brushDesc(Color::PaleGoldenrod);
		StringFormat formatString;
		formatString.SetAlignment(StringAlignmentCenter);
		formatString.SetLineAlignment(StringAlignmentCenter);

		g.DrawString(strTitle, -1, &fontTitle, PointF((REAL)rc.CenterPoint().x, (REAL)rc.CenterPoint().y - 10),
			&formatString, &brushFont);
		g.DrawString(strDescription, -1, &fontDesc, PointF((REAL)rc.CenterPoint().x, (REAL)rc.CenterPoint().y + 10),
			&formatString, &brushDesc);
	}

	Graphics g(pDC->GetSafeHdc());
	g.DrawImage(&bmpBuffer, 0, 0);
}

void CCameraView::SetDrawableView(BOOL drawable)
{
	m_bDrawable = drawable;

	if (!drawable)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		m_dcBuffer.FillSolidRect(rcClient, RGB(0, 0, 0));
	}

	if (m_bDrawable)
	{
		SetTimer(CAMERA_RECONNECT_TIME, CAMERA_RECONNECT_TIME, 0);
		SetTimer(NO_SIGNAL_TIME, NO_SIGNAL_TIME, 0);
	}
	else
	{
		KillTimer(NO_SIGNAL_TIME);
		KillTimer(CAMERA_RECONNECT_TIME);
	}

	Invalidate(FALSE);
}

void CCameraView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == NO_SIGNAL_TIME)
	{
		if ((GetTickCount() - m_dwLastUpdateTime) > NO_SIGNAL_TIME && m_bNoSingal == FALSE)
		{
			InterlockedExchange((LONG*)&m_bNoSingal, TRUE);
			SetTimer(CAMERA_RECONNECT_TIME, CAMERA_RECONNECT_TIME, NULL);
			Invalidate(FALSE);
		}
	}
	else if (nIDEvent == CAMERA_RECONNECT_TIME)
	{
		OpenDefaultCamera();
	}

	CDialogEx::OnTimer(nIDEvent);
}
