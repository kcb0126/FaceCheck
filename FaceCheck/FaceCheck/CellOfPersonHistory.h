#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "LabelTrans.h"

// CCellOfPersonHistory dialog

class CCellOfPersonHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfPersonHistory)

public:
	CCellOfPersonHistory();
	virtual ~CCellOfPersonHistory();

// Dialog Data
	enum { IDD = IDD_CELL_PERSONHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CStatic m_staticPhoto;
	CString m_strTime;
	CString m_strName;
	CString m_strGender;
	CString m_strAge;
	CString m_strPlace;
	CString m_strView;
	CString m_strComment;
	CLabelTrans m_lblTime;
	CLabelTrans m_lblName;
	CLabelTrans m_lblGender;
	CLabelTrans m_lblAge;
	CLabelTrans m_lblPlace;
	CLabelTrans m_lblView;
	CLabelTrans m_lblComment;
	int m_nNo;
	CLabelTrans m_lblNo;
	CLabelTrans m_lblAge1;
	CLabelTrans m_lblView1;
};
