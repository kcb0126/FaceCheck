#include "StdAfx.h"
#include "Concentration.h"
#include "ximage.h"
#include "licenseDef.h"

using namespace KIP;

Concentration::Concentration(void)
{
	m_hFaceDetector = KipFD_Create(FACE_DETECT_ID, FACE_DETECT_KEY);
	m_hConcentration = KipEW_Create(EYE_WINK_ID, EYE_WINK_KEY);

	m_nEyeWink = -1;
	clear_face_eye_data(&m_faeEyeData);

	m_fConcentration = 0.f;
	m_nEyeCount = 0;
	m_nEyeTempCount = 0;

	time(&m_nEyeStartTime);
}

Concentration::~Concentration(void)
{
	KipEW_Destroy(m_hConcentration);
	clear_face_eye_data(&m_faeEyeData);
}

float GetAngleRotatedFace(PointF ptfStart, PointF ptfEnd)
{
	float fDiffX = ptfStart.X - ptfEnd.X;
	float fDiffY = ptfStart.Y - ptfEnd.Y;

	return 180 + float(atan2(fDiffY, fDiffX) * 180 / PI);
}

PixelFormat GetPixelFormat(int nBitsPixel)
{
	PixelFormat pixelFormat;
	switch (nBitsPixel)
	{
	case 1:
		pixelFormat = PixelFormat1bppIndexed;
		break;
	case 4:
		pixelFormat = PixelFormat4bppIndexed;
		break;
	case 8:
		pixelFormat = PixelFormat8bppIndexed;
		break;
	case 16:
		pixelFormat = PixelFormat16bppRGB565;
		break;
	case 24:
		pixelFormat = PixelFormat24bppRGB;
		break;
	case 32:
		pixelFormat = PixelFormat32bppARGB;
		break;
	}

	return pixelFormat;
}

Bitmap* CreateGdiplusBitmap(BITMAP bmBitmap)
{
	return ::new Bitmap(bmBitmap.bmWidth, bmBitmap.bmHeight, -bmBitmap.bmWidthBytes, GetPixelFormat(bmBitmap.bmBitsPixel), (PBYTE)bmBitmap.bmBits + bmBitmap.bmWidthBytes * (bmBitmap.bmHeight - 1));
}

Bitmap* CreateGdiplusBitmap(HBITMAP hBitmap)
{
	if (hBitmap == NULL)
		return NULL;

	BITMAP bmBitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bmBitmap);

	return ::new Bitmap(bmBitmap.bmWidth, bmBitmap.bmHeight, -bmBitmap.bmWidthBytes, GetPixelFormat(bmBitmap.bmBitsPixel), (PBYTE)bmBitmap.bmBits + bmBitmap.bmWidthBytes * (bmBitmap.bmHeight - 1));
}

void ReleaseGdiplusBitmap(Bitmap *pBitmap)
{
	if (pBitmap == NULL)
		return;

	::delete pBitmap;
}

