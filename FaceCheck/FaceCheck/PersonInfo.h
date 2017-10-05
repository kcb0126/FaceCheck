#pragma once
#include "atltime.h"
#include "afxwin.h"

// CPersonInfo dialog

class CPersonInfo : public CPropertyPage
{
	DECLARE_DYNAMIC(CPersonInfo)

public:
	CPersonInfo();
	virtual ~CPersonInfo();

// Dialog Data
	enum { IDD = IDD_PERSONINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	

public:
	int m_nGender;
	int m_nPlayerLevel;
	int m_nSecurityLevel;
	CTime m_dateBirthday;
	CTime m_dateBlockedWhen;
	CTime m_dateTo;
	CString m_strFirstName;
	CEdit m_strInformation;
	CString m_strLastName;
	CString m_strNickName;
	CString m_strBlockedReason;
	CString m_strBlockedPlace;
	int m_nBlockType;
	int m_nBlocked;
	CStatic m_staticPhoto;
};
