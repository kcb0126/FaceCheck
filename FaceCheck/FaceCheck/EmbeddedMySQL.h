#pragma once

#include <WinSock.h>
//#include "../../shared/GSDBTypes.h"
#include "mysql.h"
#include "myDef.h"
#include "PersonDB.h"
#include "types.h"

extern CString			g_strUsername;
extern int				g_nUserID;
extern int				g_nMaxMugIndex;
extern CString			g_strPlace;

using namespace KIP;

class CEmbeddedMySQL
{
public:
	CEmbeddedMySQL(void);
	~CEmbeddedMySQL(void);
	bool connect_mysql_server(CString strServer, int nPort, CString strDBName, CString strUser, CString strPassword);
	void close_mysql();
	MYSQL_RES * runQuery(const char * szSQL);
	void runQueryWithoutResult(const char * szSQL);
	void freeSQLResult(MYSQL_RES * results);
	MYSQL_ROW	fetch_row(MYSQL_RES * results);
	bool isValid();
	void verifyTable(const char * name);
	void checkTableContainsCamera(const char * name);

	bool ExportDatabase(/*[IN]*/const TCHAR *ptchHost, /*[IN]*/const TCHAR *ptchUserID, /*[IN]*/const TCHAR *ptchPassword,
		/*[IN]*/const TCHAR *ptchDatabaseNameToExport, /*[IN]*/const TCHAR *ptchExportDatabaseFileWithPath);
	bool ImportDatabase(/*[IN]*/const TCHAR *ptchHost, /*[IN]*/const TCHAR *ptchUserID, /*[IN]*/const TCHAR *ptchPassword,
		/*[IN]*/int nPort, /*[IN]*/const TCHAR *ptchDatabaseNameToImport, /*[IN]*/const TCHAR *ptchImportDatabaseFile);



	void SearchForFilePath(/*[IN]*/TCHAR *strStartingDirectoryPath, /*[IN]*/TCHAR *strFileNameToSearchForDirectory, /*[OUT]*/TCHAR *strReturnFileDirectoryPath);
	void WriteVectorInFile(/*[IN]*/vector<TCHAR *> vecSource, /*[IN]*/TCHAR * strFileName);
	int IsConnected(void);
	TCHAR *GetError(void);
	bool Connect(/*[IN]*/const TCHAR *ptchHost, /*[IN]*/const TCHAR *ptchUserID,
		/*[IN]*/const TCHAR *ptchDatabase, /*[IN]*/const TCHAR *ptchPassword);
	void escape(CString &strUnescaped);

	//added by robin /////////////////////////////////////////////////////////
	//
	bool		loadPersonBinaryData();
	bool		reloadPersonBinaryData();

	long		insertPerson(CString strFirstName, CString strLastName, CString strNickName, CString strBirthday, int nGender, CString strInfor);
	void		insertPersonBinaryData(int nID, CPerson& arg_person);
	void		insertPersonSecurityInfo(int nID, int nPlayerLevel, int nSecurityLevel, int nBlocked, int nBlockedType, CString strWhen, CString strWhere, CString strWhy);
	void		insertPersonUpdateLog(int nID, CString strUsername, CString strUseraction, CString strDateTime, CString strPlace, CString strFields);
	void		insertUserHistory(CString strAction, CString strInfo = _T(""));
	void		insertPersonChangeInfo(int nUserId, int nMugIdx, int nAction);
	void		insertUser(CString strUsername, CString strPassword, int nPriv, CString strCreator, CString strPhone);

	CString		getPersonName(int nPersonID);
	CString		getUserName(int nUserId);
	int			getUserPrivilege(int nUserID);
	int			getUserPrivID(CString strPriv);
	CString		getUserPrivText(int priv_id);
	person_info	getPersonInfoWithSecurity(int nID);
	CxImage		getHistoryImage(int nIDX);
	int			getLastMugIndex();
	int			getPersonIdFromIdx(int nIDX);

	void		addComment(int nIDX, CString strcomment);
	void		updateUserId(int nOldId, int nNewId);
	long		updatePerson(int nID, CString strFirstName, CString strLastName, CString strNickName, CString strBirthday, int nGender, CString strInfor);
	void		updatePersonSecurityInfo(int nID, int nPlayerLevel, int nSecurityLevel, int nBlocked, int nBlockedType, CString strWhen, CString strWhere, CString strWhy);
	void		updateUser(CString strUsername, CString strPassword, int nPriv, CString strOldname, CString strPhone);

	void		deletePerson(int nID);
	void		deletePersonBinaryData(int nPersonID, int nIdx);

	int			findPerson(CString strFirstName, CString strLastName);
	BOOL		verifyPasswordAndBlocked(CString strName, CString strPassword);
	//
	//////////////////////////////////////////////////////////////////////////

protected:
	void run_query(const char * sql);
	bool check_table(const char * name);
	void alterDBEngine();
	MYSQL_RES * store_result();
	void		free_result(MYSQL_RES * results);
protected:
	CRITICAL_SECTION	m_secEvent;
	MYSQL * mysql;
	MYSQL mysqlInitial; // Passed to mysql_init.

public:
	int m_nPageCount = 0;
	int m_nCurrentPage = 0;
	int m_nTotalCount = 0;

	const int m_nCapacityOfPage = 20;

	CString m_strLastInsertedTime;
	int m_nLastInsertedView;

	int m_nMaxIDinMonitorHistory;
};
