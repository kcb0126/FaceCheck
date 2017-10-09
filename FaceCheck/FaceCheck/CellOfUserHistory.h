#pragma once
#include "Resource.h"
#include "LabelTrans.h"


// CCellOfUserHistory dialog

class CCellOfUserHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfUserHistory)

public:
	CCellOfUserHistory();
	virtual ~CCellOfUserHistory();

// Dialog Data
	enum { IDD = IDD_CELL_USERHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strUsername;
	CString m_strAction;
	CString m_strTime;
	CString m_strContent;
	CLabelTrans m_lblUsername;
	CLabelTrans m_lblAction;
	CLabelTrans m_lblTime;
	CLabelTrans m_lblContent;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CLabelTrans m_lblNo;
};
