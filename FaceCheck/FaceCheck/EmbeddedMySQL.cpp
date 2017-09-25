#include "StdAfx.h"
#include "EmbeddedMySQL.h"
#include "FaceCheck.h"
#include "myDef.h"
#include "ExecutablePathInfo.h"
#include <ShlObj.h>
//--#include "DlgOfSetServer.h"

CString			g_strUsername;
int				g_nUserID;
int				g_nMaxMugIndex;
CString			g_strPlace;
CEmbeddedMySQL*	g_pDBManager;

CEmbeddedMySQL::CEmbeddedMySQL(void)
{
	mysql = NULL;
	InitializeCriticalSectionAndSpinCount(&m_secEvent, 0x80000400);
	//test code: connect_mysql_server(_T("127.0.0.1"), 3306, _T("FaceCheck_DB"), _T("root"), _T(""));
}

CEmbeddedMySQL::~CEmbeddedMySQL(void)
{
	close_mysql();
	DeleteCriticalSection(&m_secEvent);
}

bool CEmbeddedMySQL::connect_mysql_server(CString strServer, int nPort, CString strDBName, CString strUser, CString strPassword)
{/*--
	close_mysql();

	mysql = mysql_init(NULL);

	if (mysql == NULL)
	{
		MessageBox(NULL, _T("mysql_init fault"), _T("MySql error"), MB_OK);
		return false;
	}

	if (mysql_real_connect(mysql, CW2A(strServer.GetBuffer()), CW2A(strUser.GetBuffer()), CW2A(strPassword.GetBuffer()), "information_schema",
		nPort, NULL, 0) == NULL)
	{
		int nResponse = MessageBox(NULL, _T("Server connection failed. Do you want to set connection manually?"), _T("Connection error"), MB_YESNO);
		if (nResponse == 6)			//Clicked "Yes"
		{
			CDlgOfSetServer dlg;
			dlg.m_strAddress = strServer;
			dlg.m_nPort = nPort;
			dlg.m_strUsername = strUser;
			dlg.m_strPassword = strPassword;
			dlg.m_strDBName = strDBName;
			//dlg.UpdateData(false);			//Don't need. I will do it in OnInitDialog();
			if (dlg.DoModal() == IDCANCEL) {
				mysql = NULL;
				return false;
			}
			//dlg.UpdateData(TRUE);		//Don't need. but i don't know the reason.
			strServer = dlg.m_strAddress;
			strUser = dlg.m_strUsername;
			strPassword = dlg.m_strPassword;
			nPort = dlg.m_nPort;
			strDBName = dlg.m_strDBName;

			AfxGetApp()->WriteProfileString(_T("Setting"), _T("Address"), strServer);
			AfxGetApp()->WriteProfileInt(_T("Setting"), _T("Port"), nPort);
			AfxGetApp()->WriteProfileString(_T("Setting"), _T("UserName"), strUser);
			AfxGetApp()->WriteProfileString(_T("Setting"), _T("Password"), strPassword);
			AfxGetApp()->WriteProfileString(_T("Setting"), _T("DBName"), strDBName);

			return connect_mysql_server(strServer, nPort, strDBName, strUser, strPassword);
		}
		mysql = NULL;
		return false;
	}
	// create facecheck_db DataBase
	run_query("CREATE DATABASE IF NOT EXISTS FaceCheck_DB");

	close_mysql();
	mysql = mysql_init(NULL);

	if (mysql == NULL)
	{
		MessageBox(NULL, _T("mysql_init fault"), _T("MySql error"), MB_OK);
		return false;
	}

	if (mysql_real_connect(mysql, CW2A(strServer.GetBuffer()), CW2A(strUser.GetBuffer()), CW2A(strPassword.GetBuffer()), CW2A(strDBName.GetBuffer()),
		nPort, NULL, 0) == NULL)
	{
		MessageBox(NULL, _T("Error occured in connecting FaceCheck_DB."), _T("Connection error"), MB_OK);
		mysql = NULL;
		return false;
	}
	mysql->reconnect = 1;
	//MessageBox(NULL, _T("mysql_real_connect succeed"), _T("MySql "), MB_OK);

	MYSQL_RES* resultTemp = runQuery(CW2A(L"SELECT MAX(IDX) from monitor_history"));
	MYSQL_ROW recordTemp = g_pDBManager->fetch_row(resultTemp);
	int nIdx = recordTemp[0] == NULL ? 0 : atoi(recordTemp[0]);
	m_nMaxIDinMonitorHistory = nIdx;
--*/
	return true;
}

void CEmbeddedMySQL::close_mysql()
{
	if (mysql == NULL)
	{
		return;
	}

	mysql_close(mysql);
	//comment by Robin mysql_server_end();
	mysql = NULL;
}

bool CEmbeddedMySQL::isValid()
{
	return mysql != NULL;
}

void CEmbeddedMySQL::run_query(const char * sql)
{
	if (isValid() == false || mysql == NULL)
		return;
	mysql_query(mysql, sql);
}

MYSQL_RES * CEmbeddedMySQL::store_result()
{
	if (isValid() == false)
		return NULL;
	return mysql_store_result(mysql);
}

MYSQL_ROW CEmbeddedMySQL::fetch_row(MYSQL_RES * results)
{
	return mysql_fetch_row(results);
}

void		CEmbeddedMySQL::free_result(MYSQL_RES * results)
{
	mysql_free_result(results);
}

bool CEmbeddedMySQL::check_table(const char * name)
{
	if (isValid() == false || name == 0)
		return false;

	bool ret = true;
	char szSQL[0x100];
	sprintf_s(szSQL, "CHECK TABLE %s", name);
	MYSQL_RES * result = runQuery(szSQL);
	if (result == 0)
		return false;
	MYSQL_ROW last_record = 0;
	while (MYSQL_ROW record = fetch_row(result))
	{
		last_record = record;
	}
	freeSQLResult(result);

	if (last_record == 0)
		return false;
	if (_stricmp(last_record[2], "status") != 0 || _stricmp(last_record[3], "OK") != 0)
		ret = false;

	return ret;
}

MYSQL_RES * CEmbeddedMySQL::runQuery(const char * szSQL)
{
	EnterCriticalSection(&m_secEvent);
	run_query(szSQL);
	MYSQL_RES * results = store_result();
	LeaveCriticalSection(&m_secEvent);

	return results;
}

void CEmbeddedMySQL::freeSQLResult(MYSQL_RES * results)
{
	if (results)
		free_result(results);
}

void CEmbeddedMySQL::runQueryWithoutResult(const char * szSQL)
{
	EnterCriticalSection(&m_secEvent);
	run_query(szSQL);
	//	freeSQLResult(store_result());
	LeaveCriticalSection(&m_secEvent);
}

void CEmbeddedMySQL::verifyTable(const char * name)
{
	if (check_table(name))
		return;

	char szSQL[0x100];
	sprintf_s(szSQL, "REPAIR TABLE %s", name);
	runQueryWithoutResult(szSQL);
}

