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
	void SetPersonID(int nID);
	void InitializeMembers(void);
	void RefreshThumbImage(void);
	void GetChangedInfo(person_info t);
	BOOL IsDataValid();
	void CheckInput(CString &strField, int nID);

public:
	int m_nNo;
	CPerson m_person;
	CxImage m_imgPhoto;
	BOOL m_bPhotoShow;
	CString m_strChanged;
	int m_nMode;

public:
	int m_nGender;
	int m_nPlayerLevel;
	int m_nSecurityLevel;
	CTime m_dateBirthday;
	CTime m_dateBlockedWhen;
	CTime m_dateTo;
	CString m_strFirstName;
	CString m_strInformation;
	CString m_strLastName;
	CString m_strNickName;
	CString m_strBlockedReason;
	CString m_strBlockedPlace;
	int m_nBlockType;
	int m_nBlocked;
	CStatic m_staticPhoto;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnStnClickedStaticPhoto();
	afx_msg void OnBnClickedButtonFiles();
	afx_msg void OnEnChangeEditFirstname();
	afx_msg void OnEnChangeEditLastname();
	afx_msg void OnEnChangeEditNickname();
	afx_msg void OnBnClickedButtonCamera();
	virtual BOOL OnInitDialog();
};
