#pragma once
/**************************************************************************\
*
* Copyright (c) 2010-2012, Kulak Image Processing Team, RIC.  All Rights Reserved.
*
* Module Name:
*
*   KipEyeWink.h
*
* Abstract:
*
*   Kip head position APIs.
*
\**************************************************************************/
#ifndef _KIPHEADPOSITION_H
#define _KIPHEADPOSITION_H
#include "KipFaceDefs.h"

typedef void * KipCameraMatrixHandle;
#ifdef __cplusplus
extern "C"
{
#endif

	//--------------------------------------------------------------------------
	// Create and destroy a head position engine
	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	// Create head position engine and load database.
	// Return Values :
	//		if succesfully create the head position engine, return the handle to the engine, otherwise return 0
	// Require database files :
	//		
	// Require dll files :
	//		

	KipEngineHandle	KipHP_Create(char* pszLicenseID, char* pszLicenseKey);
	void			KipHP_Destroy(KipEngineHandle hKipEngine);

	//--------------------------------------------------------------------------
	// Create and destroy a camera matrix
	//--------------------------------------------------------------------------
	// Parameters :
	//		width :
	//			[in] Camera capture image width
	//		height :
	//			[in] Camera capture image height
	//		horiz_fov_deg
	//			[in] Camera horizontal field of view in degree. default value is 55.
	// Return Values :
	//		if succesfully create the camera matrix, return the handle to the engine, otherwise return 0

	KipCameraMatrixHandle	KipHP_CreateCameraMatrix(int width, int height, int horiz_fov_deg = 55);
	void			KipHP_DestroyCameraMatrix(KipCameraMatrixHandle hKipEngine);

	//--------------------------------------------------------------------------
	// estimate head position and rotation with face feature.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the head position engine from a previous call to the KipHP_Create function.
	//		hKipCameraMatrix:
	//			[in] Handle to the camera matrix from a previous call to the KipHP_CreateCameraMatrix function.
	//		kipFaceLandmark:
	//			[in] A pointer to the face landmarks in original image.
	//		nLandmarkCount:
	//			[in] A count of landmarks in kipfaceLandmark parameter.
	//		KipheadPosition:
	//			[out] A pointer to the head position in original image.
	//	Return Values
	//		The return value is the engine's error code value. 
	KipResultCode				KipHP_Estimate(KipEngineHandle hKipEngine, KipCameraMatrixHandle hKipCameraMatrix, const KipFaceLandmark * kipFaceLandmark, int nLandmarkCount, KipHeadPosition * kipHeadPosition);

	//--------------------------------------------------------------------------
	// retrieves the calling engine's last-error code value.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the head position engine from a previous call to the KipHP_Create function.
	//		errorMsg :
	//			[out] Pointer to a buffer that receives a null-terminated string that specifies the error info of the engine. 
	//				If the length of the error info exceeds the size that the nSize parameter specifies, the function succeeds, and the string is truncated to nSize characters and cannot be null terminated.
	//		nSize 
	//			[in] Size of the errorMsg buffer, in chars. 
	//	Return Values
	//		The return value is the calling engine's last-error code value. 
	KipResultCode	KipHP_GetLastError(KipEngineHandle hKipEngine, char * errorMsg = 0, int nSize = 0);
//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif //_KIPHEADPOSITION_H