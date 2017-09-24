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
*   Kip eye wink APIs.
*
\**************************************************************************/
#ifndef _KIPEYEWINK_H
#define _KIPEYEWINK_H
#include "KipTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

	//--------------------------------------------------------------------------
	// Create and destroy a eye wink engine
	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	// Create eye wink engine and load database.
	// Return Values :
	//		if succesfully create the eyewink engine, return the handle to the engine, otherwise return 0
	// Require database files :
	//		eyewink.svm
	// Require dll files :
	//		cximagecrtu.dll

	KipEngineHandle	KipEW_Create(char* pszLicenseID, char* pszLicenseKey);
	void			KipEW_Destroy(KipEngineHandle hKipEngine);

	//--------------------------------------------------------------------------
	// estimate eye wink with eye local image.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the eyewink engine from a previous call to the KipEW_Create function.
	//		kipEyeImage:
	//			[in] A pointer to the image info contains eye local image.
	// Return Values :
	//		Returns percent of eyewink if estimated successfull or a negetive value(-1) otherwise.
	//		If the eye is fully closed, return 100. if the eye is fully open, return 0, oterwise return 0 ~ 100
	//		To get extended error information, call KipEW_GetLastError.
	int				KipEW_Estimate(KipEngineHandle hKipEngine, const KipImageInfo * kipEyeImage);

	//--------------------------------------------------------------------------
	// retrieves the calling engine's last-error code value.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the eye wink engine from a previous call to the KipEW_Create function.
	//		errorMsg :
	//			[out] Pointer to a buffer that receives a null-terminated string that specifies the error info of the engine. 
	//				If the length of the error info exceeds the size that the nSize parameter specifies, the function succeeds, and the string is truncated to nSize characters and cannot be null terminated.
	//		nSize 
	//			[in] Size of the errorMsg buffer, in chars. 
	//	Return Values
	//		The return value is the calling engine's last-error code value. 
	KipResultCode	KipEW_GetLastError(KipEngineHandle hKipEngine, char * errorMsg = 0, int nSize = 0);
//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif //_KIPEYEWINK_H