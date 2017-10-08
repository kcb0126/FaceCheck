#include "resource.h"		// main symbols

#include "myDef.h"
#include "EmbeddedMySQL.h"

#include "MonitorHistory.h"
#include "DlgOfWarning.h"
#include "PersonManageList.h"
#include "PersonInfo.h"
#include "UserManageList.h"
#include "UserInfo.h"

extern CEmbeddedMySQL*	g_pDBManager;
extern CString			g_strUsername;
extern int				g_nUserID;
extern CString			g_strPlace;
extern int				g_nMaxMugIndex;		//for binaryDatabase update
extern HANDLE			g_hMonitorMutex;

extern CMonitorHistory* g_pMonitorHistory;
extern CDlgOfWarning* g_pWarningDialog;

extern UINT DoInsert(void *pData);

extern CPersonManageList*	g_pPersonManageList;
extern CPersonInfo*			g_pPersonInfo;

extern CUserManageList*		g_pUserManageList;
extern CUserInfo*			g_pUserInfo;

