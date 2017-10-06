/************************************************************************/
/*
Comment:	Declare global functions and variables.
Producer:	RobinHood
Date:		2017.02.23
*/
/************************************************************************/

#include "resource.h"		// main symbols

#include "myDef.h"
//#include "FaceCheckDlg.h"
#include "EmbeddedMySQL.h"

#include "MonitorHistory.h"
#include "DlgOfWarning.h"

/*--#include "MainFrm.h"

#include "FormOfMonitorHistory.h"
#include "PageOfPersonManage.h"
#include "PageOfPersonHistory.h"
#include "PageOfUserManage.h"
#include "PageOfUserHistory.h"
#include "FormOfMonitor.h"
#include "DlgOfWarning.h"

#include "CameraViewContainer.h"
--*/
//declare global variables
//extern CFaceCheckDlg*	g_pMainDlg;
extern CEmbeddedMySQL*	g_pDBManager;
extern CString			g_strUsername;
extern int				g_nUserID;
extern CString			g_strPlace;
extern int				g_nMaxMugIndex;		//for binaryDatabase update
extern HANDLE			g_hMonitorMutex;

extern CMonitorHistory* g_pMonitorHistory;
extern CDlgOfWarning* g_pWarningDialog;

extern UINT DoInsert(void *pData);


/*--extern CMainFrame* g_pMainFrame;

extern CFormOfMonitorHistory* g_pMonitorHistoryForm;
extern CPageOfPersonManage* g_pPersonManageDialog;
extern CPageOfPersonHistory* g_pPersonHistoryDialog;
extern CPageOfUserManage* g_pUserManageDialog;
extern CPageOfUserHistory* g_pUserHistoryDialog;

extern CCameraViewContainer* g_pMainCameraViewContainer;

extern CFormOfMonitor* g_pMonitorForm;
extern CDlgOfWarning* g_pWarningDialog;

extern void AddItemsForMonitorHistory(int nBeginPos, int nCount);
extern void AddItemsForPersonManage(int nBeginPos, int nCount);
extern void AddItemsForPersonHistory(int nBeginPos, int nCount);
extern void AddItemsForUserManage(int nBeginPos, int nCount);
extern void AddItemsForUserHistory(int nBeginPos, int nCount);

extern void OnDblClickForMonitorHistory(NMHDR *pNMHDR, LRESULT *pResult);
extern void OnDblClickForPersonManage(NMHDR *pNMHDR, LRESULT *pResult);
extern void OnDblClickForUserManage(NMHDR *pNMHDR, LRESULT *pResult);

extern UINT DoInsert(void *pData);
--*/