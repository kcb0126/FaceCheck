#pragma once


#include "FaceProcessor.h"
using namespace KIP;

#define ID_VIDEO_VIEW					(WM_USER + 1500)

#define MESSAGE_SELECTED_VIDEO_VIEW		WM_USER + 1600
#define MESSAGE_CAMERA_SETTING			WM_USER	+ 1601
#define MESSAGE_SINGLE_VIDEO_VIEW		WM_USER + 1602

// CCameraView dialog

class CCameraView : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraView)

public:
	CCameraView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCameraView();

	// Dialog Data
	enum { IDD = IDD_CAMERA_VIEW };

public:
	int		m_nViewIndex;		// index of the view

	//////////////////////////////////////////////////////////////////////////
	//2016.03.04 add by jsc
public:
	KipEngineHandle		m_hCamera;

	FaceProcessor	*	m_pProcessor;	// camera frame processor
	CCriticalSection	m_csProcessor;	// for sync

	CBitmap				m_bmpBuffer;	// for draw camera data
	CDC					m_dcBuffer;		// for draw camera data
	BOOL				m_bDrawable;	// draw
	volatile BOOL			m_bNoSingal;
	volatile DWORD			m_dwLastUpdateTime;

	BOOL				m_bIsDlgOfTakePhoto = FALSE;

public:
	int		GetCameraId();
	void	OpenDefaultCamera();
	void	SelectCameraByUser();
	void	StopCamera();
	void	SetFrameProcessor(FrameProcessor * processor);
	static int CALLBACK _Process(const KipImageInfo *pImage, DWORD_PTR dwUserData);
	int		Process(const KipImageInfo *pImage);
	void	DrawNoSignal(CDC *pDC);
	void	SetDrawableView(BOOL drawable);
public:
	afx_msg LRESULT	OnProcessedFrame(WPARAM wParam, LPARAM lParam);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSettingsSelectcamera();
	afx_msg void OnSettingsRemovecamera();
	void RemoveSelectedCameraSetting(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
