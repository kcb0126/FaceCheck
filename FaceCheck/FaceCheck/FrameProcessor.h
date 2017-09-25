#pragma once
#include "ximage.h"
#include "KipCameraManager.h"

#define UM_FRAME_PROCESSED_NOTIFY		WM_USER + 444

namespace KIP
{
	class FrameProcessor
	{
	public:
		FrameProcessor(void);
		~FrameProcessor(void);
		void setImageSize(int w, int h);
		void pushImageData(uint8 * pData, int len);
		void pushImageData(const KipImageInfo * pImage);
		void start();
		void stop();
		void restart();
		void draw(CDC * pDC, const CRect & rc);
	public:
		virtual void setOptions();
		virtual CWnd * createOutputWnd(CWnd * pParent);
		virtual void onDblClick(const CPoint & pt, const CRect & rc);
	protected:
		CRect CalcFrameRect(const CRect & rc);
		static	DWORD WINAPI ThreadProc(LPVOID param);
		void run();
		virtual void processFrame(const KipImageInfo * pFrame);
		virtual void drawOverlay(CDC * pDC, const CRect & rc);
		virtual void updateImageSize();
		virtual void initialize();
	public:
		int					m_nImgWidth;
		int 				m_nImgHeight;
		int 				m_nImgStepBytes;
		int 				m_nImgSize;
		CxImage				m_Bufimage;
		CxImage				m_image;
		CCriticalSection	m_secBufImage;
		CCriticalSection	m_secImage;
		CEvent				m_eventUpdated;
		CEvent				m_eventDoneProcess;
		CEvent				m_eventStop;
		HANDLE				m_hThread;
		CString				m_strName;
		//	FPSCalculator		m_fpsCalculator;
		volatile int		m_nFrameNumber;
	public:
		HWND				m_hOutWnd;
	};
}