void CEmbeddedMySQL::checkTableContainsCamera(const char * name)
{
	char szSQL[0x100];
	sprintf_s(szSQL, "SHOW TABLES LIKE '%s'", name);
	MYSQL_RES * result = runQuery(szSQL);
	if (result == 0)
		return;

	bool is_table = false;
	while (MYSQL_ROW record = fetch_row(result))
	{
		if (_stricmp(record[0], name) == 0)
		{
			is_table = true;
			break;
		}
	}

	freeSQLResult(result);

	if (is_table == false)
		return;
	// there is the table.
	// check the table contains camera filed.
	sprintf_s(szSQL, "SHOW FIELDS FROM %s LIKE 'camera'", name);

	bool is_camera = false;
	result = runQuery(szSQL);
	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			if (_stricmp(record[0], "camera") == 0)
			{
				is_camera = true;
				break;
			}
		}

		freeSQLResult(result);
	}

	if (is_camera == false)
	{
		// drop the invalid table
		sprintf_s(szSQL, "DROP TABLE %s", name);
		runQueryWithoutResult(szSQL);
	}
}


void CEmbeddedMySQL::alterDBEngine()
{
	// retrieve table status
	MYSQL_RES * result = runQuery("SHOW TABLE STATUS");
	if (result == 0)
		return;

	while (MYSQL_ROW record = fetch_row(result))
	{
		if (_stricmp(record[1], "InnoDB") != 0)
		{
			char szSQL[0x100];
			sprintf_s(szSQL, "ALTER TABLE %s TYPE = INNODB", record[0]);
			runQueryWithoutResult(szSQL);
		}
	}

	freeSQLResult(result);
}

bool CEmbeddedMySQL::loadPersonBinaryData()
{
	CString strQuery;
	CString strQuery2;

	strQuery.Format(_T("SELECT * FROM person_list"));

	MYSQL_RES* result = 0;
	MYSQL_RES* result2 = 0;

	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		personDB().Clear();
		while (MYSQL_ROW record = fetch_row(result))
		{
			CPerson person;

			//Get person's ID
			person.m_nID = atoi(record[0]);
			person.m_strName = CString((record[1])) + _T(" ") + CString(record[2]);

			//Get person's BinaryData with ID
			strQuery2.Format(_T("SELECT * FROM person_binarydata WHERE id = %d"), person.m_nID);
			result2 = runQuery(CW2A(strQuery2.GetBuffer()));

			if (result2)
			{
				while (MYSQL_ROW record2 = fetch_row((result2)))
				{
					CMugshot mugshot;

					mugshot.m_nIDX = atoi(record2[0]);

					mugshot.m_photo.m_nBpp = atoi(record2[3]);
					mugshot.m_photo.m_nEffWidth = atoi(record2[4]);
					mugshot.m_photo.m_nHeight = atoi(record2[5]);
					mugshot.m_photo.m_pbyBuf = new BYTE[mugshot.m_photo.m_nEffWidth * mugshot.m_photo.m_nHeight];
					memcpy(mugshot.m_photo.m_pbyBuf, record2[2], mugshot.m_photo.m_nEffWidth * mugshot.m_photo.m_nHeight);

					int nFeatureLen = atoi(record2[7]);
					mugshot.m_pdwFeature = new DWORD[nFeatureLen / 4];
					memcpy(mugshot.m_pdwFeature, record2[6], nFeatureLen);

					person.Add(mugshot);
				}
				freeSQLResult(result2);

				// add the person to compare db
				personDB().Add(person);
			}
			else
			{
				CString strMsg;
				strMsg.Format(_T("There's no binarydata of the person of ID: %d"), person.m_nID);
				MessageBox(NULL, strMsg, _T("Message"), MB_OK);
			}
		}
		freeSQLResult(result);
	}
	else
	{
		MessageBox(NULL, _T("There's no person in the list"), _T("Message"), MB_OK);
		return false;
	}

	g_nMaxMugIndex = getLastMugIndex();
	return true;
}

bool CEmbeddedMySQL::reloadPersonBinaryData()
{
	int nCurrentMugIdx = getLastMugIndex();

	if (nCurrentMugIdx <= g_nMaxMugIndex)
		return false;

	CString strQuery;
	CString strQuery2;
	MYSQL_RES* result = 0;
	MYSQL_RES* result2 = 0;
	int nAction = -1;
	int nPersonId;
	int nMugId;

	strQuery.Format(_T("SELECT * FROM person_change_info WHERE IDX > %d"), g_nMaxMugIndex);
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			nPersonId = atoi(record[1]);
			nMugId = atoi(record[2]);
			nAction = atoi(record[3]);

			if (nAction == 0)		//if deleted
			{
				if (nMugId != -2)	//if mugshot deleted
					personDB().DeleteMugshot(nPersonId, nMugId);
				else				//if person deleted
					personDB().DeletePerson(nPersonId);
			}
			else if (nAction == 1)	//if added
			{
				strQuery2.Format(_T("SELECT * FROM person_binarydata WHERE IDX = %d"), nMugId);
				result2 = runQuery(CW2A(strQuery2.GetBuffer()));

				if (result2)
				{
					MYSQL_ROW record2 = fetch_row((result2));

					int idx = personDB().IsExist(nPersonId);
					if (idx != -1)	//if person exist
					{
						CMugshot mugshot;

						mugshot.m_nIDX = atoi(record2[0]);

						mugshot.m_photo.m_nBpp = atoi(record2[3]);
						mugshot.m_photo.m_nEffWidth = atoi(record2[4]);
						mugshot.m_photo.m_nHeight = atoi(record2[5]);
						mugshot.m_photo.m_pbyBuf = new BYTE[mugshot.m_photo.m_nEffWidth * mugshot.m_photo.m_nHeight];
						memcpy(mugshot.m_photo.m_pbyBuf, record2[2], mugshot.m_photo.m_nEffWidth * mugshot.m_photo.m_nHeight);

						int nFeatureLen = atoi(record2[7]);
						mugshot.m_pdwFeature = new DWORD[nFeatureLen / 4];
						memcpy(mugshot.m_pdwFeature, record2[6], nFeatureLen);

						personDB()[idx].Add(mugshot);
					}
					else
					{
						CPerson person;
						person.m_nID = nPersonId;
						person.m_strName = getPersonName(nPersonId);

						CMugshot mugshot;
						mugshot.m_nIDX = atoi(record2[0]);

						mugshot.m_photo.m_nBpp = atoi(record2[3]);
						mugshot.m_photo.m_nEffWidth = atoi(record2[4]);
						mugshot.m_photo.m_nHeight = atoi(record2[5]);
						mugshot.m_photo.m_pbyBuf = new BYTE[mugshot.m_photo.m_nEffWidth * mugshot.m_photo.m_nHeight];
						memcpy(mugshot.m_photo.m_pbyBuf, record2[2], mugshot.m_photo.m_nEffWidth * mugshot.m_photo.m_nHeight);

						int nFeatureLen = atoi(record2[7]);
						mugshot.m_pdwFeature = new DWORD[nFeatureLen / 4];
						memcpy(mugshot.m_pdwFeature, record2[6], nFeatureLen);

						person.Add(mugshot);

						personDB().Add(person);
					}

					freeSQLResult(result2);
				}
				else
				{
					CString strMsg;
					strMsg.Format(_T("There's no binarydata of the person of IDX: %d"), nMugId);
					MessageBox(NULL, strMsg, _T("Message"), MB_OK);
				}
			}
		}
		freeSQLResult(result);
	}
	else
	{
		MessageBox(NULL, _T("There's no person in the list"), _T("Message"), MB_OK);
		return false;
	}

	g_nMaxMugIndex = getLastMugIndex();
	return true;
}

