#pragma once
#include "resource.h"
#include "LabelTrans.h"
#include "afxwin.h"

// CCellOfPersonManage dialog

class CCellOfPersonManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCellOfPersonManage)

public:
	CCellOfPersonManage();
	virtual ~CCellOfPersonManage();

// Dialog Data
	enum { IDD = IDD_CELL_PERSONMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CLabelTrans m_lblName;
	CLabelTrans m_lblNickname1;
	CLabelTrans m_lblNickname;
	CLabelTrans m_lblGender;
	CLabelTrans m_lblBirthday1;
	CLabelTrans m_lblBirthday;
	CLabelTrans m_lblGuesttype1;
	CLabelTrans m_lblGuesttype;
	CLabelTrans m_lblSafetytype1;
	CLabelTrans m_lblSafetytype;
	CLabelTrans m_lblBlocked;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	CStatic m_staticPhoto;
	afx_msg void OnBnClickedButtonEdit();

public:
	int m_nID;
};
