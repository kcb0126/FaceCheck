#include "StdAfx.h"
#include "FrameProcessor.h"
using namespace KIP;

FrameProcessor::FrameProcessor()
	:m_eventDoneProcess(FALSE, TRUE)
	, m_eventStop(FALSE, TRUE)
	, m_eventUpdated(FALSE, TRUE)
{
	m_hThread = 0;
}

FrameProcessor::~FrameProcessor()
{
	stop();

	CloseHandle(m_hThread);
	m_hThread = 0;
}

#define CALCU_EFF_WIDTH(effwidth, width, bpp) \
{ \
	effwidth = (int)ceil(width * bpp / 8.0); \
	if (effwidth % 4 != 0) \
	effwidth = (effwidth / 4 + 1) * 4; \
}

void FrameProcessor::setImageSize(int w, int h)
{
	CSingleLock locker1(&m_secImage, TRUE);
	CSingleLock locker2(&m_secBufImage, TRUE);
	m_nImgWidth = w;
	m_nImgHeight = h;
	m_image.Create(w, h, 24, CXIMAGE_FORMAT_BMP);
	m_nImgStepBytes = m_image.GetEffWidth();
	m_nImgSize = m_image.GetEffWidth() * h;
	m_Bufimage.Create(w, h, 24, CXIMAGE_FORMAT_BMP);

	updateImageSize();
}

void FrameProcessor::pushImageData(uint8 * pData, int len)
{
	CSingleLock _locker(&m_secBufImage, TRUE);
	memcpy(m_Bufimage.GetBits(), pData, m_nImgSize);
	m_eventUpdated.SetEvent();
}

void FrameProcessor::pushImageData(const KipImageInfo * pImage)
{
	if (m_nImgWidth != pImage->width || m_nImgHeight != pImage->height)
	{
		setImageSize(pImage->width, pImage->height);
	}

	if (pImage->format == KipImageCodeBGR24u)
	{
		CSingleLock _locker(&m_secBufImage, TRUE);
		memcpy(m_Bufimage.GetBits(), pImage->pixel_addr, m_nImgSize);
	}
	else
	{
		CSingleLock _locker(&m_secBufImage, TRUE);
		m_Bufimage.CreateFromArray(pImage->pixel_addr, pImage->width, pImage->height, KipImageBitsPerPixel(pImage),
			abs(pImage->step_bytes), KipImageIsTopDown(pImage));
	}
	m_eventUpdated.SetEvent();
}

void FrameProcessor::start()
{
	if (m_hThread == NULL)
	{
		m_eventStop.ResetEvent();
		m_hThread = CreateThread(0, 0, ThreadProc, (LPVOID)this, 0, 0);
	}
}

void FrameProcessor::stop()
{
	if (m_hThread == NULL)
		return;
	m_eventStop.SetEvent();
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
	initialize();
}

void FrameProcessor::restart()
{
	stop();
	start();
}

DWORD WINAPI FrameProcessor::ThreadProc(LPVOID param)
{
	((FrameProcessor*)param)->run();
	return 0;
}

void FrameProcessor::run()
{
	CSyncObject* pEvens[] = { &m_eventUpdated, &m_eventStop };
	CMultiLock _lock(pEvens, 2);
	DWORD dwEvent;
	m_eventDoneProcess.SetEvent();
	while (true)
	{
		dwEvent = _lock.Lock(INFINITE, FALSE);
		if (dwEvent == WAIT_OBJECT_0 + 1)
			return;
		m_eventDoneProcess.ResetEvent();
		CSingleLock _lock1(&m_secImage, TRUE);
		{
			CSingleLock _lock2(&m_secBufImage, TRUE);
			memcpy(m_image.GetBits(), m_Bufimage.GetBits(), m_nImgSize);
			m_eventUpdated.ResetEvent();
		}
		KipImageInfo imgInfo;
		imgInfo.format = KipImageCodeBGR24u;
		imgInfo.width = m_nImgWidth;
		imgInfo.height = m_nImgHeight;
		imgInfo.pixel_addr = m_image.GetBits();
		imgInfo.step_bytes = m_image.GetEffWidth();

		processFrame(&imgInfo);

		// 		m_fpsCalculator.setFrame(++m_nFrameNumber);
		PostMessage(m_hOutWnd, UM_FRAME_PROCESSED_NOTIFY, NULL, (LPARAM)this);

		m_eventDoneProcess.SetEvent();
	}
}

void FrameProcessor::draw(CDC * pDC, const CRect & rc)
{
	if (!m_image.IsValid())
		return;

	{
		CSingleLock _dataLock(&m_secImage, FALSE);


		int nImgW = m_image.GetWidth();
		int nImgH = m_image.GetHeight();

		if (nImgW * rc.Height() < nImgH * rc.Width())
		{
			nImgH = rc.Height();
			nImgW = nImgW * rc.Height() / m_image.GetHeight();
		}
		else
		{
			nImgW = rc.Width();
			nImgH = nImgH * rc.Width() / m_image.GetWidth();
		}

		CRect rcFrame = rc;
		rcFrame.DeflateRect((rc.Width() - nImgW) / 2, (rc.Height() - nImgH) / 2);

		m_image.Draw2(pDC->GetSafeHdc(), rcFrame);

		drawOverlay(pDC, rcFrame);
	}
}

void FrameProcessor::processFrame(const KipImageInfo * pFrame)
{

}

void FrameProcessor::drawOverlay(CDC * pDC, const CRect & rc)
{

}

void FrameProcessor::updateImageSize()
{

}

void FrameProcessor::initialize()
{
	// 	m_fpsCalculator.start(0);
	// 	m_nFrameNumber = 0;
}

void FrameProcessor::setOptions()
{
}

CWnd * FrameProcessor::createOutputWnd(CWnd * pParent)
{
	return NULL;
}

void FrameProcessor::onDblClick(const CPoint & pt, const CRect & rc)
{

}


CRect FrameProcessor::CalcFrameRect(const CRect & rc)
{
	CRect rcFrame = rc;
	if (!m_image.IsValid())
		return rcFrame;

	int nImgW = m_image.GetWidth();
	int nImgH = m_image.GetHeight();

	if (nImgW * rc.Height() < nImgH * rc.Width())
	{
		nImgH = rc.Height();
		nImgW = nImgW * rc.Height() / m_image.GetHeight();
	}
	else
	{
		nImgW = rc.Width();
		nImgH = nImgH * rc.Width() / m_image.GetWidth();
	}

	rcFrame.DeflateRect((rc.Width() - nImgW) / 2, (rc.Height() - nImgH) / 2);

	return rcFrame;
}