HBITMAP CreateDIB(int nWidth, int nHeight, int nBitsPixel)
{
	BITMAPINFO bmi;

	ZeroMemory(&bmi, sizeof(bmi));
	bmi.bmiHeader.biBitCount = nBitsPixel;
	bmi.bmiHeader.biHeight = nHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = nWidth;

	return CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
}
HBITMAP CropBITMAP(HBITMAP hBitmap, RECT rcCrop)
{
	HDC hDCDesk = GetDC(NULL);

	int nImgW = rcCrop.right - rcCrop.left;
	int nImgH = rcCrop.bottom - rcCrop.top;

	BITMAP bmBitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bmBitmap);

	RECT rcImage;
	rcImage.left = 0; rcImage.top = 0;
	rcImage.right = bmBitmap.bmWidth - 1; rcImage.bottom = bmBitmap.bmHeight - 1;

	RECT rcTemp;
	IntersectRect(&rcTemp, &rcImage, &rcCrop);

	int nTempW = rcTemp.right - rcTemp.left;
	int nTempH = rcTemp.bottom - rcTemp.top;

	HDC hDCSrc = CreateCompatibleDC(hDCDesk);
	HBITMAP hRet = (HBITMAP)SelectObject(hDCSrc, hBitmap);

	HDC hDCCrop = CreateCompatibleDC(hDCDesk);
	HBITMAP hCropBitmap = CreateDIB(nImgW, nImgH, 24);
	HBITMAP hCropRet = (HBITMAP)SelectObject(hDCCrop, hCropBitmap);

	//만일 자르려는 4각형이 이미지를 벗어나는 경우
	//이미지의 모자라는 령역을 이미지의 평균색상으로 채운다.
	if (nTempW < nImgW || nTempH < nImgH)
	{
		HDC hDCTemp = CreateCompatibleDC(hDCDesk);
		HBITMAP hTempBitmap = CreateDIB(nTempW, nTempH, 24);
		HBITMAP hTemp = (HBITMAP)SelectObject(hDCTemp, hTempBitmap);

		BitBlt(hDCTemp, 0, 0, nTempW, nTempH, hDCSrc, rcTemp.left, rcTemp.top, SRCCOPY);

		GetObject(hTempBitmap, sizeof(BITMAP), &bmBitmap);

		int nR = 0, nG = 0, nB = 0;
		PBYTE pLineBits = NULL;

		for (int y = 0; y < bmBitmap.bmHeight; y++)
		{
			pLineBits = (PBYTE)bmBitmap.bmBits + y * bmBitmap.bmWidthBytes;

			for (int x = 0; x < bmBitmap.bmWidth; x++)
			{
				nR += pLineBits[2];
				nG += pLineBits[1];
				nB += pLineBits[0];

				pLineBits += 3;
			}
		}

		int nPixelSize = bmBitmap.bmWidth * bmBitmap.bmHeight;
		nR /= nPixelSize;
		nG /= nPixelSize;
		nB /= nPixelSize;

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(nR, nG, nB));
		HBRUSH hBrush = CreateSolidBrush(RGB(nR, nG, nB));

		SelectObject(hDCCrop, hPen);
		SelectObject(hDCCrop, hBrush);

		Rectangle(hDCCrop, 0, 0, nImgW, nImgH);

		int nLeft = 0;
		if (rcCrop.left < 0)
			nLeft = -rcCrop.left;

		int nTop = 0;
		if (rcCrop.top < 0)
			nTop = -rcCrop.top;

		BitBlt(hDCCrop, nLeft, nTop, nTempW, nTempH, hDCTemp, 0, 0, SRCCOPY);

		SelectObject(hDCTemp, hTemp);

		DeleteObject(hPen);
		DeleteObject(hBrush);
		DeleteObject(hTempBitmap);
		DeleteObject(hDCTemp);
	}
	else
		BitBlt(hDCCrop, 0, 0, nImgW, nImgH, hDCSrc, rcCrop.left, rcCrop.top, SRCCOPY);

	SelectObject(hDCSrc, hRet);
	SelectObject(hDCCrop, hCropRet);

	ReleaseDC(NULL, hDCDesk);
	DeleteObject(hDCSrc);
	DeleteObject(hDCCrop);

	return hCropBitmap;
}

RECT boundLandmark(const KipFaceLandmark * plandmark, int count)
{
	RECT rc;
	rc.right = rc.left = (int)plandmark[0].pos.x;
	rc.bottom = rc.top = (int)plandmark[0].pos.y;

	for (int i = 1; i < count; i++)
	{
		rc.left = (int)min(rc.left, (int)plandmark[i].pos.x);
		rc.right = (int)max(rc.right, (int)plandmark[i].pos.x);
		rc.top = (int)min(rc.top, (int)plandmark[i].pos.y);
		rc.bottom = (int)max(rc.bottom, (int)plandmark[i].pos.y);
	}

	return rc;
}

RectF GetBoundRect(PointF *pPtf, int nCount)
{
	float X = pPtf[0].X, Y = pPtf[0].Y;
	float Right = pPtf[0].X, Bottom = pPtf[0].Y;

	for (int i = 1; i < nCount; i++)
	{
		X = min(X, pPtf[i].X);
		Y = min(Y, pPtf[i].Y);
		Right = max(Right, pPtf[i].X);
		Bottom = max(Bottom, pPtf[i].Y);
	}

	return RectF(X, Y, Right - X, Bottom - Y);
}

void GetCropRect(PointF *pt, CRect &rcCrop)
{
	if (pt[1].X > pt[3].X)
		swap(pt[1], pt[3]);

	KipCoord2f ptn;
	ptn.x = pt[1].X;
	ptn.y = (pt[1].Y + pt[3].Y) / 2;

	KipCoord2f ptTopLeft;
	ptTopLeft.x = pt[1].X;
	ptTopLeft.y = ptn.y - (pt[3].X - pt[1].X) / 2;

	rcCrop.left = (long)(ptTopLeft.x + 0.5f);
	rcCrop.top = (long)(ptTopLeft.y + 0.5f);
	rcCrop.right = (long)(pt[3].X + 0.5f);
	rcCrop.bottom = (long)(ptTopLeft.y + (pt[3].X - pt[1].X) + 0.5f);
}

