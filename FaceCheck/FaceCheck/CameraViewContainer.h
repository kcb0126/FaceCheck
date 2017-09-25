#pragma once

#include "CameraView.h"
#include "CameraLayout.h"


// CCameraViewContainer Class
class CCameraViewContainer : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraViewContainer)

public:
	CCameraViewContainer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCameraViewContainer();

	// Dialog Data
	enum { IDD = IDD_CAMERAVIEW_CONTAINER };

public:
	CCameraLayout	m_cameraLayout;
	CCameraView		m_cameraViews[MAX_CAMERA_NUM];

	int				m_nCurrentMode;			// current ScreenMode:현재 화면방식
	int				m_nSelectedView;		// current selected view
	int				m_nViewW;
	int				m_nViewH;
	BOOL			m_bSingleView;

	static int					m_nBorderW;
	static int					m_nBorderH;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	void SetScreenMode(int arg_nMode);	// Set the screen mode:화면방식을 설정한다.
	void InitializeMembers(void);		// Initialize members:성원들을 초기화한다.
	void DestroyCamera();
	void UpdateView();

	HRESULT OnMessageSingleVideoView(WPARAM wparam, LPARAM lparam);
	HRESULT	OnMessageSelectedVideoView(WPARAM wparam, LPARAM lparam);

public:
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnWindowsCreated(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageOpenDefaultCamera(WPARAM wParam, LPARAM lParam);

	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
