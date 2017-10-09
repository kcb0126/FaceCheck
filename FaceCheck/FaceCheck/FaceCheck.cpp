
// FaceCheck.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "FaceCheckDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE g_hMonitorMutex;

// CFaceCheckApp

BEGIN_MESSAGE_MAP(CFaceCheckApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFaceCheckApp construction

CString CFaceCheckApp::m_strAppPath;

CFaceCheckApp::CFaceCheckApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CFaceCheckApp object

CFaceCheckApp theApp;


// CFaceCheckApp initialization

BOOL CFaceCheckApp::InitInstance()
{
	g_hMonitorMutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, MONITOR_CLIENT_MUTEX);
	if (g_hMonitorMutex != NULL)
	{
		MessageBox(NULL, _T("The program is already running!"), _T("Information"), MB_OK);
		return FALSE;
	}
	g_hMonitorMutex = CreateMutex(NULL, NULL, MONITOR_CLIENT_MUTEX);

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	TCHAR* pos = _tcsrchr(szPath, _T('\\'));
	pos[1] = 0;
	m_strAppPath = szPath;

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	SetRegistryKey(_T("FaceCheck"));

	//load Setting Values
	CString strServerAddress, strDBName, strUsername, strPassword;
	int nPort;
/*	strServerAddress = AfxGetApp()->GetProfileString(_T("Setting"), _T("Address"), _T("85.214.18.79"));
	nPort = AfxGetApp()->GetProfileInt(_T("Setting"), _T("Port"), 3306);
	strDBName = AfxGetApp()->GetProfileString(_T("Setting"), _T("DBName"), _T("facecheck_db"));
	strUsername = AfxGetApp()->GetProfileString(_T("Setting"), _T("UserName"), _T("facecheck_user"));
	strPassword = AfxGetApp()->GetProfileString(_T("Setting"), _T("Password"), _T("facecheck@123"));
*/
	strServerAddress = AfxGetApp()->GetProfileString(_T("Setting"), _T("Address"), _T("server"));
	nPort = AfxGetApp()->GetProfileInt(_T("Setting"), _T("Port"), 3306);
	strDBName = AfxGetApp()->GetProfileString(_T("Setting"), _T("DBName"), _T("facecheck_db"));
	strUsername = AfxGetApp()->GetProfileString(_T("Setting"), _T("UserName"), _T("super_user"));
	strPassword = AfxGetApp()->GetProfileString(_T("Setting"), _T("Password"), _T("super"));

	g_pDBManager = new CEmbeddedMySQL;
	if (g_pDBManager->connect_mysql_server(strServerAddress, nPort, strDBName, strUsername, strPassword))
	{
		g_pDBManager->loadPersonBinaryData();

		personDB().getThresholdValue(AfxGetApp()->GetProfileInt(_T("FaceOption"), _T("ThresholdLevel"), 3));


	}
	else
	{
		exit(1);
	}
	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization

	CFaceCheckDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString CFaceCheckApp::GetAppSubFilePath(LPCTSTR lpszFileName)
{
	return m_strAppPath + lpszFileName;
}