HBITMAP RotateFaceImage(HBITMAP hBitmap, PointF* ptfEyePoint, Matrix* pMatrix, BOOL bLeft)
{
	Bitmap *pDrawBitmap = CreateGdiplusBitmap(hBitmap);

	Matrix appineMat;

	float fCx = pDrawBitmap->GetWidth() / 2.0f;
	float fCy = pDrawBitmap->GetHeight() / 2.0f;

	float fAngle;
	if (bLeft == FALSE)
		fAngle = GetAngleRotatedFace(ptfEyePoint[1], ptfEyePoint[0]);
	else
		fAngle = GetAngleRotatedFace(ptfEyePoint[0], ptfEyePoint[3]);

	appineMat.RotateAt(-fAngle, PointF(fCx, fCy), MatrixOrderAppend);

	PointF ptfImage[4];
	ptfImage[0] = PointF(0.0f, 0.0f);
	ptfImage[1] = PointF((float)pDrawBitmap->GetWidth(), 0.0f);
	ptfImage[2] = PointF((float)pDrawBitmap->GetWidth(), (float)pDrawBitmap->GetHeight());
	ptfImage[3] = PointF(0.0f, (float)pDrawBitmap->GetHeight());

	appineMat.TransformPoints(ptfImage, 4);

	RectF rcfConvert = GetBoundRect(ptfImage, 4);

	int nConvW = int(rcfConvert.Width + 0.5f);
	int nConvH = int(rcfConvert.Height + 0.5f);
	HDC hDeskDC = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hDeskDC);

	HBITMAP hRotateImage = CreateDIB(nConvW, nConvH, 24);
	HBITMAP hRotateTemp = (HBITMAP)SelectObject(hDC, hRotateImage);

	Matrix drawMat;
	Matrix *pDrawMat = &drawMat;

	if (pMatrix != NULL)
		pDrawMat = pMatrix;

	{
		Graphics graphics(hDC);
		graphics.SetInterpolationMode(InterpolationModeInvalid);
		graphics.SetSmoothingMode(SmoothingModeInvalid);
		graphics.SetCompositingMode(CompositingModeSourceCopy);

		fCx = rcfConvert.Width / 2;
		fCy = rcfConvert.Height / 2;

		pDrawMat->Translate(-rcfConvert.X, -rcfConvert.Y, MatrixOrderAppend);
		pDrawMat->RotateAt(-fAngle, PointF(fCx, fCy), MatrixOrderAppend);
		pDrawMat->TransformPoints(ptfEyePoint, 4);

		graphics.SetTransform(pDrawMat);
		graphics.DrawImage(pDrawBitmap, 0, 0);
	}

	DeleteDC(hDC);
	ReleaseDC(NULL, hDeskDC);
	ReleaseGdiplusBitmap(pDrawBitmap);

	SelectObject(hDC, hRotateTemp);

	return hRotateImage;
}

void ConvertImage(CxImage img, PBYTE pImage, BOOL bForward)
{
	PBYTE pLineBits = NULL;

	int nIndex = 0;
	for (int y = 0; y < (int)img.GetHeight(); y++)
	{
		pLineBits = (PBYTE)img.GetBits() + y * img.GetEffWidth();

		for (int x = 0; x < (int)img.GetWidth(); x++)
		{
			if (bForward)
				pImage[nIndex] = pLineBits[0];
			else
			{
				pLineBits[0] = pImage[nIndex];
				//				pLineBits[1] = pImage[nIndex];
				//				pLineBits[2] = pImage[nIndex];
			}

			nIndex++;
			pLineBits++;
			//			pLineBits += 3;
		}
	}
}

