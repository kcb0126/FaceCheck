#include "stdafx.h"
#include "CameraLayout.h"


CCameraLayout::CCameraLayout(void)
{
	m_nSpaceWidth = 1;
	for (int i = 0; i < MAX_CAMERA_NUM; i++)
		rc_cameraViews[i].SetRect(0, 0, 0, 0);
}


CCameraLayout::~CCameraLayout(void)
{
}


void CCameraLayout::CalculatePos(int arg_nWidth, int arg_nHeight, int arg_nMode)
{
	//	get Horizontal and vertical camera number:수직, 수평카메라개수를 얻는다
	int nHoriCamNum, nVertCamNum;

	switch (arg_nMode)
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

	// get width and height of each view:매 보기창문의 너비, 높이를 얻는다
	m_nViewWidth = int(arg_nWidth / (float)nHoriCamNum);
	m_nViewHeight = int(arg_nHeight / (float)nVertCamNum);

	// set rect of each view:매 보기창문의 rect를 설정한다
	int x, y, w, h;
	for (int i = 0; i < nVertCamNum; i++)
	{
		for (int j = 0; j < nHoriCamNum; j++)
		{
			x = m_nViewWidth * j + m_nSpaceWidth;
			y = m_nViewHeight * i + m_nSpaceWidth;
			w = m_nViewWidth - 2 * m_nSpaceWidth;
			h = m_nViewHeight - 2 * m_nSpaceWidth;

			rc_cameraViews[i * nHoriCamNum + j].SetRect(x, y, x + w, y + h);
		}
	}
}

int CCameraLayout::GetCameraNum(int arg_nMode)
{
	int camera_channel = 0;
	switch (arg_nMode)
	{
	case 0:
		camera_channel = 1;
		break;
	case 1:
		camera_channel = 4;
		break;
	case 2:
		camera_channel = 6;
		break;
	case 3:
		camera_channel = 6;
		break;
	case 4:
		camera_channel = 9;
		break;
	case 5:
		camera_channel = 16;
		break;
	default:
		camera_channel = 4;
		break;
	}

	return camera_channel;
}
