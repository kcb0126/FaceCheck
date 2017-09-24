#pragma once
/**************************************************************************\
*
* Copyright (c) 2010-2012, Kulak Image Processing Team, RIC.  All Rights Reserved.
*
* Module Name:
*
*   KipFaceDetector.h
*
* Abstract:
*
*   Kip face detector APIs.
*
\**************************************************************************/
#ifndef _KIPFACEDETECTOR_H
#define _KIPFACEDETECTOR_H

#include "KipFaceDefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

	//--------------------------------------------------------------------------
	// Create and destroy a face detector engine
	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	// Create face detector engine and load database.
	// Return Values :
	//		if succesfully create the face engine, return the handle to the engine, otherwise return 0
	// Require database files :
	//		***.db
	KipEngineHandle	KipFD_Create(char* pszLicenseID, char* pszLicenseKey);
	void			KipFD_Destroy(KipEngineHandle hKipEngine);

	//--------------------------------------------------------------------------
	// detect face on the image.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face detector engine from a previous call to the KipFD_Create function.
	//		pImageInfo :
	//			[in] A pointer to the KipImageInfo struct will detect face.
	// Return Values :
	//		Returns the count of the face detected if detect successfully or a negative value(-1) otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	int				KipFD_Detect(KipEngineHandle hKipEngine, const KipImageInfo * pImageInfo);

	//--------------------------------------------------------------------------
	// Get face landmarks on the image predetected face from a previoius call to the KipFD_Detect.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face detector engine from a previous call to the KipFD_Create function.
	//		iFace :
	//			[i] A index of face to receive landmark. The index number must is between 0 to face count - 1,
	//				the face count is return value from a previous call to the KipFD_Detect function.
	//		ppFaceLandmark :
	//			[out] A pointer to the KipFacelandmark point that receive a landmark of face indexed to iFace.
	//				 A caller must delete *ppFaceLandmark array with KipFD_FreeLandmarks function.
	//			
	// Return Values :
	//		Returns the count of the landmark allocated and copied to ppFaceLandmark if successfully or a negative value(-1) otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	int				KipFD_GetLandmarks(KipEngineHandle hKipEngine, int iFace, KipFaceLandmark ** ppFaceLandmark);

	//--------------------------------------------------------------------------
	// Get face feature on the image predetected face from a previoius call to the KipFD_Detect.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face detector engine from a previous call to the KipFD_Create function.
	//		pImageInfo :
	//			[in] A pointer to the KipImageInfo struct prepassed to a previous cal to the KipFD_Detect.
	//		iFace :
	//			[i] A index of face to receive landmark. The index number must is between 0 to face count - 1,
	//				the face count is return value from a previous call to the KipFD_Detect function.
	//		pFaceFeature :
	//			[out] A pointer to the KipFaceFeature struct that receive a image and landmarks of face indexed to iFace.
	//				 A caller must delete pFaceFeature with KipFD_FreeFeature.
	// Return Values :
	//		Returns 0 if successfully or a negative value(-1) otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	int				KipFD_GetFeature(KipEngineHandle hKipEngine, const KipImageInfo * pImageInfo, int iFace, KipFaceFeature * pFaceFeature);

	//--------------------------------------------------------------------------
	// Save a thumbnail about predetected face from a previoius call to the KipFD_Detect.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face detector engine from a previous call to the KipFD_Create function.
	//		pImageInfo :
	//			[in] A pointer to the KipImageInfo struct prepassed to a previous cal to the KipFD_Detect.
	//		iFace :
	//			[i] A index of face to be saved. The index number must is between 0 to face count - 1,
	//				the face count is return value from a previous call to the KipFD_Detect function.
	//		pwszFileName :
	//			[in] Pointer to a wide-character null-terminated string containing the file name.
	// Return Values :
	//		Returns 0 if successfully or a negative value(-1) otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	int				KipFD_SaveFaceThumbnail(KipEngineHandle hKipEngine, const KipImageInfo * pImageInfo, int iFace, LPCWSTR pwszFileName);

	//--------------------------------------------------------------------------
	// Export a feature to file.
	// Parameters :
	//		pFaceFeature :
	//			[in] Pointer to a KipFaceFeature to be exported.
	//		pwszFileName :
	//			[in] Pointer to a wide-character null-terminated string containing the file name.
	// Return Values :
	//		Returns 0 if successfully or a negative value(-1) otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	int				KipFD_ExportFeature(KipFaceFeature *pFaceFeature, LPCWSTR pwszFileName);

	//--------------------------------------------------------------------------
	// Import a feature from file.
	// Parameters :
	//		pFaceFeature :
	//			[out] Pointer to the KipFaceFeature imported.
	//		pwszFileName :
	//			[in] Pointer to a wide-character null-terminated string containing the file name.
	// Return Values :
	//		Returns 0 if successfully or a negative value(-1) otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	int				KipFD_ImportFeature(KipFaceFeature * pFaceFeature, LPCWSTR pwszFileName);

	//--------------------------------------------------------------------------
	// Free face landmarks from a previous call to the KipFD_GetLandmarks.
	// Parameters :
	//		pFaceLandmark :
	//			[in] A pointer to the KipFacelandmark point from a previous call to the KipFD_GetLandmarks.
	// Return Values :
	//		Returns KipResultSuccess if successfully or a KipResultError otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	KipResultCode	KipFD_FreeLandmarks(KipFaceLandmark * pFaceLandmark);

	//--------------------------------------------------------------------------
	// Free face feature from a previous call to the KipFD_GetFeature.
	// Parameters :
	//		pFaceFeature :
	//			[in] A pointer to the KipFaceFeature point from a previous call to the KipFD_GetFeature.
	// Return Values :
	//		Returns KipResultSuccess if successfully or a KipResultError otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	KipResultCode	KipFD_FreeFeature(KipFaceFeature * pFaceFeature);

	//--------------------------------------------------------------------------
	// retrieves the calling engine's last-error code value.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face detector engine from a previous call to the KipFD_Create function.
	//		errorMsg :
	//			[out] Pointer to a buffer that receives a null-terminated string that specifies the error info of the engine. 
	//				If the length of the error info exceeds the size that the nSize parameter specifies, the function succeeds, and the string is truncated to nSize characters and cannot be null terminated.
	//		nSize 
	//			[in] Size of the errorMsg buffer, in chars. 
	//	Return Values
	//		The return value is the calling engine's last-error code value. 
	KipResultCode	KipFD_GetLastError(KipEngineHandle hKipEngine, char * errorMsg = 0, int nSize = 0);

	//--------------------------------------------------------------------------
	// Cluster faces by their recogniton-information.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face classifier engine from a previous call to the KipFD_Create function.
	//		lppRecogInfoArr :
	//			[in] Array of pointers to recog-info.
	//		nFaceNums :
	//			[in] Size of above array.
	//		pnClusterIDArr :
	//			[out] Array of pointers to cluster ID. Cluster ID must be initialized -1, 
	//				Size of array is equal that of <lppRecogInfoArr>
	//		pnRealClusterNums :
	//			[out] Pointer to the number of clusters.
	//		fltThreshold :
	//			[in] Threshod for clustering. Recommend {6.0 < Threshold < 9.5}, Default value is 8.3
	//		nMaxClusterNums :
	//			[in] Max size of cluter.
	// Return Values :
	//		Returns KipResultSuccess if successfully or a KipResultError otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	KipResultCode	KipFC_CreateClusters(KipEngineHandle hKipEngine, void** lppRecogInfoArr, int nFaceNums, int* pnClusterIDArr,
										int* pnRealClusterNums, float fltThreshold = 0.83f, int nMaxClusterNums = INT_MAX);

	//--------------------------------------------------------------------------
	// Compare a face to another face, or any group.
	// Parameters :
	//		hKipEngine : 
	//			[in] Handle to the face classifier engine from a previous call to the KipFD_Create function.
	//		lppRecogInfoArr :
	//			[in] Array of pointers to recog-info. First element is a point to any face, remainders are pointers to faces to be compared
	//		nFaceNums :
	//			[in] Size of above array. must be > 1.
	//		pfltSimilarity :
	//			[out] Similarity between face and face-group,
	// Return Values :
	//		Returns KipResultSuccess if successfully or a KipResultError otherwise.
	//		To get extended error information, call KipFD_GetLastError.
	KipResultCode	KipFC_CompareCluster(KipEngineHandle hKipEngine, void** lppRecogInfoArr, 
													int nFaceNums, float *pfltSimiarity);

	//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif // !_KIPFACEDETECTOR_H