int CEmbeddedMySQL::getPersonIdFromIdx(int nIDX)
{
	CString strQuery;

	MYSQL_RES* result = 0;
	strQuery.Format(_T("SELECT id FROM monitor_history WHERE IDX = %d"), nIDX);
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result == 0)
		return NON_EMPLOYEE;

	MYSQL_ROW record = mysql_fetch_row(result);
	int ret = atoi(record[0]);
	freeSQLResult(result);

	return ret;
}

int CEmbeddedMySQL::getLastMugIndex()
{
	CString strQuery;

	MYSQL_RES* result = 0;
	strQuery.Format(_T("SELECT MAX(IDX) FROM person_change_info"));
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result == 0 || result->row_count == 0)
		return 0;

	MYSQL_ROW record = mysql_fetch_row(result);
	if (record == NULL || record[0] == NULL)
		return 0;
	int ret = atoi(record[0]);
	freeSQLResult(result);

	return ret;
}
/*
func:	add a person into person_list table
return value:
record's id: if successful
0:			 if unsuccessful
-1:		     if user refused to insert
*/

void CEmbeddedMySQL::escape(CString &strUnescaped)
{
	strUnescaped.Replace(L"'", L"''");
	//	strUnescaped.Replace(L"%", L"/%");
	//	strUnescaped.Replace(L"_", L"/_");
}

long CEmbeddedMySQL::insertPerson(CString strFirstName, CString strLastName, CString strNickName, CString strBirthday, int nGender, CString strInfo)
{
	CString strQuery;

	escape(strFirstName);
	escape(strLastName);
	escape(strNickName);
	escape(strBirthday);
	escape(strInfo);

	strQuery.Format(_T("SELECT id From person_list WHERE firstname = '%s' AND lastname = '%s'"), strFirstName, strLastName);
	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		if (result->row_count > 0)
		{
			if (MessageBox(NULL, _T("The same name exists! Do you still want to continue?"), _T("Message"), MB_YESNO) == IDNO)
				return -1;
		}
		freeSQLResult(result);
	}

	strQuery.Format(_T("INSERT INTO person_list (id, firstname, lastname, nickname, birthday, gender, information) VALUES (NULL, '%s', '%s', '%s', '%s', %d, '%s')"), strFirstName, strLastName, strNickName, strBirthday, nGender, strInfo);

	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	return (long)(mysql_insert_id(mysql));
}

void CEmbeddedMySQL::insertPersonBinaryData(int nID, CPerson& arg_person)
{
	CString strQuery;

	int nSize = (int)arg_person.m_vecMugshot.size();

	CString csPhoto, csFeature;
	char* szPhoto;
	char* szFeature;
	int nPhotoRealSize, nPhotoSaveSize, nFeatureRealSize, nFeatureSaveSize;

	for (int i = 0; i < nSize; i++)
	{
		if (arg_person.m_vecMugshot[i].m_nIDX != -1)
			continue;

		//change photo binary to string in order to save table
		nPhotoRealSize = arg_person.m_vecMugshot[i].m_photo.m_nEffWidth * REG_IMAGE_H;
		nPhotoSaveSize = nPhotoRealSize * 2 + 3; //+3 = '0','x',...'\0'
		szPhoto = new char[nPhotoSaveSize];
		strcpy(szPhoto, "0x");
		mysql_hex_string(szPhoto + 2, (char *)(arg_person.m_vecMugshot[i].m_photo.m_pbyBuf), nPhotoRealSize);
		csPhoto = szPhoto;

		//change feature binary to string in order to save table
		nFeatureRealSize = arg_person.m_vecMugshot[i].m_pdwFeature[0];
		nFeatureSaveSize = nFeatureRealSize * 2 + 3; //+3 = '0','x',...'\0'
		szFeature = new char[nFeatureSaveSize];
		strcpy(szFeature, "0x");
		mysql_hex_string(szFeature + 2, (char *)(arg_person.m_vecMugshot[i].m_pdwFeature), nFeatureRealSize);
		csFeature = szFeature;

		strQuery.Format(_T("INSERT INTO person_binarydata (id, photo_data, photo_bpp, photo_height, photo_effwidth, feature_data, feature_size) VALUES ( %d, %s, %d, %d, %d, %s, %d)")
			, nID
			, csPhoto
			, arg_person.m_vecMugshot[i].m_photo.m_nBpp
			, REG_IMAGE_H
			, arg_person.m_vecMugshot[i].m_photo.m_nEffWidth
			, csFeature
			, nFeatureRealSize);

		runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
		delete[] szPhoto;
		delete[] szFeature;

		long insertedID = (long)(mysql_insert_id(mysql));
		insertPersonChangeInfo(nID, insertedID, 1);
	}
}

void CEmbeddedMySQL::insertPersonChangeInfo(int nUserId, int nMugIdx, int nAction)
{
	CString strQuery;
	strQuery.Format(_T("INSERT INTO person_change_info (person_id, mug_id, action) VALUES (%d, %d, %d)"), nUserId, nMugIdx, nAction);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
}

/*
func:	add a personSecurityInfo into person_security_info table
*/
void CEmbeddedMySQL::insertPersonSecurityInfo(int nID, int nPlayerLevel, int nSecurityLevel, int nBlocked, int nBlockedType, CString strWhen, CString strWhere, CString strWhy)
{
	CString strQuery;

	escape(strWhen);
	escape(strWhere);
	escape(strWhy);

	strQuery.Format(_T("INSERT INTO person_security_info (id, player_level, security_level, blocked, blocked_type, blocked_when, blocked_where, blocked_why) VALUES (%d, %d, %d, %d, %d, '%s', '%s', '%s')"), nID, nPlayerLevel, nSecurityLevel, nBlocked, nBlockedType, strWhen, strWhere, strWhy);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
	return;
}