void HistogramNormalize(PBYTE pbyImage)
{
	float* pflImage = new float[400];
	float fMean = 0, fStdDev = 0;

	int i;
	for (i = 0; i<400; i++)
		pflImage[i] = (float)pbyImage[i];

	//평균
	for (i = 0; i< 400; i++)
		fMean += pflImage[i];
	fMean /= (float)400;

	//Xi-Mean
	for (i = 0; i< 400; i++)
		pflImage[i] -= fMean;

	//표준편차
	for (i = 0; i< 400; i++)
		fStdDev += pflImage[i] * pflImage[i];
	fStdDev /= (float)400;
	fStdDev = (float)sqrt(fStdDev);

	//Xi * 64 / StdDev + 127 ,   0 - 254사이값으로 변환

	for (i = 0; i< 400; i++)
	{
		pflImage[i] = pflImage[i] * 64.f / fStdDev + 127.f + 0.5f;
		pbyImage[i] = min(max((BYTE)pflImage[i], 0), 255);
	}

	delete[] pflImage;
}

CxImage Concentration::RoteateAndCropImage(HBITMAP hBitmap, KipFaceLandmark* ppLandmark, BOOL bLeft)
{
	PointF ptfEye[4];
	CRect rcCrop;

	if (bLeft == FALSE)
	{
		ptfEye[0].X = ppLandmark[12].pos.x;
		ptfEye[0].Y = ppLandmark[12].pos.y;
		ptfEye[1].X = ppLandmark[4].pos.x;
		ptfEye[1].Y = ppLandmark[4].pos.y;
		ptfEye[2].X = ppLandmark[13].pos.x;
		ptfEye[2].Y = ppLandmark[13].pos.y;
		ptfEye[3].X = ppLandmark[5].pos.x;
		ptfEye[3].Y = ppLandmark[5].pos.y;
	}
	else
	{
		ptfEye[0].X = ppLandmark[14].pos.x;
		ptfEye[0].Y = ppLandmark[14].pos.y;
		ptfEye[1].X = ppLandmark[6].pos.x;
		ptfEye[1].Y = ppLandmark[6].pos.y;
		ptfEye[2].X = ppLandmark[15].pos.x;
		ptfEye[2].Y = ppLandmark[15].pos.y;
		ptfEye[3].X = ppLandmark[7].pos.x;
		ptfEye[3].Y = ppLandmark[7].pos.y;
	}

	HBITMAP hRotate = RotateFaceImage(hBitmap, ptfEye, NULL, bLeft);
	GetCropRect(ptfEye, rcCrop);

	HBITMAP hCrop = CropBITMAP(hRotate, rcCrop);
	BITMAP bmCrop;
	GetObject(hCrop, sizeof(BITMAP), &bmCrop);

	CxImage ximage(bmCrop.bmWidth, bmCrop.bmHeight, 24);
	memcpy(ximage.GetBits(), bmCrop.bmBits, ximage.GetEffWidth() * ximage.GetHeight());
	ximage.Resample(20, 20);

	DeleteObject(hRotate);
	DeleteObject(hCrop);

	return ximage;
}

bool Concentration::eyeWink(CxImage & img)
{
	KipImageInfo imgInfo;
	imgInfo.format = KipImageCodeBGR24u;
	imgInfo.width = img.GetWidth();
	imgInfo.height = img.GetHeight();
	imgInfo.pixel_addr = img.GetBits();
	imgInfo.step_bytes = img.GetEffWidth();

	return KipEW_Estimate(m_hConcentration, &imgInfo) >= 50;
}

