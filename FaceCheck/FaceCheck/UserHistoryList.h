#pragma once
#include "ListOfUserHistory.h"
#include "CellOfUserHistory.h"
#include "BitmapButtonPlus.h"
#include "LabelTrans.h"
#include "afxwin.h"

// CUserHistoryList dialog

class CUserHistoryList : public CPropertyPage
{
	DECLARE_DYNAMIC(CUserHistoryList)

public:
	CUserHistoryList();
	virtual ~CUserHistoryList();

// Dialog Data
	enum { IDD = IDD_USERHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CCellOfUserHistory m_listHeader;
	CListOfUserHistory* m_pListOfUserHistory = NULL;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CBitmapButtonPlus m_btnFirst;
	CBitmapButtonPlus m_btnPrev;
	CBitmapButtonPlus m_btnNext;
	CBitmapButtonPlus m_btnLast;
	CEdit m_editPagenumber;
	CLabelTrans m_lblTotalrecords;
	CLabelTrans m_lblTotalpages;

public:
	CCriticalSection m_secData;

public:
	int m_nRecordCount = 0;
	int m_nPageCount = 0;
	int m_nPageCapacity = 30;
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
};
