// PersonInfo.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonInfo.h"
#include "afxdialogex.h"


// CPersonInfo dialog

IMPLEMENT_DYNAMIC(CPersonInfo, CPropertyPage)

CPersonInfo::CPersonInfo()
	: CPropertyPage(CPersonInfo::IDD)
	, m_nGender(0)
	, m_nPlayerLevel(0)
	, m_nSecurityLevel(0)
	, m_dateBirthday(0)
	, m_dateBlockedWhen(0)
	, m_dateTo(0)
	, m_strFirstName(_T(""))
	, m_strLastName(_T(""))
	, m_strNickName(_T(""))
	, m_strBlockedReason(_T(""))
	, m_strBlockedPlace(_T(""))
	, m_nBlockType(0)
	, m_nBlocked(0)
{

}

CPersonInfo::~CPersonInfo()
{
}

void CPersonInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_GENDER, m_nGender);
	DDX_CBIndex(pDX, IDC_COMBO_GUESTTYPE, m_nPlayerLevel);
	DDX_CBIndex(pDX, IDC_COMBO_SAFETYTYPE, m_nSecurityLevel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_dateBirthday);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dateBlockedWhen);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dateTo);
	DDX_Text(pDX, IDC_EDIT_FIRSTNAME, m_strFirstName);
	DDX_Control(pDX, IDC_EDIT_INFOMATION, m_strInformation);
	DDX_Text(pDX, IDC_EDIT_LASTNAME, m_strLastName);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, m_strNickName);
	DDX_Text(pDX, IDC_EDIT_REASON, m_strBlockedReason);
	DDX_Text(pDX, IDC_EDIT_WHERE, m_strBlockedPlace);
	DDX_Radio(pDX, IDC_RADIO_LOCAL, m_nBlockType);
	DDX_Radio(pDX, IDC_RADIO_UNBLOCKED, m_nBlocked);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_staticPhoto);
}


BEGIN_MESSAGE_MAP(CPersonInfo, CPropertyPage)
END_MESSAGE_MAP()


// CPersonInfo message handlers
