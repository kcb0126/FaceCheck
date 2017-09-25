/************************************************************************/
/*
Comment:	Define common data used in the project.
Producer:	RobinHood
Date:		2017.02.23
*/
/************************************************************************/
#pragma once

// define for UI 
#define MAIN_MIN_WIDTH				900
#define MAIN_MIN_HEIGHT				600
#define BANNER_HEIGHT				30
#define MENUBUTTON_HEIGHT			25
#define MENUBUTTON_WIDTH			100
#define COMBO_SCREENMODE_WIDTH		50
#define COMBO_SCREENMODE_HEIGHT		20
#define STATIC_SCREENMODE_WIDTH		70
#define STATIC_SCREENMODE_HEIGHT	20
#define CUSTOMER_PHOTO_WIDTH		100
#define CUSTOMER_PHOTO_HEIGHT		100
#define HISTORY_PHOTO_WIDTH			50
#define HISTORY_PHOTO_HEIGHT		50

// timer id
#define ID_SYNC_TIMER				1

// user define messages
#define UM_ADD_HISTORY		WM_USER + 316

//modes for User Manage
#define MODE_USER_ADD				1
#define MODE_USER_MODIFY			2

//modes for Customer manage
#define MODE_CUSTOMER_ADD			1
#define MODE_CUSTOMER_MODIFY		2
#define MODE_CUSTOMER_MUGADD		3
#define MODE_CUSTOMER_SHOW			4

//user groups
#define Administrator				0
#define	FrontService				1
#define TechnicalSupport			2
#define Office						3

//
#define MONITOR_CLIENT_MUTEX	_T("FaceCheck Monitor mutex")
#define AGE_LIMIT					20

//pages of program
#define MONITOR_PAGE				0
#define MONITOR_HISTORY_PAGE		1
#define CUSTOMER_MANAGE_PAGE		2
#define CUSTOMER_HISTORY_PAGE		3
#define USER_MANAGE_PAGE			4
#define USER_HISTORY_PAGE			5
#define SETTING_PAGE				6

#define MAX_CAMERA_NUM				16

//log texts
#define LOG_USER_LOGIN			_T("logged in")
#define LOG_USER_LOGOUT			_T("logged out")

//////////////////////////////////////////////////////////////////////////
//	Global structures
typedef struct person_info
{
	// person_list table
	int		m_nID;
	CString m_strFirstname;
	CString m_strLastname;
	CString m_strNickname;
	CString m_strBirthday;
	int		m_nAge;
	int		m_nGender;
	CString m_strInfo;

	//person_security_info table
	int		m_nPlayerLevel;
	int		m_nSecurityLevel;
	int		m_nBlocked;
	int		m_nBlockedType;
	CString m_strBlockedWhen;
	CString m_strBlockedWhere;
	CString m_strBlockedWhy;
} person_info;