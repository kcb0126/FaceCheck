#pragma once
/**************************************************************************\
*
* Copyright (c) 2010-2012, Kulak Image Processing Team, RIC.  All Rights Reserved.
*
* Module Name:
*
*   KipAgeEstimator.h
*
* Abstract:
*
*   Kip age estimator APIs.
*
\**************************************************************************/
#ifndef _KIPAGEESTIMATOR_H
#define _KIPAGEESTIMATOR_H

#include "KipFaceDefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------
// Create and destroy a age estimator engine
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Create age estimator engine and load database.
// Return Values :
//		if succesfully create the age engine, return the handle to the engine, otherwise return 0
// Require database files :
//		male.aedat, female.aedat
// Require dll files :
//		cximagecrtu.dll, cv100.dll, cxcore100.dll

KipEngineHandle	KipAE_Create(char* pszLicenseID, char* pszLicenseKey);
void			KipAE_Destroy(KipEngineHandle hKipEngine);

//--------------------------------------------------------------------------
// estimate age with face image.
// Parameters :
//		hKipEngine : 
//			[in] Handle to the age estimator engine from a previous call to the KipGE_Create function.
//		kipFaceFeature :
//			[in] A pointer to the face feature will estimate age.
//		nGender :
//			[in] A int value specified gender of the face. if the face is fully male, 100, is fully female, 0, is unknown, -1.
//					default value is -1 specified unknown gender.
//				if nGender is -1, age estimator engine will estimate gender of the face itself.
// Return Values :
//		Returns age estimated of the face if estimated age successfull or a negetive value(-1) otherwise.
//		To get extended error information, call KipGE_GetLastError.
int				KipAE_Estimate(KipEngineHandle hKipEngine, const KipFaceFeature * kipFaceFeature, int nGender = -1);
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// retrieves the calling engine's last-error code value.
// Parameters :
//		hKipEngine : 
//			[in] Handle to the age estimator engine from a previous call to the KipAE_Create function.
//		errorMsg :
//			[out] Pointer to a buffer that receives a null-terminated string that specifies the error info of the engine. 
//				If the length of the error info exceeds the size that the nSize parameter specifies, the function succeeds, and the string is truncated to nSize characters and cannot be null terminated.
//		nSize 
//			[in] Size of the errorMsg buffer, in chars. 
//	Return Values
//		The return value is the calling engine's last-error code value. 
KipResultCode	KipAE_GetLastError(KipEngineHandle hKipEngine, char * errorMsg = 0, int nSize = 0);
//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif // !_KIPAGEESTIMATOR_H