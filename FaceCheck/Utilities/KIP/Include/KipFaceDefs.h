#pragma once
/**************************************************************************\
*
* Copyright (c) 2010-2012, Kulak Image Processing Team, RIC.  All Rights Reserved.
*
* Module Name:
*
*   KipFaceDefs.h
*
* Abstract:
*
*   Kip face definement structs.
*
\**************************************************************************/
#ifndef _KIPFACEDEFSTYPES_H
#define _KIPFACEDEFSTYPES_H

#include "KipTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------
// face feature enumeration
//--------------------------------------------------------------------------
enum KipFaceLandmarkId
{
	KipFaceLandmarkFaceCornerTopLeft = 0,									//------------------------------//
	KipFaceLandmarkFaceCornerTopRight = 1,									//								//
	KipFaceLandmarkFaceCornerBottomRight = 2,								//	0 --------------------- 1	//	
	KipFaceLandmarkFaceCornerBottomLeft = 3,								//	|  22-23-24    25-26-27	|	//
	KipFaceLandmarkEyeLeftOuter = 4,										//	|    ----        ----   |	//
	KipFaceLandmarkEyeLeftInner = 5,										//	|   4 12 5  16  6 14 7  |	//
	KipFaceLandmarkEyeRightInner = 6,										//	|	 -13-        -15-   |	//
	KipFaceLandmarkEyeRightOuter = 7,										//	|           17          |	//
	KipFaceLandmarkMouthLeft = 8,											//	|         10  11        |	//
	KipFaceLandmarkMouthRight = 9,											//	|           18          |	//
	KipFaceLandmarkNoseLeft = 10,											//	|        ---19---       |	//
	KipFaceLandmarkNoseRight = 11,											//	|       8   20   9      |	//
	KipFaceLandmarkEyeLeftPupil = 12,										//	|        ---21---       |	//
	KipFaceLandmarkEyeLeftBottom = 13,										//	|                       |	//
	KipFaceLandmarkEyeRightPupil = 14,										//	3 --------------------- 2	//
	KipFaceLandmarkEyeRightBottom = 15,										//______________________________//
	KipFaceLandmarkBetweenEyes = 16,
	KipFaceLandmarkNoseTip = 17,
	KipFaceLandmarkNoseBottom = 18,
	KipFaceLandmarkMouthTop = 19,
	KipFaceLandmarkMouthCenter = 20,
	KipFaceLandmarkMouthBottom = 21,
	KipFaceLandmarkEyebrowLeftOuter = 22,
	KipFaceLandmarkEyebrowLeftCenter = 23,
	KipFaceLandmarkEyebrowLeftInner = 24,
	KipFaceLandmarkEyebrowRightInner = 25,
	KipFaceLandmarkEyebrowRightCenter = 26,
	KipFaceLandmarkEyebrowRightOuter = 27,
	KipFacelandmarkCount
};

//--------------------------------------------------------------------------
// face feature struct
//--------------------------------------------------------------------------
typedef struct KipFaceLandmark
{
	KipFaceLandmarkId	id;
	KipCoord2f			pos;
} KipFaceLandmark;

typedef struct KipFaceFeature
{
	KipImageInfo		faceImage;
	KipFaceLandmark *	landmarks;
	int					numLandmarks;
	float				anglePan;
	void*				recogInfo;
	float				confidence;
} KipFaceFeature;

typedef struct KipHeadPosition
{
	KipCoord3f		position;
	KipCoord3f		rotation;
	float			spacePupils;
} KipHeadPosition;
#ifdef __cplusplus
}
#endif
#endif // !_KIPFACEDEFSTYPES_H