/*
func:	add a personUpdateLog into person_updatelog table
*/
void CEmbeddedMySQL::insertPersonUpdateLog(int nID, CString strUsername, CString strUseraction, CString strDateTime, CString strPlace, CString strFields)
{
	CString strQuery;

	escape(strUsername);
	escape(strUseraction);
	escape(strPlace);
	escape(strFields);

	strQuery.Format(_T("INSERT INTO person_updatelog (person_id, user_name, user_action, user_datetime, user_place, user_changedfields) VALUES (%d, '%s', '%s', '%s', '%s', '%s')"), nID, strUsername, strUseraction, strDateTime, strPlace, strFields);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
	return;
}


void CEmbeddedMySQL::insertUser(CString strUsername, CString strPassword, int nPriv, CString strCreator, CString strPhone)
{
	CString strQuery;
	strQuery.Format(_T("INSERT INTO user_list (username, password, privilege_id, creator, created_time, phone) VALUES ('%s', '%s', %d, '%s', '%s', '%s')"), strUsername, strPassword, nPriv, strCreator, CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"), strPhone);
	runQueryWithoutResult(CW2A(strQuery));
	return;
}
/*
func:	add a user history into user_history table
*/
void CEmbeddedMySQL::insertUserHistory(CString strAction, CString strInfo)
{
	CString strQuery;
	escape(strInfo);

	strQuery.Format(_T("INSERT INTO user_history (user_id, taken_action, action_datetime, info) VALUES (%d, '%s', '%s', '%s')"), g_nUserID, strAction, CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"), strInfo);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
	return;
}



CString CEmbeddedMySQL::getPersonName(int nPersonID)
{
	CString strQuery;
	CString strRet;

	strQuery.Format(_T("SELECT firstname, lastname FROM person_list WHERE id = %d"), nPersonID);

	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			strRet = CString(record[0]) + _T(" ") + CString(record[1]);
			break;
		}
		freeSQLResult(result);
	}
	else
		strRet.Format(_T("UnknownID-%d"), nPersonID);

	return strRet;
}

int CEmbeddedMySQL::getUserPrivilege(int nUserID)
{
	CString strQuery;

	strQuery.Format(_T("SELECT privilege_id FROM user_list WHERE id = %d"), nUserID);

	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	int nRet = -1;
	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			nRet = atoi(record[0]);
			break;
		}
		freeSQLResult(result);
	}
	else
		return -1;

	return nRet;
}

CString CEmbeddedMySQL::getUserPrivText(int priv_id)
{
	CString strQuery;

	strQuery.Format(_T("SELECT privilege_type FROM user_privilege_type WHERE id = %d"), priv_id);

	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	CString strRet;

	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			strRet = record[0];
			break;
		}
		freeSQLResult(result);
	}
	else
		return _T("");

	return strRet;
}

int CEmbeddedMySQL::getUserPrivID(CString strPriv)
{
	CString strQuery;

	strQuery.Format(_T("SELECT id FROM user_privilege_type WHERE privileg_type = '%s'"), strPriv);

	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	int nRet = -1;
	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			nRet = atoi(record[0]);
			break;
		}
		freeSQLResult(result);
	}
	else
		return -1;


	return nRet;
}

CString CEmbeddedMySQL::getUserName(int nUserId)
{
	CString strQuery;
	CString strRet;

	strQuery.Format(_T("SELECT username FROM user_list WHERE id = %d"), nUserId);

	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			strRet = record[0];
			break;
		}
		freeSQLResult(result);
	}
	else
		strRet.Format(_T("UnknownID-%d"), nUserId);

	return strRet;
}

person_info	CEmbeddedMySQL::getPersonInfoWithSecurity(int nID)
{
	person_info retInfo;
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM person_list AS t JOIN person_security_info AS tt ON t.id = tt.id AND t.id = %d "), nID);

	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		while (MYSQL_ROW record = fetch_row(result))
		{
			retInfo.m_nID = atoi(record[0]);
			retInfo.m_strFirstname = record[1];
			retInfo.m_strLastname = record[2];
			retInfo.m_strNickname = record[3];
			retInfo.m_strBirthday = record[4];
			retInfo.m_nGender = atoi(record[5]);
			retInfo.m_strInfo = record[6];
			retInfo.m_nPlayerLevel = atoi(record[9]);
			retInfo.m_nSecurityLevel = atoi(record[10]);
			retInfo.m_nBlocked = atoi(record[11]);
			retInfo.m_nBlockedType = atoi(record[12]);
			retInfo.m_strBlockedWhen = record[13];
			retInfo.m_strBlockedWhere = record[14];
			retInfo.m_strBlockedWhy = record[15];
			break;
		}
		freeSQLResult(result);
	}
	return retInfo;
}

CxImage CEmbeddedMySQL::getHistoryImage(int nIDX)
{
	CxImage imgReturn;
	int nbpp, nEffWidth, nHeight;
	CString strQuery;
	MYSQL_RES* result = 0;

	strQuery.Format(_T("SELECT * FROM monitor_history WHERE IDX =  %d"), nIDX);
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		MYSQL_ROW record = fetch_row(result);
		nbpp = atoi(record[5]);
		nEffWidth = atoi(record[6]);
		nHeight = atoi(record[7]);

		BYTE* pbyBuf = new BYTE[nEffWidth * nHeight];
		memcpy(pbyBuf, record[4], nEffWidth * nHeight);

		imgReturn.CreateFromArray(pbyBuf, CUSTOMER_PHOTO_WIDTH, CUSTOMER_PHOTO_HEIGHT, nbpp, nEffWidth, FALSE);

		delete[] pbyBuf;

	}
	g_pDBManager->freeSQLResult(result);
	return imgReturn;
}

BOOL CEmbeddedMySQL::verifyPasswordAndBlocked(CString strName, CString strPassword)
{
	BOOL ret = FALSE;

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM user_list WHERE username  = '%s'"), strName);

	MYSQL_RES * result = 0;
	result = runQuery(CW2A(strQuery));

	if (result)
	{
		MYSQL_ROW record;

		if (result->row_count == 0)
		{
			MessageBox(NULL, _T("The user does not exit! Please type username correctly"), _T("Message"), MB_OK | MB_ICONINFORMATION);
			ret = FALSE;
		}
		else
		{
			while (record = fetch_row(result))
			{
				if (strcmp(record[2], CW2A(strPassword.GetBuffer())) == 0)// if the password matches
				{
					CString strBlocked = CString(record[6]);
					if (strBlocked == "blocked") {
						MessageBox(NULL, _T("The user is blocked."), _T("Message"), MB_OK | MB_ICONINFORMATION);
						freeSQLResult(result);
						return FALSE;
					}
					if (g_strUsername != strName) // if another user logged
					{
						if (g_strUsername != _T("")) // if not startup case
							insertUserHistory(LOG_USER_LOGOUT);

						g_strUsername = strName;
						g_nUserID = atoi(record[0]);
						insertUserHistory(LOG_USER_LOGIN);
					}
					ret = TRUE;
				}
				else //if the password dismatches
				{
					MessageBox(NULL, _T("Wrong password!!! Please type password correctly"), _T("Message"), MB_OK);
					ret = FALSE;
				}
			}
		}
		freeSQLResult(result);
	}
	else
	{
		MessageBox(NULL, _T("Error occured in verifying Password.\nPlease ensure 'user_list' table is exists in the DB"), _T("Error"), MB_OK);
		return FALSE;
	}
	return ret;
}

