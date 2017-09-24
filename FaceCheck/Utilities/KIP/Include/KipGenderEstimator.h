#pragma once
/**************************************************************************\
*
* Copyright (c) 2010-2012, Kulak Image Processing Team, RIC.  All Rights Reserved.
*
* Module Name:
*
*   KipGenderEstimator.h
*
* Abstract:
*
*   Kip gender estimator APIs.
*
\**************************************************************************/
#ifndef _KIPGENDERESTIMATOR_H
#define _KIPGENDERESTIMATOR_H

#include "KipFaceDefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------
// Create and destroy a gender estimator engine
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Create gender estimator engine and load database.
// Return Values :
//		if succesfully create the gender engine, return the handle to the engine, otherwise return 0
// Require database files :
//		Threshold_SVM
// Require dll files :
//		cximagecrtu.dll

KipEngineHandle	KipGE_Create(char* pszLicenseID, char* pszLicenseKey);
void			KipGE_Destroy(KipEngineHandle hKipEngine);

//--------------------------------------------------------------------------
// estimate gender with face image.
// Parameters :
//		hKipEngine : 
//			[in] Handle to the gender estimator engine from a previous call to the KipGE_Create function.
//		kipFaceFeature :
//			[in] A pointer to the face feature will estimate gender.
// Return Values :
//		Returns percent of male if estimated gender successfull or a negetive value(-1) otherwise.
//		If the gender of the face is fully male, return 100. if the gender of the face is fully female, return 100, oterwise return 0 ~ 100
//		To get extended error information, call KipGE_GetLastError.
int				KipGE_Estimate(KipEngineHandle hKipEngine, const KipFaceFeature * kipFaceFeature);
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// retrieves the calling engine's last-error code value.
// Parameters :
//		hKipEngine : 
//			[in] Handle to the gender estimator engine from a previous call to the KipGE_Create function.
//		errorMsg :
//			[out] Pointer to a buffer that receives a null-terminated string that specifies the error info of the engine. 
//				If the length of the error info exceeds the size that the nSize parameter specifies, the function succeeds, and the string is truncated to nSize characters and cannot be null terminated.
//		nSize 
//			[in] Size of the errorMsg buffer, in chars. 
//	Return Values
//		The return value is the calling engine's last-error code value. 
KipResultCode	KipGE_GetLastError(KipEngineHandle hKipEngine, char * errorMsg = 0, int nSize = 0);
//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif // !_KIPGENDERESTIMATOR_H