void Concentration::processFrame(const KipImageInfo * pFrame)
{
	if (m_hFaceDetector == NULL || m_hConcentration == NULL)
		return;

	FaceEyeData faceData;
	clear_face_eye_data(&faceData);

	int nFaceSize = 0;
	int nCount = KipFD_Detect(m_hFaceDetector, pFrame);
	KipFaceFeature faceFeature;
	float			faceAngle = 0;

	for (int i = 0; i < nCount; i++)
	{
		KipFaceLandmark * landmarks;
		int nLandmarkCount = KipFD_GetLandmarks(m_hFaceDetector, i, &landmarks);
		KipFD_GetFeature(m_hFaceDetector, pFrame, i, &faceFeature);

		RECT bound = boundLandmark(landmarks, nLandmarkCount);
		int nSize = (bound.bottom - bound.top) * (bound.right - bound.left);
		if (nSize > nFaceSize)
		{
			nFaceSize = nSize;
			faceData.bound = bound;
			memcpy(faceData.land, landmarks, sizeof(KipFaceLandmark) * nLandmarkCount);
			faceData.bFace = TRUE;
			faceAngle = faceFeature.anglePan;
		}

		KipFD_FreeFeature(&faceFeature);
		KipFD_FreeLandmarks(landmarks);
	}

	m_nEyeWink = -1;

	if (faceData.bFace == TRUE)
	{
		HBITMAP hBitmap = m_image.MakeBitmap();

		CxImage imgLeftEye = RoteateAndCropImage(hBitmap, faceData.land, FALSE);
		CxImage imgRightEye = RoteateAndCropImage(hBitmap, faceData.land, TRUE);

		if (eyeWink(imgLeftEye) || eyeWink(imgRightEye))
			m_nEyeWink = 1;
		else
			m_nEyeWink = 0;
		if (fabs(faceAngle) <= 15.f)
		{
			time_t	tTime;
			time(&tTime);

			if (difftime(tTime, m_nEyeStartTime) > 1.0)
			{
				m_nEyeStartTime = tTime;

				int nTotal = 0;
				for (int i = 0; i < (int)m_nEyeDatas.size(); i++)
					nTotal += m_nEyeDatas[i];

				if (m_nEyeCount + m_nEyeTempCount <= 0)
					m_fConcentration = 0.f;
				else
					m_fConcentration = (m_fConcentration * m_nEyeCount + nTotal) / (m_nEyeCount + m_nEyeTempCount);

				m_nEyeCount += m_nEyeTempCount;
				m_nEyeDatas.clear();
				m_nEyeTempCount = 0;
			}
			else
			{
				m_nEyeDatas.push_back(m_nEyeWink);
				m_nEyeTempCount++;
			}
		}

		DeleteObject(hBitmap);
	}

	CSingleLock lock(&m_secData, TRUE);
	clear_face_eye_data(&m_faeEyeData);
	m_faeEyeData = faceData;
}

void Concentration::drawOverlay(CDC * pDC, const CRect & rc)
{
	CSingleLock lock(&m_secData, TRUE);

	int w = m_image.GetWidth();
	int h = m_image.GetHeight();

	if (w * h == 0)
		return;

	CPen penR(PS_SOLID, 1, RGB(0, 255, 0));
	CPen penT(PS_SOLID, 1, RGB(255, 255, 255));

	// Initializes a CFont object with the specified characteristics. 
	CFont font;
	VERIFY(font.CreateFont(
		18,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Batang")));                 // lpszFacename

	CFont * oldFont = pDC->SelectObject(&font);
	CPen * oldPen = pDC->SelectObject(&penR);
	pDC->SelectObject(GetStockObject(NULL_BRUSH));

	if (m_faeEyeData.bFace)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&penR);

		CRect rcFace(rc.left + m_faeEyeData.bound.left * rc.Width() / w, rc.top + m_faeEyeData.bound.top * rc.Height() / h,
			rc.left + m_faeEyeData.bound.right * rc.Width() / w, rc.top + m_faeEyeData.bound.bottom * rc.Height() / h);

		pDC->Rectangle(rcFace);

		pDC->SelectObject(oldFont);
		pDC->SetTextColor(RGB(0, 255, 0));

		CString strFPS;
		strFPS.Format(_T("%.2f %%"), m_fConcentration * 100.f);

		CString strDesc = _T("");
		if (m_nEyeWink == 1)
			strDesc.Format(_T("Eye : Open"));
		else if (m_nEyeWink == 0)
			strDesc.Format(_T("Eye : Close"));

		CSize sizeText1 = pDC->GetTextExtent(strFPS);
		CSize sizeText2 = pDC->GetTextExtent(strDesc);

		pDC->TextOut(int(rcFace.left + (rcFace.right - rcFace.left - sizeText2.cx) / 2.f + 0.5f),
			rcFace.bottom + 5, strDesc);

		pDC->TextOut(int(rcFace.left + (rcFace.right - rcFace.left - sizeText1.cx) / 2.f + 0.5f),
			rcFace.top - 20, strFPS);

		pDC->SelectObject(oldPen);
	}
}

void Concentration::updateImageSize()
{

}

void Concentration::initialize()
{
	clear_face_eye_data(&m_faeEyeData);
	m_nEyeDatas.clear();
	m_nEyeWink = -1;
	m_nEyeCount = 0;
	m_nEyeTempCount = 0;
	m_fConcentration = 0.f;
}

void Concentration::clear_face_eye_data(FaceEyeData * data)
{
	memset(data->land, 0, sizeof(KipFaceLandmark) * KipFacelandmarkCount);
	data->bFace = FALSE;
}