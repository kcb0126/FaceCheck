
// FaceCheck.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "myGlobal.h"

// CFaceCheckApp:
// See FaceCheck.cpp for the implementation of this class
//

class CFaceCheckApp : public CWinApp
{
public:
	CFaceCheckApp();

	ULONG_PTR m_gdiplusToken;

public:
	CPersonDB m_PersonDB;

	static CString m_strAppPath;
	static CString GetAppSubFilePath(LPCTSTR lpszFileName);

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFaceCheckApp theApp;