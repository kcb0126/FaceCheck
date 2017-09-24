#pragma once
/**************************************************************************\
*
* Copyright (c) 2013-2014, Kulak Image Processing Team, RIC.  All Rights Reserved.
*
* Module Name:
*
*   KipGestureRecognition.h
*
* Abstract:
*
*   Kip Gesture Recognition APIs.
*
\**************************************************************************/
#ifdef KIPGESTURERECOGNITION_EXPORTS
#define KIPGESTURERECOGNITION_API __declspec(dllexport)
#else
#define KIPGESTURERECOGNITION_API __declspec(dllimport)
#endif

#include "KipTypes.h"

//--------------------------------------------------------------------------
// Create and destroy a gesture recognition engine
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Create gesture recognition engine and load database.
// Return Values :
//		if succesfully create the gesture recognition engine, return the handle to the engine, otherwise return NULL
// Require database files :
//		gtclass.db
KIPGESTURERECOGNITION_API KipEngineHandle	KipGT_Create();
KIPGESTURERECOGNITION_API void				KipGT_Destroy(KipEngineHandle hKipEngine);

//--------------------------------------------------------------------------
// Process gesture recognition.
// Parameters :
//		hKipEngine : 
//			[in] Handle to the gesture recognition engine from a previous call to the KipGT_Create function.
//		pImageInfo :
//			[in] A pointer to the KipImageInfo struct that load sequence frame.
//		pRL :
//			[out] If right hand, 0. else if left hand, 1, otherwise -1
//		pPose :
//			[out] 0 - gai, 1 - bo, otherwise -1.
//		pMotion :
//			[out] 0 - no hand, 1 - during moving, 2 - [L->R], 3 - [R->L].
// Return Values :
//		Returns the count of the face detected if detect successfully or a negative value(-1) otherwise.
//		To get extended error information, call KipFD_GetLastError.
KIPGESTURERECOGNITION_API KipResultCode		KipGT_Process(KipEngineHandle hKipEngine,
														  const KipImageInfo *pImageInfo,
														  int *pRL,
														  int *pPose,
														  int *pMotion);

//--------------------------------------------------------------------------
// Process gesture-mouse.
// Parameters :
//		hKipEngine : 
//			[in] Handle to the gesture recognition engine from a previous call to the KipGT_Create function.
//		pImageInfo :
//			[in] A pointer to the KipImageInfo struct that load sequence frame.
//		pState :
//			[out] 
//		pWorkRect :
//			[out] 
//		pPoint :
//			[out] 
// Return Values :
//		Returns the count of the face detected if detect successfully or a negative value(-1) otherwise.
//		To get extended error information, call KipFD_GetLastError.
KIPGESTURERECOGNITION_API KipResultCode		KipGT_Process2(KipEngineHandle hKipEngine,
														   const KipImageInfo *pImageInfo,
														   int *pState, 
														   RECT *pWorkRect,
														   POINT *pPoint);