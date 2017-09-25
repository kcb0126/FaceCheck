/**********************************************************
comment:	calculate positions of Views according to the mode
producer:	RobinHood
date:		2017.02.25
**********************************************************/
#pragma once

#include "myDef.h"

class CCameraLayout
{
public:
	CCameraLayout(void);
	~CCameraLayout(void);

public:
	CRect	rc_cameraViews[MAX_CAMERA_NUM];
	int		m_nSpaceWidth;
	int		m_nViewWidth;		//width of each view
	int		m_nViewHeight;		//height of each view
public:
	void CalculatePos(int arg_nWidth, int arg_nHeight, int arg_nMode);
	int	 GetCameraNum(int arg_nMode);
};

