#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "LabelTrans.h"

// CCellOfMonitorHistory dialog

class CCellOfMonitorHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfMonitorHistory)

public:
	CCellOfMonitorHistory();
	virtual ~CCellOfMonitorHistory();

// Dialog Data
	enum { IDD = IDD_CELL_MONITORHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticPhoto;
	CStatic m_staticPhotoRegistered;
	CString m_strName;
	CString m_strAgeNGender;
	CString m_strAccessedwhen;
	CString m_strStatus;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CLabelTrans m_lblName;
	CLabelTrans m_lblAgeGender;
	CLabelTrans m_lblAccessed;
	CLabelTrans m_lblAccessedWhen;
	CLabelTrans m_lblStatus1;
	CLabelTrans m_lblStatus;
};
