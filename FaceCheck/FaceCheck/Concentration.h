#pragma once

#include "FrameProcessor.h"
#include "KipEyeWink.h"
#include "types.h"

#pragma comment(lib, "KIPEyeWink.lib")

using namespace Gdiplus;

namespace KIP
{
	class Concentration : public FrameProcessor
	{
	public:
		Concentration(void);
		~Concentration(void);

	protected:
		virtual void processFrame(const KipImageInfo * pFrame);
		virtual void drawOverlay(CDC * pDC, const CRect & rc);
		virtual void updateImageSize();
		virtual void initialize();

	public:
		void clear_face_eye_data(FaceEyeData * data);
		CxImage RoteateAndCropImage(HBITMAP hBitmap, KipFaceLandmark* ppLandmark, BOOL bLeft);
		bool eyeWink(CxImage & img);

	protected:
		KipEngineHandle		m_hConcentration;
		KipEngineHandle		m_hFaceDetector;

		CCriticalSection	m_secData;
		FaceEyeData			m_faeEyeData;

		int					m_nEyeWink;

		float				m_fConcentration;
		int					m_nEyeCount;
		int					m_nEyeTempCount;
		vector<int>			m_nEyeDatas;
		time_t				m_nEyeStartTime;
	};
}

RECT boundLandmark(const KipFaceLandmark * plandmark, int count);
Bitmap* CreateGdiplusBitmap(HBITMAP hBitmap);
Bitmap* CreateGdiplusBitmap(BITMAP bmBitmap);
void ReleaseGdiplusBitmap(Bitmap *pBitmap);
HBITMAP CreateDIB(int nWidth, int nHeight, int nBitsPixel);