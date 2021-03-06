#pragma once
#include "ListOfPersonManage.h"
#include "BitmapButtonPlus.h"
#include "afxwin.h"
#include "LabelTrans.h"

// CPersonManageList dialog

class CPersonManageList : public CPropertyPage
{
	DECLARE_DYNAMIC(CPersonManageList)

public:
	CPersonManageList();
	virtual ~CPersonManageList();

// Dialog Data
	enum { IDD = IDD_PERSONMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListOfPersonManage* m_pListOfPersonManage = NULL;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CBitmapButtonPlus m_btnFirst;
	CBitmapButtonPlus m_btnPrev;
	CBitmapButtonPlus m_btnNext;
	CBitmapButtonPlus m_btnLast;
	CEdit m_editPagenumber;
	CLabelTrans m_lblTotalrecords;
	CLabelTrans m_lblTotalpages;
	virtual BOOL OnInitDialog();

public:
	CCriticalSection m_secData;

public:
	int m_nRecordCount = 0;
	int m_nPageCount = 0;
	int m_nPageCapacity = 10;
	int m_nCurrentPageNumber = 0;

public:
	void ShowItems(int nBeginPos, int nCount);
	void ShowPage(int nPageNumber);
	void ShowFirst();
	void ShowPrev();
	void ShowNext();
	void ShowLast();
	void RefreshList();
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonLast();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CBitmapButtonPlus m_btnAdd;
	afx_msg void OnBnClickedButtonAdd();
};