void CEmbeddedMySQL::deletePerson(int nID)
{
	CString strQuery;
	strQuery.Format(_T("Delete From person_list WHERE id = %d"), nID);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	strQuery.Format(_T("Delete From person_binarydata WHERE id = %d"), nID);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	strQuery.Format(_T("Delete From person_security_info WHERE id = %d"), nID);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	insertPersonChangeInfo(nID, -2, 0);// second parameter indicates all mugshot deleted
	return;
}

void CEmbeddedMySQL::deletePersonBinaryData(int nPersonID, int nIdx)
{
	CString strQuery;
	strQuery.Format(_T("Delete From person_binarydata WHERE IDX = %d"), nIdx);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	insertPersonChangeInfo(nPersonID, nIdx, 0);
	return;
}

void CEmbeddedMySQL::addComment(int nIDX, CString strcomment)
{
	CString strQuery;
	escape(strcomment);
	strQuery.Format(_T("Update monitor_history SET comment = '%s', comment_time = '%s' WHERE IDX = %d"), strcomment, CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")), nIDX);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	return;
}
void CEmbeddedMySQL::updateUserId(int nOldId, int nNewId)
{
	CString strQuery;
	strQuery.Format(_T("Update monitor_history SET id = %d WHERE id = %d"), nNewId, nOldId);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	return;
}

long CEmbeddedMySQL::updatePerson(int nID, CString strFirstName, CString strLastName, CString strNickName, CString strBirthday, int nGender, CString strInfor)
{
	CString strQuery;
	escape(strFirstName);
	escape(strLastName);
	escape(strNickName);
	escape(strInfor);
	strQuery.Format(_T("UPDATE person_list SET firstname = '%s', lastname = '%s', nickname = '%s', birthday = '%s', gender = %d, information = '%s' WHERE id = %d")
		, strFirstName, strLastName, strNickName, strBirthday, nGender, strInfor, nID);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
	return (long)(mysql_insert_id(mysql));
}


void CEmbeddedMySQL::updateUser(CString strUsername, CString strPassword, int nPriv, CString strOldname, CString strPhone)
{
	CString strQuery;
	//	escape(strUsername);
	escape(strPassword);
	strQuery.Format(_T("UPDATE user_list SET username = '%s', password = '%s', privilege_id = %d , phone = '%s' WHERE username = '%s'"), strUsername, strPassword, nPriv, strPhone, strOldname);
	runQueryWithoutResult(CW2A(strQuery));
	return;
}
void CEmbeddedMySQL::updatePersonSecurityInfo(int nID, int nPlayerLevel, int nSecurityLevel, int nBlocked, int nBlockedType, CString strWhen, CString strWhere, CString strWhy)
{
	CString strQuery;
	escape(strWhere);
	escape(strWhy);
	strQuery.Format(_T("UPDATE person_security_info SET player_level= %d, security_level = %d, blocked = %d, blocked_type = %d, blocked_when = '%s', blocked_where = '%s' , blocked_why = '%s' WHERE id = %d")
		, nPlayerLevel, nSecurityLevel, nBlocked, nBlockedType, strWhen, strWhere, strWhy, nID);
	runQueryWithoutResult(CW2A(strQuery.GetBuffer()));
}

int	CEmbeddedMySQL::findPerson(CString strFirstName, CString strLastName)
{
	CString strQuery;

	strQuery.Format(_T("SELECT id From person_list WHERE firstname = '%s' AND lastname = '%s'"), strFirstName, strLastName);
	MYSQL_RES* result = 0;
	result = runQuery(CW2A(strQuery.GetBuffer()));

	if (result)
	{
		MYSQL_ROW record;
		while (record = fetch_row(result))
		{
			return atoi(record[0]);
		}
		freeSQLResult(result);
	}

	return -1;
}

int CEmbeddedMySQL::IsConnected(void)
/* ===========================================================================
NAME OF FUNCTION:	CDatabaseManipulation::IsConnected
CREDIT:				IRDS: Satish
PURPOSE:			This function is used to check connection status of database.
Testing for connection status is simple -- you just check the value of the connection attribute.
It should be non-NULL for MySQL.
PARAMETERS:			None
RETURN VALUE:		Returns connection status of database.
CALLS TO: 			None
CALLED FROM: 		1) Connect - with no parameter
2) Connect - with 4 parameters
3) CloseConnection
4) GetError
5) InsertData
6) UpdateData
7) DeleteData
8) SelectData
Added date: 		12 March, 2015
Updated date:
============================================================================*/
{
	return !(!mysql);
}

TCHAR *CEmbeddedMySQL::GetError(void)
/* ===========================================================================
NAME OF FUNCTION:	CDatabaseManipulation::GetError
CREDIT:				IRDS: Satish
PURPOSE:			This function is used to return error occures during database connection and in database manipulation.
Retrieving error messages under mSQL is very simple and straightforward.
You just use the value of the msqlErrMsg global variable. This value is exactly what our GetError() method returns for mSQL.
MySQL, however, is a little more complicated. Being multithreaded, it needs to provide threadsafe access to any error messages.
It manages to make error handling work in a multithreaded environment by hiding error messages behind the mysql_error() function.
PARAMETERS:			None
RETURN VALUE:		Returns string containing error message.
CALLS TO: 			None
CALLED FROM: 		1) InsertData
2) UpdateData
3) DeleteData
4) SelectData
5) Connect - with no parameter
6) Connect - with 4 parameters
Added date: 		12 March, 2015
Updated date:
============================================================================*/
{
	if (IsConnected())
	{
		return (TCHAR *)mysql_error(mysql);
	}
	else
	{
		return (TCHAR *)mysql_error(&mysqlInitial);
	}
}

// At the moment, it is not used.
bool CEmbeddedMySQL::Connect(/*[IN]*/const TCHAR *ptchHost, /*[IN]*/const TCHAR *ptchUserID,
	/*[IN]*/const TCHAR *ptchDatabase, /*[IN]*/const TCHAR *ptchPassword)
	/* ===========================================================================
	NAME OF FUNCTION:	CDatabaseManipulation::Connect
	CREDIT:				IRDS: Satish
	PURPOSE:			This function is used to connect MYSQL database.
	PARAMETERS:			[IN] 1) TCHAR *ptchHost: Parameter passed as ptchHost may be either a host name or an IP address.
	If host is NULL or the string "localhost", a connection to the local host is assumed.
	For Windows, the client connects using a shared-memory connection,
	if the server has shared-memory connections enabled. Otherwise, TCP/IP is used.
	[IN] 2) TCHAR *ptchUserID: Parameter passed as ptchUserID contains the user's MySQL login ID.
	[IN] 3) TCHAR *ptchDatabase: Parameter passed as ptchDatabase is the database name.
	If ptchDatabase is not NULL, the connection sets the default database to this value.
	[IN] 4) TCHAR *ptchPassword: Parameter passed as ptchPassword contains the password for user.
	RETURN VALUE:		None
	CALLS TO: 			None
	CALLED FROM:
	Added date: 		12 March, 2015
	Updated date:
	============================================================================*/
{
	bool bConnectionSuccess = false;

	if (/**/!IsConnected())
	{
		TRACE(_T("Connection has already been established."));
		bConnectionSuccess = false;
	}

	//Allocates or initializes a MYSQL object suitable for mysql_real_connect()
	//returns an initialized MYSQL* handle. Returns NULL if there was insufficient memory to allocate a new object.

	MYSQL* mysqlinit = mysql_init(NULL);

	//	if (mysql_init(&mysqlInitial) == NULL)
	if (!mysqlinit)
	{
		TRACE(_T("Failed to initiate MySQL connection"));
		bConnectionSuccess = false;
	}
	//Establishes a connection to a database server. Returns a MYSQL * handle or NULL if an error occurred.
	//mysql = mysql_real_connect(&mysqlInitial, (const char*)ptchHost, (const char*)ptchUserID, (const char*)ptchPassword, (const char*)ptchDatabase, 0, 0, 0);
	mysql = mysql_real_connect(mysqlinit, (const char*)ptchHost, (const char*)ptchUserID, (const char*)ptchPassword, (const char*)ptchDatabase, 3306, 0, 0);

	// Check if connection succeeded.
	if (mysql == NULL)
	{
		LPTSTR lptstrError = new TCHAR[1024];

		_stprintf_s(lptstrError, 1024, _T("%s %s"), _T("Couldn't connect to MySQL database server! Error: "), mysql_error(mysql));
		TRACE(lptstrError);

		delete[] lptstrError;

		bConnectionSuccess = false;
	}
	else
	{
		TRACE(_T("Connect success."), _T("INFO"));
		bConnectionSuccess = true;
	}

	if (!IsConnected())
	{
		TRACE(GetError());
		bConnectionSuccess = false;
	}

	return bConnectionSuccess;
}

bool CEmbeddedMySQL::ImportDatabase(/*[IN]*/const TCHAR *ptchHost, /*[IN]*/const TCHAR *ptchUserID, /*[IN]*/const TCHAR *ptchPassword,
	/*[IN]*/int nPort, /*[IN]*/const TCHAR *ptchDatabaseNameToImport, /*[IN]*/const TCHAR *ptchImportDatabaseFile)
	/* ======================================================================================================
	NAME OF FUNCTION:	CDatabaseManipulation::ImportDatabase
	CREDIT:				IRDS: Satish
	PURPOSE:			This function is used to import database using import file into MySql database.
	This function create vector of strings containing commands to import database.
	This function then creates batch file.
	This function then writes vector of commands into batch file.
	This function then execute batch file using cmd.exe.
	At the end after import of database, function removes batch file.
	PARAMETERS:			[IN] 1) TCHAR *ptchHost: Host or server name to connect and import database.
	[IN] 2) TCHAR *ptchUserID: User name to connect and import database.
	[IN] 3) TCHAR *ptchPassword: Password to connect and import database.
	[IN] 4) TCHAR *ptchDatabaseNameToImport: MySql database name to import.
	[IN] 5) TCHAR *ptchImportDatabaseFile: Database file to import into MySql database.
	RETURN VALUE:		None
	CALLS TO: 			1) WriteVectorInFile
	2) GetExecutablePath
	CALLED FROM: 		None
	Added date: 		17 March, 2015
	Updated date:
	=======================================================================================================*/
{
	bool bImportDBSuccess = false;

	//Database connection
	connect_mysql_server(ptchHost, 3306, ptchDatabaseNameToImport, ptchUserID, ptchPassword);	//Connect and create database if not exist.
	if (!IsConnected())
	{
		TRACE(_T("MySql server is not connected."));
		bImportDBSuccess = false;
	}
	else
	{
		/*TCHAR *strCreateDatabaseCommand = new TCHAR[MAX_PATH];
		_tcscpy_s(strCreateDatabaseCommand, MAX_PATH, _T("CREATE DATABASE "));
		_tcscat_s(strCreateDatabaseCommand, MAX_PATH, ptchDatabaseNameToImport);
		mysql_query(mysql, (const char*)strCreateDatabaseCommand);
		delete strCreateDatabaseCommand; */

		//Creating batch file data to execute
		TCHAR szDirectory[MAX_PATH] = L"";
		::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

		TCHAR * strReturnSQLFilePath = new TCHAR[MAX_PATH];
		_tcscpy_s(strReturnSQLFilePath, MAX_PATH, _T(""));

		SearchForFilePath(szDirectory, _T("mysql.exe"), strReturnSQLFilePath);

		if (!_tcscmp(strReturnSQLFilePath, _T("")))
		{
			return false;
		}

		//populate vector with import database command to write into batch file for import database
		vector<TCHAR *> vecToWriteInFile;
		vecToWriteInFile.push_back(_T("@echo off"));
		vecToWriteInFile.push_back(_T("set MainDir = %CD%"));
		vecToWriteInFile.push_back(_T("CD %MainDir%"));

		TCHAR strSQLDrive[3];
		strSQLDrive[0] = strReturnSQLFilePath[0];
		strSQLDrive[1] = strReturnSQLFilePath[1];
		strSQLDrive[2] = _T('\0');
		vecToWriteInFile.push_back(strSQLDrive);

		TCHAR * strTempPath = new TCHAR[MAX_PATH];
		_tcscpy_s(strTempPath, MAX_PATH, _T("CD "));
		_tcscat_s(strTempPath, MAX_PATH, strReturnSQLFilePath);
		vecToWriteInFile.push_back(strTempPath);

		TCHAR strImportCommand[1024];
		_tcscpy_s(strImportCommand, MAX_PATH, _T("mysql --host="));
		_tcscat_s(strImportCommand, ptchHost);
		_tcscat_s(strImportCommand, _T(" --user="));
		_tcscat_s(strImportCommand, ptchUserID);
		_tcscat_s(strImportCommand, _T(" --password="));
		_tcscat_s(strImportCommand, ptchPassword);
		_tcscat_s(strImportCommand, _T(" -D"));
		_tcscat_s(strImportCommand, ptchDatabaseNameToImport);
		_tcscat_s(strImportCommand, _T(" < \""));
		_tcscat_s(strImportCommand, ptchImportDatabaseFile);
		_tcscat_s(strImportCommand, _T("\""));
		vecToWriteInFile.push_back(strImportCommand);
		vecToWriteInFile.push_back(_T("exit"));

		//Create temporary import batch file
		CExecutablePathInfo objExecutablePathInfo;
		LPTSTR lptstrExecutableDirectory = new TCHAR[1024];
		objExecutablePathInfo.GetExecutableDirectory(lptstrExecutableDirectory, 1024);
		_tcscat_s(lptstrExecutableDirectory, MAX_PATH, _T("\\TempDatabaseManipulationImport.bat"));

		//Write into temporary created import batch file
		WriteVectorInFile(vecToWriteInFile, lptstrExecutableDirectory);

		vecToWriteInFile.clear(); //clears the vector
		vecToWriteInFile.shrink_to_fit(); //It requests the removal of unused capacity of vector

		TCHAR strSystemDirPath[MAX_PATH] = _T("");
		GetSystemDirectory(strSystemDirPath, sizeof(strSystemDirPath) / sizeof(_TCHAR));

		// path to cmd.exe, path to batch file, plus some space for quotes, spaces, etc.
		TCHAR strCommandLine[2 * MAX_PATH + 16] = _T("");

		_sntprintf_s(strCommandLine, sizeof(strCommandLine) / sizeof(_TCHAR), _T("\"%s\\cmd.exe\" /C \"%s\""), strSystemDirPath, lptstrExecutableDirectory);

		delete[] strTempPath;
		strTempPath = NULL;
		delete[] strReturnSQLFilePath;
		strReturnSQLFilePath = NULL;

		STARTUPINFO si = { 0 }; // alternative way to zero array
		si.cb = sizeof(si);
		PROCESS_INFORMATION pi = { 0 };

		if (!CreateProcess(NULL,
			strCommandLine,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi)
			)
		{
			LPTSTR lpstrError = new TCHAR[1024];

			_stprintf_s(lpstrError, 1024, _T("CreateProcess failed (%d)\n"), GetLastError());
			TRACE(lpstrError);

			delete[] lpstrError;

			bImportDBSuccess = false;
		}
		else
		{
			bImportDBSuccess = true;
		}

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		//Remove batch file
		remove((const char*)lptstrExecutableDirectory);

		delete[] lptstrExecutableDirectory;
		lptstrExecutableDirectory = NULL;
	}

	return bImportDBSuccess;
}


bool CEmbeddedMySQL::ExportDatabase(/*[IN]*/const TCHAR *ptchHost, /*[IN]*/const TCHAR *ptchUserID, /*[IN]*/const TCHAR *ptchPassword,
	/*[IN]*/const TCHAR *ptchDatabaseNameToExport, /*[IN]*/const TCHAR *ptchExportDatabaseFileWithPath)
	/* ======================================================================================================
	NAME OF FUNCTION:	CDatabaseManipulation::ExportDatabase
	CREDIT:				IRDS: Satish
	PURPOSE:			This function is used to export database to the specified path with specified file name.
	PARAMETERS:			[IN] 1) TCHAR *ptchHost: Host or server name to connect and import database.
	[IN] 2) TCHAR *ptchUserID: User name to connect and import database.
	[IN] 3) TCHAR *ptchPassword: Password to connect and import database.
	[IN] 4) TCHAR *ptchDatabaseNameToExport: MySql database name to export.
	[IN] 5) TCHAR *ptchExportDatabaseFileWithPath: Database filename with path to export MySql database.
	RETURN VALUE:		Returns true on success.
	CALLS TO: 			1) WriteVectorInFile
	2) GetExecutablePath
	CALLED FROM: 		None
	Added date: 		17 March, 2015
	Updated date:
	=======================================================================================================
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%  T H A N K   Y O U , S a t i s h  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
{
	bool bExportDBSuccess = false;

	//Database connection
	//connect_mysql_server(_T("rwunhyok-note"), 3306, _T("FaceCheck_DB"), _T("facecheck"), _T("facecheck"));
	//Connect(ptchHost, ptchUserID, ptchDatabaseNameToExport, ptchPassword);
	if (!IsConnected())
	{
		TRACE(_T("MySql server is not connected."));
		bExportDBSuccess = false;
	}
	else
	{
		//Creating batch file data to execute
		TCHAR szDirectory[MAX_PATH] = L"";
		::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

		TCHAR * strReturnSQLFilePath = new TCHAR[MAX_PATH];
		_tcscpy_s(strReturnSQLFilePath, MAX_PATH, _T(""));

		SearchForFilePath(szDirectory, _T("mysqldump.exe"), strReturnSQLFilePath);

		if (!_tcscmp(strReturnSQLFilePath, _T("")))
		{
			return false;
		}

		//populate vector with export database command to write into batch file for export database
		vector<TCHAR *> vecToWriteInFile;
		vecToWriteInFile.push_back(_T("@echo off"));
		vecToWriteInFile.push_back(_T("set MainDir = %CD%"));
		vecToWriteInFile.push_back(_T("CD %MainDir%"));

		TCHAR strSQLDrive[3];
		strSQLDrive[0] = strReturnSQLFilePath[0];
		strSQLDrive[1] = strReturnSQLFilePath[1];
		strSQLDrive[2] = _T('\0');
		vecToWriteInFile.push_back(strSQLDrive);

		TCHAR * strTempPath = new TCHAR[MAX_PATH];
		_tcscpy_s(strTempPath, MAX_PATH, _T("CD "));
		_tcscat_s(strTempPath, MAX_PATH, strReturnSQLFilePath);
		vecToWriteInFile.push_back(strTempPath);

		TCHAR strImportCommand[1024];
		_tcscpy_s(strImportCommand, MAX_PATH, _T("mysqldump --host="));
		_tcscat_s(strImportCommand, ptchHost);
		_tcscat_s(strImportCommand, _T(" --user="));
		_tcscat_s(strImportCommand, ptchUserID);
		_tcscat_s(strImportCommand, _T(" --password="));
		_tcscat_s(strImportCommand, ptchPassword);
		_tcscat_s(strImportCommand, _T(" --result-file="));
		_tcscat_s(strImportCommand, _T("\""));
		_tcscat_s(strImportCommand, ptchExportDatabaseFileWithPath);
		_tcscat_s(strImportCommand, _T("\""));
		_tcscat_s(strImportCommand, _T(" "));
		_tcscat_s(strImportCommand, ptchDatabaseNameToExport);
		vecToWriteInFile.push_back(strImportCommand);
		vecToWriteInFile.push_back(_T("exit"));

		//Create temporary import batch file
		CExecutablePathInfo objExecutablePathInfo;
		LPTSTR lptstrExecutableDirectory = new TCHAR[1024];
		objExecutablePathInfo.GetExecutableDirectory(lptstrExecutableDirectory, 1024);
		_tcscat_s(lptstrExecutableDirectory, MAX_PATH, _T("\\TempDatabaseManipulationExport.bat"));

		//Write into temporary created import batch file
		WriteVectorInFile(vecToWriteInFile, lptstrExecutableDirectory);

		vecToWriteInFile.clear(); //clears the vector
		vecToWriteInFile.shrink_to_fit(); //It requests the removal of unused capacity of vector

		TCHAR strSystemDirPath[MAX_PATH] = _T("");
		GetSystemDirectory(strSystemDirPath, sizeof(strSystemDirPath) / sizeof(_TCHAR));

		// path to cmd.exe, path to batch file, plus some space for quotes, spaces, etc.
		TCHAR strCommandLine[2 * MAX_PATH + 16] = _T("");

		_sntprintf_s(strCommandLine, sizeof(strCommandLine) / sizeof(_TCHAR), _T("\"%s\\cmd.exe\" /C \"%s\""), strSystemDirPath, lptstrExecutableDirectory);

		delete[] strTempPath;
		strTempPath = NULL;
		delete[] strReturnSQLFilePath;
		strReturnSQLFilePath = NULL;

		STARTUPINFO si = { 0 }; // alternative way to zero array
		si.cb = sizeof(si);
		PROCESS_INFORMATION pi = { 0 };

		if (!CreateProcess(NULL,
			strCommandLine,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi)
			)
		{
			LPTSTR lpstrError = new TCHAR[1024];

			_stprintf_s(lpstrError, 1024, _T("CreateProcess failed (%d)\n"), GetLastError());
			TRACE(lpstrError);

			delete[] lpstrError;

			bExportDBSuccess = false;
		}
		else
		{
			bExportDBSuccess = true;
		}

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		//Remove batch file
		remove((const char*)lptstrExecutableDirectory);

		delete[] lptstrExecutableDirectory;
		lptstrExecutableDirectory = NULL;
	}

	return bExportDBSuccess;
}

void CEmbeddedMySQL::SearchForFilePath(/*[IN]*/TCHAR *strStartingDirectoryPath, /*[IN]*/TCHAR *strFileNameToSearchForDirectory, /*[OUT]*/TCHAR *strReturnFileDirectoryPath)
/* =====================================================================================================================
NAME OF FUNCTION:	CDatabaseManipulation::SearchForFilePath
CREDIT:				IRDS: Satish
PURPOSE:			This function is used to retrieve containing directory path of given file.
PARAMETERS:			[IN]  1) TCHAR *strStartingDirectoryPath: Starting directory path to start search with.
[IN]  2) TCHAR *strFileNameToSearchForDirectory: File to search.
[OUT] 3) TCHAR *strReturnFileDirectoryPath: Containing directory path of given file.
RETURN VALUE:		None
CALLS TO: 			None
CALLED FROM: 		1) ImportDatabase(const TCHAR*, const TCHAR*)
2) ImportDatabase(const TCHAR*, const TCHAR*, const TCHAR*, const TCHAR*, const TCHAR*)
3) ExportDatabase(const TCHAR*, const TCHAR*)
4) ExportDatabase(const TCHAR*, const TCHAR*, const TCHAR*, const TCHAR*, const TCHAR*)
Added date: 		17 March, 2015
Updated date:
======================================================================================================================*/
{
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR strTempStartingDirPath[MAX_PATH];
	TCHAR strPathFound[MAX_PATH];

	_stprintf_s(strTempStartingDirPath, MAX_PATH, _T("%s\\*"), strStartingDirectoryPath);
	_tcsncpy_s(strPathFound, MAX_PATH, strTempStartingDirPath, (_tcslen(strTempStartingDirPath) - 2));

	if ((hFind = FindFirstFile(strTempStartingDirPath, &wfd)) == INVALID_HANDLE_VALUE)
	{
		LPTSTR lpstrError = new TCHAR[1024];

		_stprintf_s(lpstrError, 1024, _T("FindFirstFIle failed on path = \"%s\""), strTempStartingDirPath);
		TRACE(lpstrError);

		delete[] lpstrError;

		return;
	}

	static BOOL bContinueSearch = TRUE;
	static BOOL bFound = TRUE;

	bContinueSearch = TRUE;
	bFound = TRUE;

	while (bContinueSearch)
	{
		if ((_tcsncmp(_T("."), wfd.cFileName, 1) != 0) && (_tcsncmp(_T(".."), wfd.cFileName, 2) != 0))
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				_stprintf_s(strTempStartingDirPath, MAX_PATH, _T("%s\\%s"), strStartingDirectoryPath, wfd.cFileName);

				SearchForFilePath(strTempStartingDirPath, strFileNameToSearchForDirectory, strReturnFileDirectoryPath);
			}
			else
			{
				TCHAR * strTemp = new TCHAR[MAX_PATH];

				_tcscpy_s(strTemp, MAX_PATH, wfd.cFileName);

				if (!_tcscmp(strTemp, strFileNameToSearchForDirectory))
				{
					_tcscpy_s(strReturnFileDirectoryPath, MAX_PATH, strPathFound);
					_tcscpy_s(strTempStartingDirPath, MAX_PATH, _T(""));
					bFound = false;
					bContinueSearch = false;
					hFind = NULL;
				}

				delete[] strTemp;
				strTemp = NULL;
			}
		}

		if (bFound)
		{
			bContinueSearch = FindNextFile(hFind, &wfd);
		}
	}

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		LPTSTR lpstrError = new TCHAR[1024];

		_stprintf_s(lpstrError, 1024, _T("FindNextFile died for some reason; path = \"%s\""), strTempStartingDirPath);
		TRACE(lpstrError);

		delete[] lpstrError;

		return;
	}

	if (FindClose(hFind) == FALSE)
	{
		LPTSTR lpstrError = new TCHAR[1024];

		_stprintf_s(lpstrError, 1024, _T("FindClose failed"));
		TRACE(lpstrError);

		delete[] lpstrError;

		return;
	}
}

void CEmbeddedMySQL::WriteVectorInFile(/*[IN]*/vector<TCHAR *> vecSource, /*[IN]*/TCHAR * strFileName)
/* ===========================================================================
NAME OF FUNCTION:	CDatabaseManipulation::WriteVectorInFile
CREDIT:				IRDS: Satish
PURPOSE:			This function is used to write vector of strings into file.
PARAMETERS:			[IN] 1) vector<TCHAR *> vecSource: Vector of strings to write into file.
[IN] 2) TCHAR * strFileName: File to write.
RETURN VALUE:		None
CALLS TO: 			None
CALLED FROM: 		None
Added date: 		17 March, 2015
Updated date:
============================================================================*/
{
	CString strOut;
	int k = vecSource.size();
	for (int i = 0; i < k; i++)
	{
		strOut.Append(vecSource[i]);
		strOut.Append(L"\n");
	}

	CStdioFile file;
	if (file.Open((LPCTSTR)strFileName, CFile::modeCreate | CFile::modeWrite))
	{
		file.WriteString(strOut);
	}

}
