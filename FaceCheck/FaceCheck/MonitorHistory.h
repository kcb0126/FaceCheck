#pragma once
#include "ListOfMonitorHistory.h"
#include "BitmapButtonPlus.h"
#include "LabelTrans.h"
#include "afxwin.h"

// CMonitorHistory dialog

class CMonitorHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CMonitorHistory)

public:
	CMonitorHistory();
	virtual ~CMonitorHistory();

// Dialog Data
	enum { IDD = IDD_MONITOR_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	CListOfMonitorHistory* m_pListOfMonitorHistory = NULL;

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
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
};
